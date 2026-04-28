#ifndef ARVORE_REQUISICOES_HPP
#define ARVORE_REQUISICOES_HPP

#include "models/Requisicao.hpp"

class ArvoreRequisicoes {

private:
    struct No {
        Requisicao dado;
        No* esquerda;
        No* direita;

        No(Requisicao r)
            : dado(r), esquerda(nullptr), direita(nullptr) {}
    };

    No* raiz;

    No* inserir(No* no, Requisicao r);
    void emOrdem(No* no);
    No* buscar(No* no, int id);

public:
    ArvoreRequisicoes();
    ~ArvoreRequisicoes();

    void inserir(Requisicao r);
    Requisicao* buscar(int id);
    void imprimirOrdenado();
    void destruir(No* no);
};

#endif