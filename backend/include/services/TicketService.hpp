#ifndef TICKET_SERVICE_HPP
#define TICKET_SERVICE_HPP

#include "repositories/TicketRepository.hpp"
#include "dto/TicketRequest.hpp"

#include "fila.h"
#include "pilha.h"
#include "abb.h"
#include "lista.h"

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
    // Observação importante:
    // - Fila/Pilha/ABB/Lista NÃO possuem API de iteração para retorno.
    // - Portanto, o serviço usa o DB (repository) como fonte de verdade.
    // - As estruturas são usadas como motor/estado em memória.
    Fila filaAtendimento;
    Pilha pilhaReabertura;
    ABB arvorePrioridade;
    Lista historico;
};

#endif

