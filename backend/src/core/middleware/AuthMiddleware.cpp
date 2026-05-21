#include "core/middleware/AuthMiddleware.hpp"


// ======================================================
// VERIFICAR AUTENTICACAO
// ======================================================
bool AuthMiddleware::isAuthenticated(const httplib::Request& req, httplib::Response& res) {
    std::string token = extractToken(req);

    if (token.empty()) {
    res.status = 401;
    res.set_content(R"({"success":false,"message":"Token nao fornecido"})", "application/json");
    return false;
    }

    if (!validateToken(token)) {
        res.status = 401;
        res.set_content(R"({"success":false,"message":"Token invalido ou expirado"})", "application/json");
        return false;
    }

    return true;
}

// ======================================================
// EXTRAIR TOKEN DO HEADER
// ======================================================
std::string AuthMiddleware::extractToken(const httplib::Request& req) {
    auto it = req.headers.find("Authorization");
    if (it == req.headers.end()) {
        return "";
    }

    const std::string& auth = it->second;
    const std::string prefix = "Bearer ";

    if (auth.rfind(prefix, 0) == 0) {
        return auth.substr(prefix.length());
    }

    return "";
}

// ======================================================
// VALIDAR TOKEN (PLACEHOLDER)
// Futuramente integrar com JWTService::verifyToken()
// ======================================================
bool AuthMiddleware::validateToken(const std::string& token) {
    // Placeholder: aceita qualquer token nao-vazio com prefixo valido
    // Substituir por JWTService::verifyToken() quando possivel
    return !token.empty() && token.length() > 10;
}

