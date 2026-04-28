#ifndef LISTA_DUPLA_H
#define LISTA_DUPLA_H

#include "models/Requisicao.hpp"

// ===============================
// Lista de requisições
// ===============================
class ListaDupla {

private:
    Requisicao* inicio;

public:
    ListaDupla();

    void inserir(Requisicao* r);
    void remover(int id);
    void listar();
};

#endif