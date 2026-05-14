#include "core/middleware/JWTMiddleware.hpp"

bool JWTMiddleware::authenticate(const httplib::Request& req, JWTPayload& payload)
{
    std::string token = JWTService::extractFromHeader(req);

    if (token.empty()) {
        return false;
    }

    return JWTService::validateToken(token, payload);
}