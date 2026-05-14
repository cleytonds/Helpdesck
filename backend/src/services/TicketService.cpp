#include "services/TicketService.hpp"

#include <algorithm>

// ======================================================
// CONSTRUCTOR
// ======================================================
TicketService::TicketService(TicketRepository& ticketRepo)
    : ticketRepo_(ticketRepo) {}

// ======================================================
// GET ALL TICKETS
// ======================================================
std::vector<Ticket> TicketService::getAllTickets() const {
    return ticketRepo_.findAll();
}

// ======================================================
// GET TICKET BY ID
// ======================================================
std::optional<Ticket> TicketService::getTicketById(int id) const {
    return ticketRepo_.findById(id);
}

// ======================================================
// CREATE TICKET
// ======================================================
bool TicketService::createTicket(const TicketRequest& req, int userId) {
    if (!req.isValid()) return false;

    int id = ticketRepo_.create(
        req.title,
        req.description,
        req.priority,
        userId
    );

    if (id <= 0) return false;

    Ticket t;
    t.id = id;
    t.title = req.title;
    t.description = req.description;
    t.priority = req.priority;
    t.status = "aberto";
    t.userId = userId;

    // =========================================
    // Estruturas em memória
    // =========================================
    filaAtendimento.adicionar(t);
    pilhaReabertura.adicionar(t);
    arvorePrioridade.inserir(t);
    historico.adicionar(t);

    return true;
}

// ======================================================
// UPDATE STATUS
// ======================================================
bool TicketService::updateTicketStatus(
    int id,
    const std::string& status
) {
    auto ticketOpt = ticketRepo_.findById(id);

    if (!ticketOpt)
        return false;

    bool updated = ticketRepo_.updateStatus(id, status);

    if (!updated)
        return false;

    Ticket t = *ticketOpt;
    t.status = status;

    historico.adicionar(t);

    // =========================================
    // Reabertura
    // =========================================
    if (status == "reaberto") {
        pilhaReabertura.adicionar(t);
        filaAtendimento.adicionar(t);
        arvorePrioridade.inserir(t);
    }

    return true;
}

// ======================================================
// DELETE TICKET
// ======================================================
bool TicketService::deleteTicket(int id) {
    return ticketRepo_.remove(id);
}

// ======================================================
// PROCESS NEXT TICKET (FILA)
// ======================================================
bool TicketService::processNextTicket() {

    if (filaAtendimento.vazia())
        return false;

    Ticket t = filaAtendimento.proximo();

    filaAtendimento.remover();

    t.status = "em andamento";

    bool ok = ticketRepo_.updateStatus(
        t.id,
        t.status
    );

    if (!ok)
        return false;

    historico.adicionar(t);

    return true;
}

// ======================================================
// GET TICKETS BY PRIORITY
// ======================================================
std::vector<Ticket> TicketService::getTicketsByPriority() {

    auto tickets = ticketRepo_.findAll();

    auto rank = [](const std::string& p) {

        if (p == "alta")
            return 0;

        if (p == "media" || p == "média")
            return 1;

        if (p == "baixa")
            return 2;

        return 3;
    };

    std::stable_sort(
        tickets.begin(),
        tickets.end(),
        [&](const Ticket& a, const Ticket& b) {
            return rank(a.priority) < rank(b.priority);
        }
    );

    return tickets;
}

// ======================================================
// REOPEN LAST TICKET (PILHA)
// ======================================================
void TicketService::reopenLastTicket() {

    if (pilhaReabertura.vazia())
        return;

    Ticket t = pilhaReabertura.remover();

    t.status = "reaberto";

    ticketRepo_.updateStatus(
        t.id,
        t.status
    );

    filaAtendimento.adicionar(t);

    historico.adicionar(t);
}

// ======================================================
// HISTORY
// ======================================================
std::vector<Ticket> TicketService::getHistory() {
    return historico.listar();
}

// ======================================================
// GET FILA
// ======================================================
std::vector<Ticket> TicketService::getFila() {

    auto tickets = ticketRepo_.findAll();

    std::vector<Ticket> out;

    for (const auto& t : tickets) {

        if (
            t.status == "aberto" ||
            t.status == "em andamento" ||
            t.status == "reaberto"
        ) {
            out.push_back(t);
        }
    }

    auto rank = [](const std::string& p) {

        if (p == "alta")
            return 0;

        if (p == "media" || p == "média")
            return 1;

        if (p == "baixa")
            return 2;

        return 3;
    };

    std::stable_sort(
        out.begin(),
        out.end(),
        [&](const Ticket& a, const Ticket& b) {
            return rank(a.priority) < rank(b.priority);
        }
    );

    return out;
}