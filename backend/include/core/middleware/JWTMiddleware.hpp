#ifndef JWT_MIDDLEWARE_HPP
#define JWT_MIDDLEWARE_HPP

#include <string>
#include "httplib.h"
#include "core/server/JWTService.hpp"

// ======================================================
// JWT Middleware
// ======================================================
class JWTMiddleware {
public:
    static bool authenticate(const httplib::Request& req, JWTPayload& payload);

    template<typename NextFunc>
    static void createHandler(NextFunc next) {
        // reservado para framework futuro
    }
};

#endif