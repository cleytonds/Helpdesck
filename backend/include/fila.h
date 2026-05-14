#ifndef FILA_H
#define FILA_H

#include "models/Ticket.hpp"

struct FilaNode {
    Ticket data;
    FilaNode* prox;
};

class Fila {

private:
    FilaNode* inicio;
    FilaNode* fim;

public:
    Fila();

    void enfileirar(Ticket t);
    Ticket desenfileirar();
    void listar();
};

#endif