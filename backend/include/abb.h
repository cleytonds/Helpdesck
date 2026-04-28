#ifndef ABB_H
#define ABB_H

#include <iostream>
#include "models/Requisicao.hpp"

class ABB {
public:
    ABB();

    void inserir(Requisicao* r);
    void inOrder(Requisicao* no);
    void listar();

private:
    Requisicao* raiz;
    Requisicao* inserirRec(Requisicao* no, Requisicao* r);
};

#endif