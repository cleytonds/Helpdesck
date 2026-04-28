#ifndef IMIDDLEWARE_HPP
#define IMIDDLEWARE_HPP

#include "../../include/httplib.h"

// ===========================================
// Interface para middleware HTTP
// Inspirada em NestJS/Express middleware pipeline
// ===========================================
class IMiddleware {
public:
    virtual ~IMiddleware() = default;

    virtual void before(const httplib::Request& req, httplib::Response& res) = 0;
    virtual void after(const httplib::Request& req, httplib::Response& res) {}
};

#endif // IMIDDLEWARE_HPP

