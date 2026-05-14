#ifndef RESPONSE_FACTORY_HPP
#define RESPONSE_FACTORY_HPP

#include <string>
#include "json.hpp"

using json = nlohmann::json;

// ======================================================
// Response Factory
// Utility para criar respostas JSON padronizadas
// Estilo Express.js
// ======================================================
class ResponseFactory {
public:
    // ======================================================
    // Resposta de sucesso
    // ======================================================
    static json success(const std::string& message, const json& data = nullptr) {
        json response;
        response["success"] = true;
        response["message"] = message;
        if (!data.is_null()) {
            response["data"] = data;
        }
        return response;
    }

    // ======================================================
    // Resposta de erro
    // ======================================================
    static json error(const std::string& message, int statusCode = 400) {
        json response;
        response["success"] = false;
        response["message"] = message;
        response["code"] = statusCode;
        return response;
    }

    // ======================================================
    // Resposta de não encontrado
    // ======================================================
    static json notFound(const std::string& message = "Resource not found") {
        return error(message, 404);
    }

    // ======================================================
    // Resposta não autorizado
    // ======================================================
    static json unauthorized(const std::string& message = "Unauthorized") {
        return error(message, 401);
    }

    // ======================================================
    // Resposta proibido
    // ======================================================
    static json forbidden(const std::string& message = "Forbidden") {
        return error(message, 403);
    }

    // ======================================================
    // Resposta erro interno
    // ======================================================
    static json internalError(const std::string& message = "Internal server error") {
        return error(message, 500);
    }

    // ======================================================
    // Resposta válido
    // ======================================================
    static json badRequest(const std::string& message = "Bad request") {
        return error(message, 400);
    }
};

#endif
