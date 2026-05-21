#include "repositories/UserRepository.hpp"

#include <cstring>
#include <iostream>

UserRepository::UserRepository(MYSQL* conn)
    : conn_(conn) {}

// ======================================================
// FIND USER BY EMAIL
// ======================================================
std::optional<User> UserRepository::findByEmail(
    const std::string& email) {

    const char* query =
        "SELECT id, name, email, password_hash, role, active "
        "FROM users WHERE email=? LIMIT 1";

    MYSQL_STMT* stmt = mysql_stmt_init(conn_);

    if (!stmt) {
        std::cerr << "[MYSQL] stmt init falhou\n";
        return std::nullopt;
    }

    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        std::cerr << "[MYSQL PREPARE ERROR] "
                  << mysql_stmt_error(stmt) << std::endl;

        mysql_stmt_close(stmt);
        return std::nullopt;
    }

    MYSQL_BIND param[1];
    memset(param, 0, sizeof(param));

    param[0].buffer_type = MYSQL_TYPE_STRING;
    param[0].buffer = (char*)email.c_str();
    param[0].buffer_length = email.length();

    if (mysql_stmt_bind_param(stmt, param)) {
        std::cerr << "[MYSQL BIND ERROR] "
                  << mysql_stmt_error(stmt) << std::endl;

        mysql_stmt_close(stmt);
        return std::nullopt;
    }

    if (mysql_stmt_execute(stmt)) {
        std::cerr << "[MYSQL EXECUTE ERROR] "
                  << mysql_stmt_error(stmt) << std::endl;

        mysql_stmt_close(stmt);
        return std::nullopt;
    }

    User user;

    int id = 0;
    int activeInt = 0;

    char name[255] = {0};
    char emailRes[255] = {0};
    char password[255] = {0};
    char role[50] = {0};

    unsigned long name_len = 0;
    unsigned long email_len = 0;
    unsigned long password_len = 0;
    unsigned long role_len = 0;

    // ======================================================
    // CORREÇÃO PARA MARIADB / MSYS2
    // ======================================================
    my_bool is_null[6] = {0};

    MYSQL_BIND result[6];
    memset(result, 0, sizeof(result));

    // ID
    result[0].buffer_type = MYSQL_TYPE_LONG;
    result[0].buffer = &id;

    // NAME
    result[1].buffer_type = MYSQL_TYPE_STRING;
    result[1].buffer = name;
    result[1].buffer_length = sizeof(name);
    result[1].length = &name_len;
    result[1].is_null = &is_null[1];

    // EMAIL
    result[2].buffer_type = MYSQL_TYPE_STRING;
    result[2].buffer = emailRes;
    result[2].buffer_length = sizeof(emailRes);
    result[2].length = &email_len;
    result[2].is_null = &is_null[2];

    // PASSWORD
    result[3].buffer_type = MYSQL_TYPE_STRING;
    result[3].buffer = password;
    result[3].buffer_length = sizeof(password);
    result[3].length = &password_len;
    result[3].is_null = &is_null[3];

    // ROLE
    result[4].buffer_type = MYSQL_TYPE_STRING;
    result[4].buffer = role;
    result[4].buffer_length = sizeof(role);
    result[4].length = &role_len;
    result[4].is_null = &is_null[4];

    // ACTIVE
    result[5].buffer_type = MYSQL_TYPE_LONG;
    result[5].buffer = &activeInt;
    result[5].is_null = &is_null[5];

    if (mysql_stmt_bind_result(stmt, result)) {
        std::cerr << "[MYSQL BIND RESULT ERROR] "
                  << mysql_stmt_error(stmt) << std::endl;

        mysql_stmt_close(stmt);
        return std::nullopt;
    }

    if (mysql_stmt_store_result(stmt)) {
        mysql_stmt_close(stmt);
        return std::nullopt;
    }

    if (mysql_stmt_fetch(stmt) != 0) {
        mysql_stmt_close(stmt);
        return std::nullopt;
    }

    user.id = id;
    user.name = std::string(name);
    user.email = std::string(emailRes);
    user.password = std::string(password);
    user.role = std::string(role);
    user.active = activeInt != 0;

    mysql_stmt_close(stmt);

    return user;
}

// ======================================================
// CREATE USER
// ======================================================
bool UserRepository::create(
    const std::string& name,
    const std::string& email,
    const std::string& password,
    bool active,
    const std::string& role) {

    const char* query =
        "INSERT INTO users(name,email,password_hash,active,role) "
        "VALUES(?,?,?,?,?)";

    MYSQL_STMT* stmt = mysql_stmt_init(conn_);

    if (!stmt) {
        return false;
    }

    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        mysql_stmt_close(stmt);
        return false;
    }

    MYSQL_BIND bind[5];
    memset(bind, 0, sizeof(bind));

    int activeInt = active ? 1 : 0;

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char*)name.c_str();
    bind[0].buffer_length = name.length();

    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = (char*)email.c_str();
    bind[1].buffer_length = email.length();

    bind[2].buffer_type = MYSQL_TYPE_STRING;
    bind[2].buffer = (char*)password.c_str();
    bind[2].buffer_length = password.length();

    bind[3].buffer_type = MYSQL_TYPE_LONG;
    bind[3].buffer = &activeInt;

    bind[4].buffer_type = MYSQL_TYPE_STRING;
    bind[4].buffer = (char*)role.c_str();
    bind[4].buffer_length = role.length();

    if (mysql_stmt_bind_param(stmt, bind)) {
        mysql_stmt_close(stmt);
        return false;
    }

    bool ok = mysql_stmt_execute(stmt) == 0;

    if (!ok) {
        std::cerr << "[MYSQL INSERT ERROR] "
                  << mysql_stmt_error(stmt) << std::endl;
    }

    mysql_stmt_close(stmt);

    return ok;
}

// ======================================================
// UPDATE PASSWORD
// ======================================================
bool UserRepository::updatePassword(
    int userId,
    const std::string& newPassword) {

    const char* query =
        "UPDATE users SET password_hash=? WHERE id=?";

    MYSQL_STMT* stmt = mysql_stmt_init(conn_);

    if (!stmt) {
        return false;
    }

    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        mysql_stmt_close(stmt);
        return false;
    }

    MYSQL_BIND bind[2];
    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char*)newPassword.c_str();
    bind[0].buffer_length = newPassword.length();

    bind[1].buffer_type = MYSQL_TYPE_LONG;
    bind[1].buffer = &userId;

    if (mysql_stmt_bind_param(stmt, bind)) {
        mysql_stmt_close(stmt);
        return false;
    }

    bool ok = mysql_stmt_execute(stmt) == 0;

    mysql_stmt_close(stmt);

    return ok;
}

// ======================================================
// EXISTS BY EMAIL
// ======================================================
bool UserRepository::existsByEmail(
    const std::string& email) {

    const char* query =
        "SELECT id FROM users WHERE email=? LIMIT 1";

    MYSQL_STMT* stmt = mysql_stmt_init(conn_);

    if (!stmt) {
        return false;
    }

    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        mysql_stmt_close(stmt);
        return false;
    }

    MYSQL_BIND param[1];
    memset(param, 0, sizeof(param));

    param[0].buffer_type = MYSQL_TYPE_STRING;
    param[0].buffer = (char*)email.c_str();
    param[0].buffer_length = email.length();

    if (mysql_stmt_bind_param(stmt, param)) {
        mysql_stmt_close(stmt);
        return false;
    }

    if (mysql_stmt_execute(stmt)) {
        mysql_stmt_close(stmt);
        return false;
    }

    mysql_stmt_store_result(stmt);

    bool exists = mysql_stmt_num_rows(stmt) > 0;

    mysql_stmt_close(stmt);

    return exists;
}