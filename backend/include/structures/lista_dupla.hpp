#pragma once
#include "../models/Ticket.hpp"

#include <vector>

struct Node {
    Ticket data;
    Node* prev;
    Node* next;
};

class ListaDupla {
private:
    Node* head = nullptr;

public:
    void adicionar(const Ticket& t) {
        Node* novo = new Node{t, nullptr, head};

        if (head) head->prev = novo;

        head = novo;
    }

    // Retorna histórico em memória para o TicketService
    std::vector<Ticket> listar() const {
        std::vector<Ticket> out;
        Node* atual = head;
        while (atual) {
            out.push_back(atual->data);
            atual = atual->next;
        }
        return out;
    }
};

