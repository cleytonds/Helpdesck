#ifndef LISTA_REQUISICOES_HPP
#define LISTA_REQUISICOES_HPP

#include "models/Requisicao.hpp"

class ListaRequisicoes {

private:
    Requisicao* inicio;
    Requisicao* fim;

public:
    ListaRequisicoes();
    ~ListaRequisicoes();

    void adicionar(Requisicao r);
    Requisicao* buscarPorId(int id);
    void remover(int id);

    void imprimirFrente();
    void imprimirTras();

    bool vazia();
};

#endif