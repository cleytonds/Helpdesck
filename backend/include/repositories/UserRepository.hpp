#pragma once

#include <mysql/mysql.h>
#include <string>
#include <optional>
#include <vector>
#include "services/AuthService.hpp"

// ======================================================
// MODEL USER
// Representa entidade de usuário no sistema
// ======================================================
struct User {
    int id;
    std::string name;
    std::string email;
    std::string password; // armazena password_hash
    std::string role;
    bool active;
};

// ======================================================
// USER REPOSITORY
// Responsável pelo acesso ao banco de dados (users)
// ======================================================
class UserRepository {
private:
    MYSQL* conn;

public:
    // ==================================================
    // CONSTRUCTOR
    // ==================================================
    explicit UserRepository(MYSQL* c);

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