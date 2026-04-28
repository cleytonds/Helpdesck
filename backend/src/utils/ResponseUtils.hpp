#ifndef RESPONSEUTILS_HPP
#define RESPONSEUTILS_HPP

#include "../include/httplib.h"
#include "../include/json.hpp"
#include <string>

using json = nlohmann::json;

// ===========================================
// Helpers para responder requisições HTTP
// ===========================================
namespace ResponseUtils {

    inline void setJsonResponse(httplib::Response& res, const json& body, int status = 200) {
        res.status = status;
        res.set_header("Content-Type", "application/json");
        res.set_content(body.dump(), "application/json");
    }

    inline void setCorsHeaders(httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");
    }

} // namespace ResponseUtils

#endif // RESPONSEUTILS_HPP

