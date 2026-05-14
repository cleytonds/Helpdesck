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

// ======================================================
// SERVICE (MOTOR DO HELP DESK)
// ======================================================
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
    // MOTOR
    // =========================
    bool processNextTicket();                 // fila -> processa (operação única)
    std::vector<Ticket> getTicketsByPriority();
    void reopenLastTicket();                 // pilha
    std::vector<Ticket> getHistory();

    std::vector<Ticket> getFila();

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

