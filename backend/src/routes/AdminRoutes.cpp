#include "httplib.h"
#include "json.hpp"

using json = nlohmann::json;

void registerAdminRoutes(httplib::Server& server)
{
    server.Get("/admin/tickets", [](const httplib::Request& req, httplib::Response& res)
    {
        json tickets = json::array();

        tickets.push_back({
            {"id", 1},
            {"priority", "alta"},
            {"status", "andamento"}
        });

        res.set_content(tickets.dump(), "application/json");
    });
}