#include "httplib.h"
#include "json.hpp"

using json = nlohmann::json;

void registerTicketRoutes(httplib::Server& server)
{
    server.Post("/tickets", [](const httplib::Request& req, httplib::Response& res)
    {
        auto body = json::parse(req.body);

        std::string title = body["title"];
        std::string description = body["description"];

        // Salvar ticket banco

        res.set_content("Ticket criado", "text/plain");
    });

    server.Get("/tickets", [](const httplib::Request& req, httplib::Response& res)
    {
        json tickets = json::array();

        tickets.push_back({
            {"id", 1},
            {"title", "Erro sistema"},
            {"status", "aberto"}
        });

        res.set_content(tickets.dump(), "application/json");
    });
}