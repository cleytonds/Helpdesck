#include "repositories/TicketRepository.hpp"
#include <iostream>
#include <sstream>
#include <mysql/mysql.h>

TicketRepository::TicketRepository(MYSQL* conn)
    : conn_(conn) {}

// ======================================================
// FIND ALL
// ======================================================
std::vector<Ticket> TicketRepository::findAll() {

    std::vector<Ticket> list;

    std::string query =
        "SELECT id, title, description, priority, status, user_id "
        "FROM tickets";

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
// CREATE
// ======================================================
int TicketRepository::create(
    const std::string& title,
    const std::string& description,
    const std::string& priority,
    int userId
) {

    std::stringstream query;

    query << "INSERT INTO tickets (title, description, priority, status, user_id) VALUES ('"
          << title << "', '"
          << description << "', '"
          << priority << "', 'aberto', "
          << userId << ")";

    if (mysql_query(conn_, query.str().c_str()) != 0) {
        return -1;
    }

    return (int)mysql_insert_id(conn_);
}

// ======================================================
// UPDATE STATUS
// ======================================================
bool TicketRepository::updateStatus(int id, const std::string& status) {

    std::stringstream query;

    query << "UPDATE tickets SET status='"
          << status << "' WHERE id=" << id;

    if (mysql_query(conn_, query.str().c_str()) != 0) {
        std::cerr << mysql_error(conn_) << std::endl;
        return false;
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