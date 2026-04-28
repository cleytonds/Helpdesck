#include "OrdenadorRequisicoes.hpp"

void OrdenadorRequisicoes::ordenarPorPrioridade(Requisicao* lista[], int tamanho) {

    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = 0; j < tamanho - i - 1; j++) {

            if (lista[j]->prioridade < lista[j + 1]->prioridade) {

                Requisicao* temp = lista[j];
                lista[j] = lista[j + 1];
                lista[j + 1] = temp;
            }
        }
    }
}