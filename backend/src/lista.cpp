#include "lista.h"
#include <iostream>

using namespace std;

Lista::Lista() {
    inicio = nullptr;
}

// inserir
void Lista::inserir(Ticket t) {

    ListaNode* novo = new ListaNode();
    novo->data = t;
    novo->prox = nullptr;

    if (!inicio) {
        inicio = novo;
        return;
    }

    ListaNode* aux = inicio;

    while (aux->prox)
        aux = aux->prox;

    aux->prox = novo;
}

// listar
std::vector<Ticket> Lista::listar() {

    std::vector<Ticket> out;

    ListaNode* aux = inicio;

    while (aux) {
        out.push_back(aux->data);
        aux = aux->prox;
    }

    return out;
}

// remover
void Lista::remover(int id) {

    if (!inicio) return;

    ListaNode* aux = inicio;
    ListaNode* ant = nullptr;

    while (aux && aux->data.id != id) {
        ant = aux;
        aux = aux->prox;
    }

    if (!aux) return;

    if (!ant)
        inicio = aux->prox;
    else
        ant->prox = aux->prox;

    delete aux;
}