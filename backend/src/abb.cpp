#include "abb.h"
#include <iostream>

using namespace std;

ABB::ABB() {
    raiz = nullptr;
}

// inserir
ABBNode* ABB::inserirRec(ABBNode* no, Ticket t) {

    if (!no) {
        ABBNode* novo = new ABBNode();
        novo->data = t;
        novo->left = nullptr;
        novo->right = nullptr;
        return novo;
    }

    if (t.priority < no->data.priority)
        no->left = inserirRec(no->left, t);
    else
        no->right = inserirRec(no->right, t);

    return no;
}

void ABB::inserir(Ticket t) {
    raiz = inserirRec(raiz, t);
}

// ordem
void ABB::inOrderRec(ABBNode* no) {

    if (!no) return;

    inOrderRec(no->left);

    cout << no->data.title
         << " prioridade: "
         << no->data.priority << endl;

    inOrderRec(no->right);
}

void ABB::listar() {
    cout << "\n=== ARVORE PRIORIDADE ===\n";
    inOrderRec(raiz);
}