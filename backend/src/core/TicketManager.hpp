#ifndef TICKET_MANAGER_HPP
#define TICKET_MANAGER_HPP

#include "FilaRequisicoes.hpp"
#include "ListaRequisicoes.hpp"
#include "ArvoreRequisicoes.hpp"
#include "Requisicao.hpp"

class TicketManager {

private:
    FilaRequisicoes fila;
    ListaRequisicoes lista;
    ArvoreRequisicoes arvore;

public:
    void registrar(Requisicao r);

    FilaRequisicoes& getFila();
    ListaRequisicoes& getLista();
    ArvoreRequisicoes& getArvore();
};

#endif