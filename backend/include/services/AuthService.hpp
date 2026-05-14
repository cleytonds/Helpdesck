#pragma once

#include "repositories/UserRepository.hpp"
#include "dto/LoginRequest.hpp"
#include "dto/RegisterRequest.hpp"

#include <string>
#include <mariadb/mysql.h>

// ======================================================
// RESULTADO
// ======================================================
struct AuthResult {
    bool success = false;

    int userId = 0;

    std::string name;
    std::string email;
    std::string role;

    std::string token;
    std::string message;
};

// ======================================================
// SERVICE
// ======================================================
class AuthService {
private:
    UserRepository& userRepo_;
    MYSQL* conn_;

public:
    AuthService(UserRepository& userRepo, MYSQL* conn);

    AuthResult login(const LoginRequest& req) const;

    AuthResult registerUser(const RegisterRequest& req) const;

    AuthResult forgotPassword(const std::string& email);

    AuthResult resetPassword(
        const std::string& token,
        const std::string& newPassword
    );
};