#include "fila.h"
#include <iostream>
#include "../include/api.h"
#include "../include/database.h"

using namespace std;

Fila::Fila() {
    inicio = fim = nullptr;
}

// entra na fila
void Fila::enfileirar(Requisicao* r) {

    r->prox = nullptr;

    if (!fim) {
        inicio = fim = r;
        return;
    }

    fim->prox = r;
    fim = r;
}

// sai da fila
Requisicao* Fila::desenfileirar() {

    if (!inicio) return nullptr;

    Requisicao* r = inicio;
    inicio = inicio->prox;

    if (!inicio)
        fim = nullptr;

    return r;
}

// listar fila
void Fila::listar() {

    Requisicao* aux = inicio;

    cout << "\n=== FILA DE ATENDIMENTO ===\n";

    while (aux) {
        cout << aux->usuario << " - prioridade: " << aux->prioridade << endl;
        aux = aux->prox;
    }
}