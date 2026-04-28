#include "ArvoreRequisicoes.hpp"
#include <iostream>

ArvoreRequisicoes::ArvoreRequisicoes() {
    raiz = nullptr;
}

ArvoreRequisicoes::~ArvoreRequisicoes() {
    destruir(raiz);
}

void ArvoreRequisicoes::destruir(No* no) {
    if (no == nullptr) return;

    destruir(no->esquerda);
    destruir(no->direita);
    delete no;
}

ArvoreRequisicoes::No* ArvoreRequisicoes::inserir(No* no, Requisicao r) {
    if (no == nullptr)
        return new No(r);

    // PRIORIDADE (árvore ordenada)
    if (r.prioridade < no->dado.prioridade)
        no->esquerda = inserir(no->esquerda, r);
    else
        no->direita = inserir(no->direita, r);

    return no;
}

void ArvoreRequisicoes::inserir(Requisicao r) {
    raiz = inserir(raiz, r);
}

void ArvoreRequisicoes::emOrdem(No* no) {
    if (no == nullptr) return;

    emOrdem(no->esquerda);

    std::cout << "ID: " << no->dado.id
              << " Usuario: " << no->dado.usuario
              << " Prioridade: " << no->dado.prioridade
              << std::endl;

    emOrdem(no->direita);
}

void ArvoreRequisicoes::imprimirOrdenado() {
    emOrdem(raiz);
}

ArvoreRequisicoes::No* ArvoreRequisicoes::buscar(No* no, int id) {
    if (no == nullptr) return nullptr;

    if (no->dado.id == id)
        return no;

    No* esquerda = buscar(no->esquerda, id);
    if (esquerda != nullptr) return esquerda;

    return buscar(no->direita, id);
}

Requisicao* ArvoreRequisicoes::buscar(int id) {
    No* resultado = buscar(raiz, id);
    return resultado ? &resultado->dado : nullptr;
}