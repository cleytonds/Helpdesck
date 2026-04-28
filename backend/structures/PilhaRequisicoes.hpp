#ifndef PILHA_REQUISICOES_HPP
#define PILHA_REQUISICOES_HPP

#include "../models/Requisicao.hpp"

class PilhaRequisicoes {

private:
    struct No {
        Requisicao dado;
        No* prox;

        No(Requisicao r) : dado(r), prox(nullptr) {}
    };

    No* topo;

public:
    PilhaRequisicoes();
    ~PilhaRequisicoes();

    void empilhar(Requisicao r);
    Requisicao desempilhar();
    Requisicao verTopo();
    bool vazia();
    void imprimir();
};

#endif