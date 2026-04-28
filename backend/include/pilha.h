#ifndef PILHA_H
#define PILHA_H

#include "requisicao.h"

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