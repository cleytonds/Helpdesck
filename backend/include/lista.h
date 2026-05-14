#ifndef LISTA_DUPLA_H
#define LISTA_DUPLA_H

#include "models/Ticket.hpp"
#include <vector>

struct ListaNode {
    Ticket data;
    ListaNode* prox;
};

class Lista {

private:
    ListaNode* inicio;

public:
    Lista();

    void inserir(Ticket t);
    void remover(int id);
    std::vector<Ticket> listar();
};

#endif