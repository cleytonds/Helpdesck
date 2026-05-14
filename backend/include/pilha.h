#ifndef PILHA_H
#define PILHA_H

#include "models/Ticket.hpp"

struct PilhaNode {
    Ticket data;
    PilhaNode* prox;
};

class Pilha {

private:
    PilhaNode* topo;

public:
    Pilha();

    void push(Ticket t);
    Ticket pop();
    void listar();
};

#endif