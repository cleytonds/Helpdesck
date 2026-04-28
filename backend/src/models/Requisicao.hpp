#ifndef REQUISICAO_HPP
#define REQUISICAO_HPP

#include <string>

// ===========================================
// Entidade de domínio: Requisicao (Ticket)
// ===========================================
struct Requisicao {
    int         id;
    std::string usuario;
    std::string descricao;
    int         prioridade;

    // Ponteiros para estruturas de dados encadeadas (lista dupla)
    Requisicao* prox;
    Requisicao* ant;

    Requisicao()
        : id(0)
        , usuario("")
        , descricao("")
        , prioridade(1)
        , prox(nullptr)
        , ant(nullptr) {}

    Requisicao(int pId, std::string pUsuario, std::string pDescricao, int pPrioridade)
        : id(pId)
        , usuario(std::move(pUsuario))
        , descricao(std::move(pDescricao))
        , prioridade(pPrioridade)
        , prox(nullptr)
        , ant(nullptr) {}
};

#endif // REQUISICAO_HPP

