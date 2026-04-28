#ifndef API_H
#define API_H

#include <string>
#include "core/TicketManager.hpp"

extern TicketManager manager;

// listar chamados
std::string listarRequisicoes(sql::Connection* con);

// criar chamado
void criarRequisicao(
    sql::Connection* con,
    std::string usuario,
    std::string descricao,
    int prioridade
);

// iniciar servidor HTTP
void iniciarServidor();

#endif