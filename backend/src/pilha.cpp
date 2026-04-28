#include "pilha.h"
#include <iostream>
#include "../include/api.h"
#include "../include/database.h"

using namespace std;

Pilha::Pilha() {
    topo = nullptr;
}

// empilhar
void Pilha::push(Requisicao* r) {

    r->prox = topo;
    topo = r;
}

// desempilhar
Requisicao* Pilha::pop() {

    if (!topo) return nullptr;

    Requisicao* r = topo;
    topo = topo->prox;

    return r;
}

// listar
void Pilha::listar() {

    Requisicao* aux = topo;

    cout << "\n=== REQUISICOES REABERTAS ===\n";

    while (aux) {
        cout << aux->usuario << endl;
        aux = aux->prox;
    }
}