#include "pilha.h"
#include <iostream>

using namespace std;

Pilha::Pilha() {
    topo = nullptr;
}

// push
void Pilha::push(Ticket t) {

    PilhaNode* novo = new PilhaNode();
    novo->data = t;
    novo->prox = topo;

    topo = novo;
}

// pop
Ticket Pilha::pop() {

    if (!topo) return Ticket();

    PilhaNode* temp = topo;
    Ticket t = temp->data;

    topo = topo->prox;

    delete temp;

    return t;
}

// listar
void Pilha::listar() {

    PilhaNode* aux = topo;

    cout << "\n=== PILHA ===\n";

    while (aux) {
        cout << aux->data.title
             << " prioridade: "
             << aux->data.priority << endl;

        aux = aux->prox;
    }
}