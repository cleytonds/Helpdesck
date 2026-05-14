#ifndef ROLE_MIDDLEWARE_HPP
#define ROLE_MIDDLEWARE_HPP

#include "httplib.h"
#include <string>

class RoleMiddleware {
public:

    static bool hasRole(
        const httplib::Request& req,
        httplib::Response& res,
        const std::string& requiredRole
    );

    static bool isAdmin(
        const httplib::Request& req,
        httplib::Response& res
    );
};

#endif