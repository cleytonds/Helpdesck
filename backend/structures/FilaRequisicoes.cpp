#include "FilaRequisicoes.hpp"
#include <iostream>

FilaRequisicoes::FilaRequisicoes() {
    inicio = nullptr;
    fim = nullptr;
}

FilaRequisicoes::~FilaRequisicoes() {
    while (!vazia()) {
        desenfileirar();
    }
}

bool FilaRequisicoes::vazia() {
    return inicio == nullptr;
}

void FilaRequisicoes::enfileirar(Requisicao r) {
    No* novo = new No(r);

    if (vazia()) {
        inicio = fim = novo;
    } else {
        fim->prox = novo;
        fim = novo;
    }
}

Requisicao FilaRequisicoes::desenfileirar() {
    if (vazia()) {
        throw std::runtime_error("Fila vazia");
    }

    No* temp = inicio;
    Requisicao r = temp->dado;

    inicio = inicio->prox;

    if (inicio == nullptr) {
        fim = nullptr;
    }

    delete temp;
    return r;
}

void FilaRequisicoes::imprimir() {
    No* atual = inicio;

    while (atual != nullptr) {
        std::cout << "ID: " << atual->dado.id
                  << " Usuario: " << atual->dado.usuario
                  << " Prioridade: " << atual->dado.prioridade
                  << std::endl;

        atual = atual->prox;
    }
}