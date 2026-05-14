#pragma once
#include <string>

struct Ticket {
    int id;
    std::string titulo;
    std::string descricao;
    std::string usuario;
    std::string prioridade; // baixa, media, alta
    std::string status;
};