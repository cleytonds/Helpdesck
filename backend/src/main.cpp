#include <iostream>

#include "database/Database.hpp"
#include "server.hpp"

// Repositories
#include "repositories/UserRepository.hpp"
#include "repositories/TicketRepository.hpp"

// Services
#include "services/AuthService.hpp"
#include "services/TicketService.hpp"

// Controllers
#include "controllers/AuthController.hpp"
#include "controllers/TicketController.hpp"

int main()
{
    std::cout << "1 START" << std::endl;

    Database::getInstance().connect();

    std::cout << "2 AFTER DB" << std::endl;

    MYSQL* conn = Database::getInstance().getConnection();

    // ==================================================
    // REPOSITORIES
    // ==================================================
    UserRepository userRepo(conn);

    TicketRepository ticketRepo(conn);

    // ==================================================
    // SERVICES
    // ==================================================
    AuthService authService(userRepo, conn);

    TicketService ticketService(ticketRepo);

    // ==================================================
    // CONTROLLERS
    // ==================================================
    AuthController auth(authService);

    TicketController ticket(ticketService);

    // ==================================================
    // SERVER
    // ==================================================
    httplib::Server server;

    std::cout << "3 BEFORE SETUP ROUTES" << std::endl;

    setupRoutes(server, auth, ticket);

    std::cout << "4 BEFORE LISTEN" << std::endl;

    server.listen("0.0.0.0", 9090);

    std::cout << "5 AFTER LISTEN" << std::endl;

    return 0;
}