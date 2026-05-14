#ifndef ABB_H
#define ABB_H

#include "models/Ticket.hpp"

struct ABBNode {
    Ticket data;
    ABBNode* left;
    ABBNode* right;
};

class ABB {
public:
    ABB();

    void inserir(Ticket t);
    void listar();

private:
    ABBNode* raiz;

    ABBNode* inserirRec(ABBNode* no, Ticket t);
    void inOrderRec(ABBNode* no);
};

#endif