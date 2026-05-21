#ifndef TICKETMANAGER_HPP
#define TICKETMANAGER_HPP

#include <vector>
#include <string>
#include "models/Requisicao.hpp"

class TicketManager {
private:
    std::vector<Requisicao> tickets;

public:
    TicketManager();

    void adicionar(const Requisicao& req);

    std::vector<Requisicao> listar() const;

    int totalTickets() const;
};

#endif