#include "core/TicketManager.hpp"

TicketManager::TicketManager() {}

void TicketManager::adicionar(const Requisicao& req) {
    tickets.push_back(req);
}

std::vector<Requisicao> TicketManager::listar() const {
    return tickets;
}

int TicketManager::totalTickets() const {
    return tickets.size();
}