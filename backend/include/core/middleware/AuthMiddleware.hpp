#ifndef AUTH_MIDDLEWARE_HPP
#define AUTH_MIDDLEWARE_HPP

#include "httplib.h"
#include <string>

// ======================================================
// Middleware: Verifica autenticacao JWT
// ======================================================
class AuthMiddleware {
public:

    // verifica autenticacao
    static bool isAuthenticated(
        const httplib::Request& req,
        httplib::Response& res
    );

    // extrai Bearer Token
    static std::string extractToken(
        const httplib::Request& req
    );

    // valida token
    static bool validateToken(
        const std::string& token
    );
};

#endif