#include "controllers/AuthController.hpp"
#include "json.hpp"

using json = nlohmann::json;

// ======================================================
// CONSTRUTOR
// ======================================================
AuthController::AuthController(AuthService& service)
    : authService_(service) {}

// ======================================================
// LOGIN
// ======================================================
void AuthController::login(const httplib::Request& req, httplib::Response& res) {

    json body;

    try {
        body = json::parse(req.body);
    } catch (...) {
        res.status = 400;
        res.set_content(R"({"success":false,"message":"Invalid JSON"})", "application/json");
        return;
    }

    LoginRequest loginReq;
    loginReq.email = body["email"];
    loginReq.password = body["password"];

    AuthResult result = authService_.login(loginReq);

    json response;

    response["success"] = result.success;
    response["message"] = result.message;

    //  SÓ ENVIA USER SE LOGIN OK
    if (result.success) {
        response["token"] = result.token;

        response["user"] = {
            {"id", result.userId},
            {"name", result.name},
            {"email", result.email},
            {"role", result.role}
        };
    }

    res.status = result.success ? 200 : 401;
    res.set_content(response.dump(), "application/json");
}

// ======================================================
// REGISTER
// ======================================================
void AuthController::registerUser(const httplib::Request& req, httplib::Response& res) {

    json body;

    try {
        body = json::parse(req.body);
    } catch (...) {
        res.status = 400;
        res.set_content("{\"success\":false,\"message\":\"Invalid JSON\"}", "application/json");
        return;
    }

    RegisterRequest regReq;
    regReq.name = body["name"];
    regReq.email = body["email"];
    regReq.password = body["password"];

    AuthResult result = authService_.registerUser(regReq);

    json response = {
        {"success", result.success},
        {"message", result.message}
    };

    res.set_content(response.dump(), "application/json");
}

// ======================================================
// FORGOT PASSWORD
// ======================================================
void AuthController::forgotPassword(const httplib::Request& req, httplib::Response& res) {

    json body = json::parse(req.body);

    std::string email = body["email"];

    AuthResult result = authService_.forgotPassword(email);

    json response = {
        {"success", result.success},
        {"message", result.message},
        {"token", result.token} // só debug
    };

    res.set_content(response.dump(), "application/json");
}

// ======================================================
