#pragma once
#include "../models/Ticket.hpp"

struct Node {
    Ticket data;
    Node* prev;
    Node* next;
};

class ListaDupla {
private:
    Node* head = nullptr;

public:
    void adicionar(Ticket t) {
        Node* novo = new Node{t, nullptr, head};

        if (head) head->prev = novo;

        head = novo;
    }

    void listar() {
        Node* atual = head;

        while (atual) {
            std::cout << atual->data.titulo << std::endl;
            atual = atual->next;
        }
    }
};