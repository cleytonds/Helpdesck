#ifndef REGISTER_REQUEST_HPP
#define REGISTER_REQUEST_HPP

#include <string>
#include <optional>

// ======================================================
// DTO: Requisição de Cadastro
// ======================================================
struct RegisterRequest {
    std::string name;
    std::string email;
    std::string password;

    bool isValid() const {
        return !name.empty() && !email.empty() && !password.empty()
            && email.find('@') != std::string::npos
            && password.length() >= 6;
    }

    std::optional<std::string> validate() const {
        if (name.empty())  return std::optional<std::string>("Nome obrigatorio");
        if (email.empty()) return std::optional<std::string>("Email obrigatorio");
        if (email.find('@') == std::string::npos) return std::optional<std::string>("Email invalido");
        if (password.empty()) return std::optional<std::string>("Senha obrigatoria");
        if (password.length() < 6) return std::optional<std::string>("Senha deve ter no minimo 6 caracteres");
        return std::nullopt;
    }
};

#endif

