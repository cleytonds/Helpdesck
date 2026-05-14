#pragma once

#include <string>

// ======================================================
// MODEL: Ticket
// ======================================================
struct Ticket {

    int id = 0;

    std::string title;
    std::string description;

    // baixa | media | alta
    std::string priority;

    // aberto | andamento | resolvido
    std::string status;

    int userId = 0;

    // ==================================================
    // Dados do usuário
    // ==================================================
    std::string user_name;
    std::string user_email;
};