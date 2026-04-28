#include "../include/abb.h"
#include "../include/requisicao.h"
#include <iostream>

using namespace std;

ABB::ABB() {
    raiz = nullptr;
}

// inserir por prioridade
Requisicao* ABB::inserirRec(Requisicao* no, Requisicao* r) {

    if (!no) return r;

    if (r->prioridade < no->prioridade)
        no->ant = inserirRec(no->ant, r);
    else
        no->prox = inserirRec(no->prox, r);

    return no;
}

void ABB::inserir(Requisicao* r) {
    raiz = inserirRec(raiz, r);
}

// ordem (prioridade)
void ABB::inOrder(Requisicao* no) {

    if (!no) return;

    inOrder(no->ant);

    cout << "Usuario: " << no->usuario << " prioridade: " << no->prioridade << endl;

    inOrder(no->prox);
}

void ABB::listar() {
    cout << "\n=== ARVORE DE PRIORIDADE ===\n";
    inOrder(raiz);
}