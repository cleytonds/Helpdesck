#pragma once

#include <mysql/mysql.h>

#include <optional>
#include <string>

#include "models/User.hpp"

class UserRepository {
private:
    MYSQL* conn_;

public:
    explicit UserRepository(MYSQL* conn);


    // ==================================================
    // BUSCA
    // ==================================================
    
    // Busca usuário por email
    std::optional<User> findByEmail(const std::string& email);

    // ==================================================
    // CREATE
    // ==================================================

    // Cria novo usuário (senha já deve vir com hash)
    bool create(const std::string& name,
                const std::string& email,
                const std::string& password,
                bool active,
                const std::string& role);

    // ==================================================
    // UPDATE
    // ==================================================

    // Atualiza senha (hash)
    bool updatePassword(int userId,
                        const std::string& newPassword);

    // ==================================================
    // VALIDATIONS
    // ==================================================

    // Verifica se email já existe
    bool existsByEmail(const std::string& email);
};