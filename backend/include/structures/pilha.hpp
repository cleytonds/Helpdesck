#pragma once
#include <stack>
#include "../models/Ticket.hpp"

class PilhaTickets {
private:
    std::stack<Ticket> pilha;

public:
    void adicionar(const Ticket& t) {
        pilha.push(t);
    }

    Ticket remover() {
        Ticket t = pilha.top();
        pilha.pop();
        return t;
    }

    bool vazia() {
        return pilha.empty();
    }
};