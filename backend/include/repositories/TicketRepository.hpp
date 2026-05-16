#pragma once

#include <mysql/mysql.h>

#include <vector>
#include <optional>
#include <string>

#include "models/Ticket.hpp"

class TicketRepository {
private:
    MYSQL* conn_;

public:
    TicketRepository(MYSQL* conn);

    // Admin + geral (ativos e não-resolvidos)
    std::vector<Ticket> findAll();

    std::optional<Ticket> findById(int id);

    int create(
        const std::string& title,
        const std::string& description,
        const std::string& priority,
        int userId
    );

    bool updateStatus(int id, const std::string& status);

    bool remove(int id);

    // Admin (histórico global - resolvidos)
    std::vector<Ticket> findResolvedTickets();

    // =========================
    // MEUS TICKETS (USER)
    // =========================
    std::vector<Ticket> findTicketsByUserActive(int userId);
    std::vector<Ticket> findResolvedTicketsByUser(int userId);
};

