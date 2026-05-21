#include "services/TicketService.hpp"

#include <algorithm>

// ======================================================
// CONSTRUCTOR
// ======================================================
TicketService::TicketService(TicketRepository& ticketRepo)
    : ticketRepo_(ticketRepo) {}

// ======================================================
// GET ALL TICKETS (ADMIN/GERAL) - apenas ativos
// ======================================================
std::vector<Ticket> TicketService::getAllTickets() const {
    auto tickets = ticketRepo_.findAll();

    std::vector<Ticket> ativos;
    for (const auto& t : tickets) {
        if (
            t.status == "aberto" ||
            t.status == "andamento" ||
            t.status == "reaberto"
        ) {
            ativos.push_back(t);
        }
    }

    return ativos;
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
    if (!req.isValid())
        return false;

    int id = ticketRepo_.create(
        req.title,
        req.description,
        req.priority,
        userId
    );

    if (id <= 0)
        return false;

    Ticket t;
    t.id = id;
    t.title = req.title;
    t.description = req.description;
    t.priority = req.priority;
    t.status = "aberto";
    t.userId = userId;

    filaAtendimento.adicionar(t);
    arvorePrioridade.inserir(t);

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

    if (status == "resolvido") {
        historico.adicionar(t);
        pilhaReabertura.adicionar(t);
    }

    if (status == "reaberto") {
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
// PROCESS NEXT TICKET
// ======================================================
bool TicketService::processNextTicket() {

    if (filaAtendimento.vazia())
        return false;

    Ticket t = filaAtendimento.proximo();
    filaAtendimento.remover();

    t.status = "andamento";

    bool ok = ticketRepo_.updateStatus(
        t.id,
        t.status
    );

    if (!ok)
        return false;

    return true;
}

// ======================================================
// PRIORIDADES
// ======================================================
std::vector<Ticket> TicketService::getTicketsByPriority() {

    auto tickets = ticketRepo_.findAll();

    std::vector<Ticket> ativos;
    for (const auto& t : tickets) {
        if (t.status != "resolvido") {
            ativos.push_back(t);
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
        ativos.begin(),
        ativos.end(),
        [&](const Ticket& a, const Ticket& b) {
            return rank(a.priority) < rank(b.priority);
        }
    );

    return ativos;
}

// ======================================================
// REOPEN LAST TICKET
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
}

// ======================================================
// HISTORY (ADMIN/GLOBAL) - resolvidos
// ======================================================
std::vector<Ticket> TicketService::getHistory() {
    return ticketRepo_.findResolvedTickets();
}

// ======================================================
// MEUS TICKETS (USER)
// ======================================================
std::vector<Ticket> TicketService::getMyActiveTickets(int userId) {
    // SQL filtra: user_id = ? AND status != 'resolvido'
    return ticketRepo_.findTicketsByUserActive(userId);
}

std::vector<Ticket> TicketService::getMyResolvedHistory(int userId) {
    // SQL filtra: user_id = ? AND status = 'resolvido'
    return ticketRepo_.findResolvedTicketsByUser(userId);
}

// ======================================================
// FILA
// ======================================================
std::vector<Ticket> TicketService::getFila() {
    auto tickets = ticketRepo_.findAll();

    std::vector<Ticket> fila;
    for (const auto& t : tickets) {
        if (
            t.status == "aberto" ||
            t.status == "andamento" ||
            t.status == "reaberto"
        ) {
            fila.push_back(t);
        }
    }

    return fila;
}

