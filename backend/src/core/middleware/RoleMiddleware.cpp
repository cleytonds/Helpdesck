#include "core/middleware/RoleMiddleware.hpp"
#include "core/server/JWTService.hpp"
#include "core/middleware/AuthMiddleware.hpp"

// ======================================================
// VERIFICA ROLE DO USUÁRIO
// ======================================================
bool RoleMiddleware::hasRole(const httplib::Request& req,
                             httplib::Response& res,
                             const std::string& requiredRole)
{
    JWTPayload payload;

    // ==============================
    // 1. EXTRAI TOKEN
    // ==============================
    std::string token = AuthMiddleware::extractToken(req);

    if (token.empty()) {
        res.status = 401;
        res.set_content(
            R"({"success":false,"message":"Token nao fornecido"})",
            "application/json"
        );
        return false;
    }

    // ==============================
    // 2. VALIDA TOKEN JWT
    // ==============================
    if (!JWTService::validateToken(token, payload)) {
        res.status = 401;
        res.set_content(
            R"({"success":false,"message":"Token invalido ou expirado"})",
            "application/json"
        );
        return false;
    }

    // ==============================
    // 3. VALIDA ROLE
    // ==============================
    if (payload.role.empty()) {
        res.status = 403;
        res.set_content(
            R"({"success":false,"message":"Role nao definida no token"})",
            "application/json"
        );
        return false;
    }

    if (payload.role != requiredRole) {
        res.status = 403;
        res.set_content(
            R"({"success":false,"message":"Acesso negado"})",
            "application/json"
        );
        return false;
    }

    return true;
}

// ======================================================
// ATALHO: ADMIN
// ======================================================
bool RoleMiddleware::isAdmin(const httplib::Request& req,
                             httplib::Response& res)
{
    return hasRole(req, res, "admin");
}