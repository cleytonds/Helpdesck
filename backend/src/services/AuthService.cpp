#include "services/AuthService.hpp"
#include "core/server/JWTService.hpp"

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>

#include <mariadb/mysql.h>


#include "services/EmailService.hpp"

// ======================================================
// GERA TOKEN
// ======================================================
std::string generateToken() {

    const std::string chars =
        "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    std::string token;

    for (int i = 0; i < 32; i++) {
        token += chars[rand() % chars.size()];
    }

    return token;
}

// ======================================================
// CONSTRUTOR
// ======================================================
AuthService::AuthService(UserRepository& userRepo, MYSQL* conn)
    : userRepo_(userRepo), conn_(conn)
{
    srand(time(nullptr));
}

// ======================================================
// LOGIN
// ======================================================
AuthResult AuthService::login(const LoginRequest& req) const {

    AuthResult result;

    auto userOpt = userRepo_.findByEmail(req.email);

    if (!userOpt.has_value()) {
        result.message = "Usuário não encontrado";
        return result;
    }

    const User& user = userOpt.value();

    if (req.password != user.password) {
        result.message = "Senha incorreta";
        return result;
    }

    if (!user.active) {
        result.message = "Conta desativada";
        return result;
    }

    result.token = JWTService::generateToken(
        user.id,
        user.email,
        user.role
    );

    result.success = true;
    result.userId = user.id;
    result.name = user.name;
    result.email = user.email;
    result.role = user.role;
    result.message = "Login realizado com sucesso";

    return result;
}

// ======================================================
// REGISTER
// ======================================================
AuthResult AuthService::registerUser(const RegisterRequest& req) const {

    AuthResult result;

    if (userRepo_.existsByEmail(req.email)) {
        result.message = "Email já cadastrado";
        return result;
    }

    std::string hashedPassword = req.password;

    bool ok = userRepo_.create(
        req.name,
        req.email,
        hashedPassword,
        true,
        "user"
    );

    if (!ok) {
        result.message = "Erro ao criar usuário";
        return result;
    }

    result.success = true;
    result.message = "Usuário criado com sucesso";

    return result;
}

// ======================================================
// FORGOT PASSWORD
// ======================================================
AuthResult AuthService::forgotPassword(const std::string& email) {

    AuthResult result;

    auto userOpt = userRepo_.findByEmail(email);

    if (!userOpt.has_value()) {
        result.message = "Email não encontrado";
        return result;
    }

    std::string token = generateToken();

    std::stringstream query;

    query << "INSERT INTO password_resets "
          << "(email, token, expires_at) VALUES('"
          << email << "', '"
          << token << "', NOW() + INTERVAL 15 MINUTE)";

    if (mysql_query(conn_, query.str().c_str()) != 0) {

        std::cerr << "[MYSQL ERROR] "
                  << mysql_error(conn_)
                  << std::endl;

        result.message = "Erro ao gerar token";
        return result;
    }

    std::string link =
        "http://localhost:5173/reset-password/" + token;

    sendEmail(email, link);

    std::cout << "\n====================================\n";
    std::cout << "LINK RESET:\n" << link << std::endl;
    std::cout << "====================================\n\n";

    result.success = true;
    result.message = "Email enviado";

    return result;
}

// ======================================================
// RESET PASSWORD
// ======================================================
AuthResult AuthService::resetPassword(
    const std::string& token,
    const std::string& newPassword
) {

    AuthResult result;

    std::stringstream query;

    query << "SELECT email FROM password_resets "
          << "WHERE token='"
          << token
          << "' AND expires_at > NOW() "
          << "LIMIT 1";

    if (mysql_query(conn_, query.str().c_str()) != 0) {

        result.message = "Erro no banco";
        return result;
    }

    MYSQL_RES* res = mysql_store_result(conn_);

    if (!res || mysql_num_rows(res) == 0) {

        result.message = "Token inválido ou expirado";
        return result;
    }

    MYSQL_ROW row = mysql_fetch_row(res);

    std::string email = row[0];

    mysql_free_result(res);

    std::string hashedPassword = newPassword;

    auto userOpt = userRepo_.findByEmail(email);

    if (!userOpt.has_value()) {
        result.message = "Usuário não encontrado";
        return result;
    }

    bool ok =
        userRepo_.updatePassword(
            userOpt->id,
            hashedPassword
        );

    if (!ok) {

        result.message = "Erro ao atualizar senha";
        return result;
    }

    std::stringstream del;

    del << "DELETE FROM password_resets "
        << "WHERE token='" << token << "'";

    mysql_query(conn_, del.str().c_str());

    result.success = true;
    result.message = "Senha atualizada com sucesso";

    return result;
}