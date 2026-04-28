#ifndef PILHA_H
#define PILHA_H

#include "models/Requisicao.hpp"

class Pilha {

private:
    Requisicao* topo;

public:
    Pilha();

    void push(Requisicao* r);
    Requisicao* pop();
    void listar();
};

#endif