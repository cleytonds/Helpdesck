#include "JWTMiddleware.h"

bool JWTMiddleware::validateToken(const std::string& token)
{
    if(token.empty())
    {
        return false;
    }

    return true;
}