#include "TicketManager.hpp"

void TicketManager::registrar(Requisicao r) {

    // 1. Fila (ordem de chegada)
    fila.enfileirar(r);

    // 2. Lista (histórico completo)
    lista.adicionar(r);

    // 3. Árvore (prioridade)
    arvore.inserir(r);
}

FilaRequisicoes& TicketManager::getFila() {
    return fila;
}

ListaRequisicoes& TicketManager::getLista() {
    return lista;
}

ArvoreRequisicoes& TicketManager::getArvore() {
    return arvore;
}