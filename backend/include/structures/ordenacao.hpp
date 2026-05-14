#pragma once
#include <vector>
#include <algorithm>
#include "../models/Ticket.hpp"

class Ordenacao {
public:
    static void ordenarPorPrioridade(std::vector<Ticket>& tickets) {
        std::sort(tickets.begin(), tickets.end(), [](Ticket a, Ticket b) {
            return a.prioridade > b.prioridade;
        });
    }
};