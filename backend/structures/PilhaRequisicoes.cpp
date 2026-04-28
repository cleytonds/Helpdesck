#include "PilhaRequisicoes.hpp"
#include <iostream>
#include <stdexcept>

PilhaRequisicoes::PilhaRequisicoes() {
    topo = nullptr;
}

PilhaRequisicoes::~PilhaRequisicoes() {
    while (!vazia()) {
        desempilhar();
    }
}

bool PilhaRequisicoes::vazia() {
    return topo == nullptr;
}

void PilhaRequisicoes::empilhar(Requisicao r) {
    No* novo = new No(r);

    novo->prox = topo;
    topo = novo;
}

Requisicao PilhaRequisicoes::desempilhar() {
    if (vazia()) {
        throw std::runtime_error("Pilha vazia");
    }

    No* temp = topo;
    Requisicao r = temp->dado;

    topo = topo->prox;
    delete temp;

    return r;
}

Requisicao PilhaRequisicoes::verTopo() {
    if (vazia()) {
        throw std::runtime_error("Pilha vazia");
    }

    return topo->dado;
}

void PilhaRequisicoes::imprimir() {
    No* atual = topo;

    while (atual != nullptr) {
        std::cout << "ID: " << atual->dado.id
                  << " Usuario: " << atual->dado.usuario
                  << " Prioridade: " << atual->dado.prioridade
                  << std::endl;

        atual = atual->prox;
    }
}