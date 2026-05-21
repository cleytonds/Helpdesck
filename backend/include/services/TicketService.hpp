#ifndef TICKET_SERVICE_HPP
#define TICKET_SERVICE_HPP

#include "repositories/TicketRepository.hpp"
#include "dto/TicketRequest.hpp"

#include "structures/fila.hpp"
#include "structures/pilha.hpp"
#include "structures/abb.hpp"
#include "structures/lista_dupla.hpp"

#include <vector>
#include <optional>
#include <string>

class TicketService {
public:
    explicit TicketService(TicketRepository& ticketRepo);

    // =========================
    // CRUD BASE
    // =========================
    std::vector<Ticket> getAllTickets() const;
    std::optional<Ticket> getTicketById(int id) const;

    bool createTicket(const TicketRequest& req, int userId);
    bool updateTicketStatus(int id, const std::string& status);
    bool deleteTicket(int id);

    // =========================
    // MOTOR (ADMIN/GERAL)
    // =========================
    bool processNextTicket();
    std::vector<Ticket> getTicketsByPriority();
    void reopenLastTicket();
    std::vector<Ticket> getHistory();
    std::vector<Ticket> getFila();

    // =========================
    // MEUS TICKETS (USER)
    // =========================
    std::vector<Ticket> getMyActiveTickets(int userId);
    std::vector<Ticket> getMyResolvedHistory(int userId);

private:
    TicketRepository& ticketRepo_;

    // =========================
    // ESTRUTURAS DO MOTOR
    // =========================
    FilaTickets filaAtendimento;
    PilhaTickets pilhaReabertura;
    ABB arvorePrioridade;
    ListaDupla historico;
};

#endif

