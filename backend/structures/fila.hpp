#pragma once
#include <queue>
#include "../models/Ticket.hpp"

class FilaTickets {
private:
    std::queue<Ticket> fila;

public:
    void adicionar(const Ticket& t) {
        fila.push(t);
    }

    void remover() {
        if (!fila.empty()) fila.pop();
    }

    Ticket proximo() {
        return fila.front();
    }

    bool vazia() {
        return fila.empty();
    }
};