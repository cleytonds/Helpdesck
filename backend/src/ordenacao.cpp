#include "ordenacao.h"
#include "../include/api.h"
#include "../include/database.h"

// Bubble Sort simples (didático)
void ordenarPorPrioridade(Requisicao* arr[], int n) {

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {

            if (arr[j]->prioridade < arr[j + 1]->prioridade) {
                Requisicao* temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}