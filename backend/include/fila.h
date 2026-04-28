#ifndef FILA_H
#define FILA_H

#include "models/Requisicao.hpp"

class Fila {

private:
    Requisicao* inicio;
    Requisicao* fim;

public:
    Fila();

    void enfileirar(Requisicao* r);
    Requisicao* desenfileirar();
    void listar();
};

#endif