#ifndef REQUISICAO_HPP
#define REQUISICAO_HPP

#include <string>

// ===============================
// Entidade de domínio (Ticket)
// ===============================
struct Requisicao {

    int id;
    std::string usuario;
    std::string descricao;
    int prioridade;

    Requisicao()
        : id(0),
          usuario(""),
          descricao(""),
          prioridade(1) {}

    Requisicao(int pId, std::string pUsuario, std::string pDescricao, int pPrioridade)
        : id(pId),
          usuario(std::move(pUsuario)),
          descricao(std::move(pDescricao)),
          prioridade(pPrioridade) {}
};

#endif