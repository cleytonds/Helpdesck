#ifndef ORDENADOR_REQUISICOES_HPP
#define ORDENADOR_REQUISICOES_HPP

#include "../models/Requisicao.hpp"

class OrdenadorRequisicoes {

public:
    static void ordenarPorPrioridade(Requisicao* lista[], int tamanho);
};

#endif