#include "lista.h"
#include <iostream>
#include "../include/api.h"
#include "../include/database.h"

using namespace std;

// ==========================
// CONSTRUTOR
// ==========================
ListaDupla::ListaDupla() {
    inicio = nullptr;
}

// ==========================
// INSERIR NO FINAL
// ==========================
void ListaDupla::inserir(Requisicao* r) {

    if (r == nullptr)
        return;

    r->prox = nullptr;
    r->ant = nullptr;

    // lista vazia
    if (inicio == nullptr) {
        inicio = r;
        return;
    }

    // percorre até o final
    Requisicao* aux = inicio;

    while (aux->prox != nullptr) {
        aux = aux->prox;
    }

    aux->prox = r;
    r->ant = aux;
}

// ==========================
// LISTAR REQUISIÇÕES
// ==========================
void ListaDupla::listar() {

    if (inicio == nullptr) {
        cout << "\nLista vazia.\n";
        return;
    }

    Requisicao* aux = inicio;

    cout << "\n=== LISTA DE REQUISICOES ===\n";

    while (aux != nullptr) {

        cout << "ID: " << aux->id << endl;
        cout << "Usuario: " << aux->usuario << endl;
        cout << "Descricao: " << aux->descricao << endl;
        cout << "Prioridade: " << aux->prioridade << endl;
        cout << "-----------------------------" << endl;

        aux = aux->prox;
    }
}

// ==========================
// REMOVER POR ID
// ==========================
void ListaDupla::remover(int id) {

    if (inicio == nullptr)
        return;

    Requisicao* aux = inicio;

    while (aux != nullptr && aux->id != id) {
        aux = aux->prox;
    }

    // não encontrou
    if (aux == nullptr)
        return;

    // remove do início
    if (aux == inicio) {
        inicio = aux->prox;

        if (inicio != nullptr) {
            inicio->ant = nullptr;
        }
    }
    else {

        if (aux->ant != nullptr) {
            aux->ant->prox = aux->prox;
        }

        if (aux->prox != nullptr) {
            aux->prox->ant = aux->ant;
        }
    }

    delete aux;
}