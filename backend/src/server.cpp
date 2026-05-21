// ======================================================
// server.cpp - HTTP Server
// ======================================================

#include <iostream>
#include "httplib.h"
#include "json.hpp"

// Controllers
#include "controllers/AuthController.hpp"
#include "controllers/TicketController.hpp"

using json = nlohmann::json;

// ======================================================
// ROUTES SETUP
// ======================================================
void setupRoutes(httplib::Server& server,
                 AuthController& auth,
                 TicketController& ticket)
{
    std::cout << "[ROUTES] setupRoutes carregado" << std::endl;

    // ==================================================
    // CORS
    // ==================================================
    server.set_pre_routing_handler([](const httplib::Request& req,
                                      httplib::Response& res)
    {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type, Authorization");

        if (req.method == "OPTIONS") {
            res.status = 200;
            return httplib::Server::HandlerResponse::Handled;
        }

        return httplib::Server::HandlerResponse::Unhandled;
    });

    // ==================================================
    // TEST
    // ==================================================
    server.Get("/", [](const auto&, auto& res) {
        res.set_content("API ONLINE", "text/plain");
    });

    // ==================================================
    // AUTH
    // ==================================================
    server.Post("/register", [&](const auto& req, auto& res) {
        auth.registerUser(req, res);
    });

    server.Post("/login", [&](const auto& req, auto& res) {
        auth.login(req, res);
    });

    server.Post("/forgot-password", [&](const auto& req, auto& res) {
        auth.forgotPassword(req, res);
    });

    server.Post("/reset-password", [&](const auto& req, auto& res) {
        auth.resetPassword(req, res);
    });

    // ==================================================
    // TICKETS (USER)
    // ==================================================
    server.Get("/tickets", [&](const auto& req, auto& res) {
        ticket.getAllTickets(req, res);
    });

    // Usuário: Meus Chamados (ativos)
    server.Get("/tickets/me", [&](const auto& req, auto& res) {
        ticket.getMyActiveTickets(req, res);
    });


    // Usuário: Histórico (resolvidos)
    server.Get("/tickets/history", [&](const auto& req, auto& res) {
        ticket.getMyHistory(req, res);
    });


    server.Post("/tickets", [&](const auto& req, auto& res) {
        ticket.createTicket(req, res);
    });

    // Nota: rotas admin continuam intocadas ( /admin/* )


    server.Put(R"(/tickets/(\d+))", [&](const auto& req, auto& res) {
        ticket.updateTicketStatus(req, res);
    });

    server.Delete(R"(/tickets/(\d+))", [&](const auto& req, auto& res) {
        ticket.deleteTicket(req, res);
    });

    // ==================================================
    // ADMIN ROUTES
    // ==================================================
    server.Get("/admin/tickets", [&](const auto& req, auto& res) {
        ticket.getAllTickets(req, res);
    });

    server.Get("/admin/fila", [&](const auto& req, auto& res) {
        ticket.getFila(req, res);
    });

    server.Get("/admin/historico", [&](const auto& req, auto& res) {
        ticket.getHistorico(req, res);
    });

    server.Get("/admin/prioridades", [&](const auto& req, auto& res) {
        ticket.getPrioridades(req, res);
    });

    server.Put(R"(/admin/tickets/(\d+))", [&](const auto& req, auto& res) {
        ticket.updateTicketStatus(req, res);
    });
}

