#ifndef LOGIN_REQUEST_HPP
#define LOGIN_REQUEST_HPP

#include <string>
#include <optional>

// ======================================================
// DTO: Requisição de Login
// ======================================================
struct LoginRequest {
    std::string email;
    std::string password;

    // Validação básica do DTO
    bool isValid() const {
        return !email.empty() && !password.empty() && email.find('@') != std::string::npos;
    }

    std::optional<std::string> validate() const {
        if (email.empty()) return std::optional<std::string>("Email obrigatorio");
        if (password.empty()) return std::optional<std::string>("Senha obrigatoria");
        if (email.find('@') == std::string::npos) return std::optional<std::string>("Email invalido");
        return std::nullopt;
    }
};

#endif

