#pragma once

#include <mysql/mysql.h>

#include <vector>
#include <optional>
#include <string>

#include "models/Ticket.hpp"

// ======================================================
// REPOSITORY
// ======================================================
class TicketRepository {

private:

    MYSQL* conn_;

public:

    explicit TicketRepository(MYSQL* conn);

    std::vector<Ticket> findAll();

    std::optional<Ticket> findById(int id);

    int create(
    const std::string& title,
    const std::string& description,
    const std::string& priority,
    int userId
    );

    bool updateStatus(
        int id,
        const std::string& status
    );

    bool remove(int id);
};