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

    int id = ticketRepo_.create(req.title, req.description, req.priority, userId);
    if (id <= 0) return false;

    Ticket t;
    t.id = id;
    t.title = req.title;
    t.description = req.description;
    t.priority = req.priority;
    t.status = "aberto";
    t.userId = userId;

    // Motor em memória (sincronizado com a criação)
    filaAtendimento.enfileirar(t);
    arvorePrioridade.inserir(t);
    historico.inserir(t);

    return true;
}

// ======================================================
// UPDATE STATUS
// ======================================================
bool TicketService::updateTicketStatus(int id, const std::string& status) {
    auto ticketOpt = ticketRepo_.findById(id);
    if (!ticketOpt) return false;

    if (!ticketRepo_.updateStatus(id, status)) return false;

    Ticket t = *ticketOpt;
    t.status = status;

    // Histórico em memória
    historico.inserir(t);

    // Reabertura: reintroduz no fluxo (fila + prioridade)
    if (status == "reaberto") {
        pilhaReabertura.push(t);
        filaAtendimento.enfileirar(t);
        arvorePrioridade.inserir(t);
    }

    return true;
}

// ======================================================
// DELETE
// ======================================================
bool TicketService::deleteTicket(int id) {
    return ticketRepo_.remove(id);
}

// ======================================================
// PROCESSAR PRÓXIMO TICKET (FILA)
// ======================================================
bool TicketService::processNextTicket() {
    Ticket t = filaAtendimento.desenfileirar();

    // Heurística: Fila vazia retorna Ticket() com id=0.
    if (t.id == 0) return false;

    t.status = "em andamento";
    if (!ticketRepo_.updateStatus(t.id, t.status)) return false;

    historico.inserir(t);
    return true;
}

// ======================================================
// PRIORIDADE (ABB)
// ======================================================
std::vector<Ticket> TicketService::getTicketsByPriority() {
    // ABB não retorna lista (apenas listar/print). Então DB é fonte de verdade.
    auto tickets = ticketRepo_.findAll();

    auto rank = [](const std::string& p) {
        if (p == "alta") return 0;
        if (p == "media" || p == "média") return 1;
        if (p == "baixa") return 2;
        return 3;
    };

    std::stable_sort(tickets.begin(), tickets.end(), [&](const Ticket& a, const Ticket& b) {
        return rank(a.priority) < rank(b.priority);
    });

    return tickets;
}

// ======================================================
// REABRIR ÚLTIMO (PILHA)
// ======================================================
void TicketService::reopenLastTicket() {
    Ticket t = pilhaReabertura.pop();
    if (t.id == 0) return;

    t.status = "reaberto";
    ticketRepo_.updateStatus(t.id, t.status);

    filaAtendimento.enfileirar(t);
    historico.inserir(t);
}

// ======================================================
// HISTÓRICO
// ======================================================
std::vector<Ticket> TicketService::getHistory() {
    // Lista retorna vector (lista.h).
    return historico.listar();
}

// ======================================================
// FILA (para endpoint admin)
// ======================================================
std::vector<Ticket> TicketService::getFila() {
    // Fila não expõe iteração/listagem retornável.
    // Então retornamos via DB (fonte de verdade) apenas tickets em aberto/em andamento.
    auto tickets = ticketRepo_.findAll();

    std::vector<Ticket> out;
    out.reserve(tickets.size());

    for (const auto& t : tickets) {
        if (t.status != "resolvido") out.push_back(t);
    }

    // Ordenação estável por prioridade (secundária) para consistência do front.
    auto rank = [](const std::string& p) {
        if (p == "alta") return 0;
        if (p == "media" || p == "média") return 1;
        if (p == "baixa") return 2;
        return 3;
    };

    std::stable_sort(out.begin(), out.end(), [&](const Ticket& a, const Ticket& b) {
        return rank(a.priority) < rank(b.priority);
    });

    return out;
}

