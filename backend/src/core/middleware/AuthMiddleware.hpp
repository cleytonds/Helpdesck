#ifndef AUTH_MIDDLEWARE_HPP
#define AUTH_MIDDLEWARE_HPP

#include "httplib.h"
#include <string>

// ======================================================
// Middleware: Verifica autenticacao (token JWT)
// ======================================================
class AuthMiddleware {
public:
    // Verifica se a requisicao possui header Authorization valido
    static bool isAuthenticated(const httplib::Request& req, httplib::Response& res);

    // Extrai token do header Authorization: Bearer <token>
    static std::string extractToken(const httplib::Request& req);

    // Valida token (placeholder - integrar com JWTService)
    static bool validateToken(const std::string& token);
};

#endif

