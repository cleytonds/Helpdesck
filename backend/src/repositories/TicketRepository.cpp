#include "repositories/TicketRepository.hpp"

#include <iostream>
#include <sstream>
#include <mysql/mysql.h>

// ======================================================
// CONSTRUCTOR
// ======================================================
TicketRepository::TicketRepository(MYSQL* conn)
    : conn_(conn) {}

// ======================================================
// FIND ALL (SEM RESOLVIDOS)
// ======================================================
std::vector<Ticket> TicketRepository::findAll() {
    std::vector<Ticket> list;

    std::string query =
        "SELECT id, title, description, priority, status, user_id "
        "FROM tickets "
        "WHERE status != 'resolvido' "
        "ORDER BY created_at DESC";

    if (mysql_query(conn_, query.c_str()) != 0) {
        std::cerr << mysql_error(conn_) << std::endl;
        return list;
    }

    MYSQL_RES* res = mysql_store_result(conn_);
    MYSQL_ROW row;

    while ((row = mysql_fetch_row(res))) {
        Ticket t;

        t.id = std::stoi(row[0]);
        t.title = row[1];
        t.description = row[2];
        t.priority = row[3];
        t.status = row[4];
        t.userId = std::stoi(row[5]);

        list.push_back(t);
    }

    mysql_free_result(res);

    return list;
}

// ======================================================
// FIND HISTORY (RESOLVIDOS - GLOBAL)
// ======================================================
std::vector<Ticket> TicketRepository::findResolvedTickets() {
    std::vector<Ticket> list;

    std::string query =
        "SELECT id, title, description, priority, status, user_id "
        "FROM tickets "
        "WHERE status = 'resolvido' "
        "ORDER BY updated_at DESC";

    if (mysql_query(conn_, query.c_str()) != 0) {
        std::cerr << mysql_error(conn_) << std::endl;
        return list;
    }

    MYSQL_RES* res = mysql_store_result(conn_);
    MYSQL_ROW row;

    while ((row = mysql_fetch_row(res))) {
        Ticket t;

        t.id = std::stoi(row[0]);
        t.title = row[1];
        t.description = row[2];
        t.priority = row[3];
        t.status = row[4];
        t.userId = std::stoi(row[5]);

        list.push_back(t);
    }

    mysql_free_result(res);

    return list;
}

// ======================================================
// MEUS TICKETS (ATIVOS)
// SQL: WHERE user_id = ? AND status != 'resolvido'
// ======================================================
std::vector<Ticket> TicketRepository::findTicketsByUserActive(int userId) {
    std::vector<Ticket> list;

    std::stringstream query;
    query <<
        "SELECT id, title, description, priority, status, user_id "
        "FROM tickets "
        "WHERE user_id = " << userId << " AND status != 'resolvido' "
        "ORDER BY created_at DESC";

    if (mysql_query(conn_, query.str().c_str()) != 0) {
        std::cerr << mysql_error(conn_) << std::endl;
        return list;
    }

    MYSQL_RES* res = mysql_store_result(conn_);
    MYSQL_ROW row;

    while ((row = mysql_fetch_row(res))) {
        Ticket t;

        t.id = std::stoi(row[0]);
        t.title = row[1];
        t.description = row[2];
        t.priority = row[3];
        t.status = row[4];
        t.userId = std::stoi(row[5]);

        list.push_back(t);
    }

    mysql_free_result(res);

    return list;
}

// ======================================================
// HISTÓRICO (RESOLVIDOS - POR USUÁRIO)
// SQL: WHERE user_id = ? AND status = 'resolvido'
// ======================================================
std::vector<Ticket> TicketRepository::findResolvedTicketsByUser(int userId) {
    std::vector<Ticket> list;

    std::stringstream query;
    query <<
        "SELECT id, title, description, priority, status, user_id "
        "FROM tickets "
        "WHERE user_id = " << userId << " AND status = 'resolvido' "
        "ORDER BY updated_at DESC";

    if (mysql_query(conn_, query.str().c_str()) != 0) {
        std::cerr << mysql_error(conn_) << std::endl;
        return list;
    }

    MYSQL_RES* res = mysql_store_result(conn_);
    MYSQL_ROW row;

    while ((row = mysql_fetch_row(res))) {
        Ticket t;

        t.id = std::stoi(row[0]);
        t.title = row[1];
        t.description = row[2];
        t.priority = row[3];
        t.status = row[4];
        t.userId = std::stoi(row[5]);

        list.push_back(t);
    }

    mysql_free_result(res);

    return list;
}

// ======================================================
// FIND BY ID
// ======================================================
std::optional<Ticket> TicketRepository::findById(int id) {
    auto tickets = findAll();
    auto resolved = findResolvedTickets();

    tickets.insert(tickets.end(), resolved.begin(), resolved.end());

    for (const auto& t : tickets) {
        if (t.id == id) {
            return t;
        }
    }

    return std::nullopt;
}

// ======================================================
// CREATE
// ======================================================
int TicketRepository::create(
    const std::string& title,
    const std::string& description,
    const std::string& priority,
    int userId
) {
    std::stringstream query;

    query << "INSERT INTO tickets "
          << "(title, description, priority, status, user_id) VALUES ('"
          << title << "', '"
          << description << "', '"
          << priority << "', 'aberto', "
          << userId << ")";

    if (mysql_query(conn_, query.str().c_str()) != 0) {
        std::cerr << mysql_error(conn_) << std::endl;
        return -1;
    }

    return (int)mysql_insert_id(conn_);
}

// ======================================================
// UPDATE STATUS + INSERT INTO ticket_history
// ======================================================
bool TicketRepository::updateStatus(int id, const std::string& status) {

    std::string oldStatus;

    {
        std::stringstream selectQuery;
        selectQuery << "SELECT status FROM tickets WHERE id=" << id;

        if (mysql_query(conn_, selectQuery.str().c_str()) != 0) {
            std::cerr << mysql_error(conn_) << std::endl;
            return false;
        }

        MYSQL_RES* res = mysql_store_result(conn_);
        if (!res) return false;

        MYSQL_ROW row = mysql_fetch_row(res);
        if (row) {
            oldStatus = row[0];
        }

        mysql_free_result(res);
    }

    std::stringstream query;
    query << "UPDATE tickets SET status='" << status << "' WHERE id=" << id;

    if (mysql_query(conn_, query.str().c_str()) != 0) {
        std::cerr << mysql_error(conn_) << std::endl;
        return false;
    }

    // HISTÓRICO
    std::stringstream historyQuery;
    historyQuery
        << "INSERT INTO ticket_history "
        << "(ticket_id, old_status, new_status, changed_by) "
        << "VALUES ("
        << id << ", '"
        << oldStatus << "', '"
        << status << "', 1)";

    if (mysql_query(conn_, historyQuery.str().c_str()) != 0) {
        std::cerr << mysql_error(conn_) << std::endl;
    }

    return true;
}

// ======================================================
// DELETE
// ======================================================
bool TicketRepository::remove(int id) {
    std::stringstream query;
    query << "DELETE FROM tickets WHERE id=" << id;

    if (mysql_query(conn_, query.str().c_str()) != 0) {
        std::cerr << mysql_error(conn_) << std::endl;
        return false;
    }

    return true;
}

