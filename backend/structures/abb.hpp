#pragma once
#include "../models/Ticket.hpp"

struct NodeABB {
    Ticket ticket;
    NodeABB* left;
    NodeABB* right;
};

class ABB {
private:
    NodeABB* root = nullptr;

    NodeABB* inserir(NodeABB* node, Ticket t) {
        if (!node) return new NodeABB{t, nullptr, nullptr};

        if (t.prioridade < node->ticket.prioridade)
            node->left = inserir(node->left, t);
        else
            node->right = inserir(node->right, t);

        return node;
    }

public:
    void inserir(Ticket t) {
        root = inserir(root, t);
    }
};