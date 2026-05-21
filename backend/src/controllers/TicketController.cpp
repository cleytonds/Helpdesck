#include "controllers/TicketController.hpp"

#include "json.hpp"
#include "core/middleware/JWTMiddleware.hpp"

using json = nlohmann::json;

// ======================================================
TicketController::TicketController(TicketService& service)
    : service_(service) {}

// ======================================================
void TicketController::getAllTickets(
    const httplib::Request&, 
    httplib::Response& res
) {
    auto tickets = service_.getAllTickets();

    json response;
    response["tickets"] = json::array();

    for (const auto& t : tickets) {
        response["tickets"].push_back({
            {"id", t.id},
            {"title", t.title},
            {"description", t.description},
            {"priority", t.priority},
            {"status", t.status}
        });
    }

    res.set_content(response.dump(4), "application/json");
}

// ======================================================
void TicketController::getTicketById(
    const httplib::Request& req,
    httplib::Response& res
) {
    int id = std::stoi(req.matches[1]);

    auto ticket = service_.getTicketById(id);
    if (!ticket) {
        res.status = 404;
        res.set_content(R"({"error":"Ticket nao encontrado"})", "application/json");
        return;
    }

    json response = {
        {"id", ticket->id},
        {"title", ticket->title},
        {"description", ticket->description},
        {"priority", ticket->priority},
        {"status", ticket->status}
    };

    res.set_content(response.dump(4), "application/json");
}

// ======================================================
void TicketController::createTicket(
    const httplib::Request& req,
    httplib::Response& res
) {
    json body;

    try {
        body = json::parse(req.body);
    } catch (const std::exception&) {
        res.status = 400;
        res.set_content(R"({"success":false,"message":"Invalid JSON"})", "application/json");
        return;
    }

    if (!body.contains("title") || !body.contains("description") || !body.contains("priority")) {
        res.status = 400;
        res.set_content(R"({"success":false,"message":"Missing fields"})", "application/json");
        return;
    }

    TicketRequest ticketReq;
    ticketReq.title = body["title"].get<std::string>();
    ticketReq.description = body["description"].get<std::string>();
    ticketReq.priority = body["priority"].get<std::string>();

    JWTPayload payload;
    bool authed = JWTMiddleware::authenticate(req, payload);

    if (!authed || payload.userId <= 0) {
        res.status = 401;
        res.set_content(R"({"success":false,"message":"Unauthorized"})", "application/json");
        return;
    }

    bool ok = service_.createTicket(ticketReq, payload.userId);
    if (!ok) {
        res.status = 400;
        res.set_content(R"({"error":"Erro ao criar ticket"})", "application/json");
        return;
    }

    res.set_content(R"({"message":"Ticket criado com sucesso"})", "application/json");
}

// ======================================================
void TicketController::updateTicketStatus(
    const httplib::Request& req,
    httplib::Response& res
) {
    int id = std::stoi(req.matches[1]);

    json body;

    try {
        body = json::parse(req.body);
    } catch (const std::exception&) {
        res.status = 400;
        res.set_content(R"({"success":false,"message":"Invalid JSON"})", "application/json");
        return;
    }

    if (!body.contains("status")) {
        res.status = 400;
        res.set_content(R"({"success":false,"message":"Missing status"})", "application/json");
        return;
    }

    std::string status = body["status"].get<std::string>();

    bool ok = service_.updateTicketStatus(id, status);
    if (!ok) {
        res.status = 400;
        res.set_content(R"({"error":"Erro ao atualizar status"})", "application/json");
        return;
    }

    res.set_content(R"({"message":"Status atualizado"})", "application/json");
}

// ======================================================
void TicketController::deleteTicket(
    const httplib::Request& req,
    httplib::Response& res
) {
    int id = std::stoi(req.matches[1]);

    bool ok = service_.deleteTicket(id);
    if (!ok) {
        res.status = 400;
        res.set_content(R"({"error":"Erro ao deletar ticket"})", "application/json");
        return;
    }

    res.set_content(R"({"message":"Ticket removido"})", "application/json");
}

// ======================================================
// ADMIN: FILA
// ======================================================
void TicketController::getFila(
    const httplib::Request&, 
    httplib::Response& res
) {
    auto tickets = service_.getFila();

    json response;
    response["tickets"] = json::array();

    for (const auto& t : tickets) {
        response["tickets"].push_back({
            {"id", t.id},
            {"title", t.title},
            {"description", t.description},
            {"priority", t.priority},
            {"status", t.status}
        });
    }

    res.set_content(response.dump(4), "application/json");
}

// ======================================================
// ADMIN: HISTÓRICO (GLOBAL)
// ======================================================
void TicketController::getHistorico(
    const httplib::Request&, 
    httplib::Response& res
) {
    auto tickets = service_.getHistory();

    json response;
    response["historico"] = json::array();

    for (const auto& t : tickets) {
        response["historico"].push_back({
            {"id", t.id},
            {"title", t.title},
            {"description", t.description},
            {"priority", t.priority},
            {"status", t.status}
        });
    }

    res.set_content(response.dump(4), "application/json");
}

// ======================================================
// ADMIN: PRIORIDADES
// ======================================================
void TicketController::getPrioridades(
    const httplib::Request&, 
    httplib::Response& res
) {
    auto tickets = service_.getTicketsByPriority();

    json response;
    response["prioridades"] = json::array();

    for (const auto& t : tickets) {
        response["prioridades"].push_back({
            {"id", t.id},
            {"title", t.title},
            {"description", t.description},
            {"priority", t.priority},
            {"status", t.status}
        });
    }

    res.set_content(response.dump(4), "application/json");
}

// ======================================================
// USER: MEUS CHAMADOS (ATIVOS)
// ======================================================
void TicketController::getMyActiveTickets(
    const httplib::Request& req,
    httplib::Response& res
) {
    JWTPayload payload;
    bool authed = JWTMiddleware::authenticate(req, payload);

    if (!authed || payload.userId <= 0) {
        res.status = 401;
        res.set_content(R"({"success":false,"message":"Unauthorized"})", "application/json");
        return;
    }

    auto tickets = service_.getMyActiveTickets(payload.userId);

    json response;
    response["tickets"] = json::array();

    for (const auto& t : tickets) {
        response["tickets"].push_back({
            {"id", t.id},
            {"title", t.title},
            {"description", t.description},
            {"priority", t.priority},
            {"status", t.status}
        });
    }

    res.set_content(response.dump(4), "application/json");
}

// ======================================================
// USER: HISTÓRICO (RESOLVIDOS)
// ======================================================
void TicketController::getMyHistory(
    const httplib::Request& req,
    httplib::Response& res
) {
    JWTPayload payload;
    bool authed = JWTMiddleware::authenticate(req, payload);

    if (!authed || payload.userId <= 0) {
        res.status = 401;
        res.set_content(R"({"success":false,"message":"Unauthorized"})", "application/json");
        return;
    }

    auto tickets = service_.getMyResolvedHistory(payload.userId);

    json response;
    response["tickets"] = json::array();

    for (const auto& t : tickets) {
        response["tickets"].push_back({
            {"id", t.id},
            {"title", t.title},
            {"description", t.description},
            {"priority", t.priority},
            {"status", t.status}
        });
    }

    res.set_content(response.dump(4), "application/json");
}

