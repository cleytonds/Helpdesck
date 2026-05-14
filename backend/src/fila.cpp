#include "fila.h"
#include <iostream>

using namespace std;

Fila::Fila() {
    inicio = fim = nullptr;
}

// entra na fila
void Fila::enfileirar(Ticket t) {

    FilaNode* novo = new FilaNode();
    novo->data = t;
    novo->prox = nullptr;

    if (!fim) {
        inicio = fim = novo;
        return;
    }

    fim->prox = novo;
    fim = novo;
}

// sai da fila
Ticket Fila::desenfileirar() {

    if (!inicio) return Ticket();

    FilaNode* temp = inicio;
    Ticket t = temp->data;

    inicio = inicio->prox;

    if (!inicio)
        fim = nullptr;

    delete temp;

    return t;
}

// listar
void Fila::listar() {

    FilaNode* aux = inicio;

    cout << "\n=== FILA ===\n";

    while (aux) {
        cout << aux->data.title
             << " prioridade: "
             << aux->data.priority << endl;

        aux = aux->prox;
    }
}