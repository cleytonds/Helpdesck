#ifndef FILA_REQUISICOES_HPP
#define FILA_REQUISICOES_HPP

#include "models/Requisicao.hpp"

class FilaRequisicoes {

private:
    struct No {
        Requisicao dado;
        No* prox;

        No(Requisicao r) : dado(r), prox(nullptr) {}
    };

    No* inicio;
    No* fim;

public:
    FilaRequisicoes();
    ~FilaRequisicoes();

    void enfileirar(Requisicao r);
    Requisicao desenfileirar();
    bool vazia();
    void imprimir();
};

#endif