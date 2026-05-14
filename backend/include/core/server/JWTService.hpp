#pragma once

#include <string>
#include "httplib.h"

// ======================================================
// PAYLOAD JWT
// ======================================================
struct JWTPayload {

    int userId = 0;

    std::string email;

    std::string role;
};

// ======================================================
// SERVICE JWT
// ======================================================
class JWTService {

public:

    // token login
    static std::string generateToken(
        int userId,
        const std::string& email,
        const std::string& role
    );

    // reset senha
    static std::string generateResetToken(int userId);

    // valida reset
    static int validateResetToken(const std::string& token);

    // valida jwt
    static bool validateToken(
        const std::string& token,
        JWTPayload& payload
    );

    // header bearer
    static std::string extractFromHeader(
        const httplib::Request& req
    );
};