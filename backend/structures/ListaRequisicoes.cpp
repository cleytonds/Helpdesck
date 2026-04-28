#include "ListaRequisicoes.hpp"
#include <iostream>

ListaRequisicoes::ListaRequisicoes() {
    inicio = nullptr;
    fim = nullptr;
}

ListaRequisicoes::~ListaRequisicoes() {
    Requisicao* atual = inicio;

    while (atual != nullptr) {
        Requisicao* prox = atual->prox;
        delete atual;
        atual = prox;
    }
}

bool ListaRequisicoes::vazia() {
    return inicio == nullptr;
}

void ListaRequisicoes::adicionar(Requisicao r) {
    Requisicao* novo = new Requisicao(r);

    if (vazia()) {
        inicio = fim = novo;
    } else {
        fim->prox = novo;
        novo->ant = fim;
        fim = novo;
    }
}

Requisicao* ListaRequisicoes::buscarPorId(int id) {
    Requisicao* atual = inicio;

    while (atual != nullptr) {
        if (atual->id == id) {
            return atual;
        }
        atual = atual->prox;
    }

    return nullptr;
}

void ListaRequisicoes::remover(int id) {
    Requisicao* atual = buscarPorId(id);

    if (!atual) return;

    if (atual->ant)
        atual->ant->prox = atual->prox;
    else
        inicio = atual->prox;

    if (atual->prox)
        atual->prox->ant = atual->ant;
    else
        fim = atual->ant;

    delete atual;
}

void ListaRequisicoes::imprimirFrente() {
    Requisicao* atual = inicio;

    while (atual != nullptr) {
        std::cout << "ID: " << atual->id
                  << " Usuario: " << atual->usuario
                  << " Prioridade: " << atual->prioridade
                  << std::endl;

        atual = atual->prox;
    }
}

void ListaRequisicoes::imprimirTras() {
    Requisicao* atual = fim;

    while (atual != nullptr) {
        std::cout << "ID: " << atual->id
                  << " Usuario: " << atual->usuario
                  << " Prioridade: " << atual->prioridade
                  << std::endl;

        atual = atual->ant;
    }
}