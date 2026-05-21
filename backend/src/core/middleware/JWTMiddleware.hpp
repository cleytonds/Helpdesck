#pragma once

#include <string>

class JWTMiddleware {
public:
    static bool validateToken(const std::string& token);
};