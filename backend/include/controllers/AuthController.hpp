#pragma once

#include "services/AuthService.hpp"
#include "dto/LoginRequest.hpp"
#include "dto/RegisterRequest.hpp"
#include "utils/ResponseFactory.hpp"
#include "httplib.h"

// ======================================================
// CONTROLLER AUTH
// ======================================================
class AuthController {
public:
    explicit AuthController(AuthService& service);

    void login(const httplib::Request& req, httplib::Response& res);
    void registerUser(const httplib::Request& req, httplib::Response& res);
    void forgotPassword(const httplib::Request& req, httplib::Response& res);
    void resetPassword(const httplib::Request& req, httplib::Response& res);

private:
    AuthService& authService_;
};