#include "repositories/TicketRepository.hpp"

#include <sstream>
#include <iostream>
#include <cstring>

// ======================================================
TicketRepository::TicketRepository(MYSQL* conn)
    : conn_(conn) {}

// ======================================================
// LISTAR TODOS
// ======================================================
std::vector<Ticket> TicketRepository::findAll() {

    std::vector<Ticket> list;

    std::string query =
        "SELECT "
        "t.id, "
        "t.title, "
        "t.description, "
        "t.status, "
        "t.user_id, "
        "t.priority, "
        "u.name, "
        "u.email "
        "FROM tickets t "
        "LEFT JOIN users u ON u.id = t.user_id";

    if (mysql_query(conn_, query.c_str()) != 0) {
        return list;
    }

    MYSQL_RES* result = mysql_store_result(conn_);
    if (!result) return list;

    MYSQL_ROW row;

    while ((row = mysql_fetch_row(result))) {

        Ticket t;

        t.id = row[0] ? std::stoi(row[0]) : 0;
        t.title = row[1] ? row[1] : "";
        t.description = row[2] ? row[2] : "";
        t.status = row[3] ? row[3] : "";
        t.userId = row[4] ? std::stoi(row[4]) : 0;
        t.priority = row[5] ? row[5] : "baixa";

        // 🔥 ADICIONE ISSO
        t.user_name = row[6] ? row[6] : "";
        t.user_email = row[7] ? row[7] : "";

        list.push_back(t);
    }

    mysql_free_result(result);

    return list;
}

// ======================================================
// BUSCAR POR ID
// ======================================================
std::optional<Ticket> TicketRepository::findById(int id) {

    std::stringstream query;

    query << "SELECT id, title, description, status, user_id, priority "
          << "FROM tickets WHERE id=" << id << " LIMIT 1";

    if (mysql_query(conn_, query.str().c_str()) != 0) {
        return std::nullopt;
    }

    MYSQL_RES* result = mysql_store_result(conn_);
    if (!result) return std::nullopt;

    MYSQL_ROW row = mysql_fetch_row(result);

    if (!row) {
        mysql_free_result(result);
        return std::nullopt;
    }

    Ticket t;

    t.id = row[0] ? std::stoi(row[0]) : 0;
    t.title = row[1] ? row[1] : "";
    t.description = row[2] ? row[2] : "";
    t.status = row[3] ? row[3] : "";
    t.userId = row[4] ? std::stoi(row[4]) : 0;
    t.priority = row[5] ? row[5] : "N1";

    mysql_free_result(result);

    return t;
}

// ======================================================
// CREATE (CORRIGIDO PROFISSIONAL)
// ======================================================
bool TicketRepository::create(
    const std::string& title,
    const std::string& description,
    const std::string& priority,
    int userId)
{
    std::string status = "aberto";

    std::string query =
        "INSERT INTO tickets (title, description, priority, user_id, status) "
        "VALUES (?, ?, ?, ?, ?)";

    MYSQL_STMT* stmt = mysql_stmt_init(conn_);
    if (!stmt) return false;

    if (mysql_stmt_prepare(stmt, query.c_str(), query.length())) {
        mysql_stmt_close(stmt);
        return false;
    }

    MYSQL_BIND bind[5];
    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char*)title.c_str();

    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = (char*)description.c_str();

    bind[2].buffer_type = MYSQL_TYPE_STRING;
    bind[2].buffer = (char*)priority.c_str();

    bind[3].buffer_type = MYSQL_TYPE_LONG;
    bind[3].buffer = &userId;

    bind[4].buffer_type = MYSQL_TYPE_STRING;
    bind[4].buffer = (char*)status.c_str();

    mysql_stmt_bind_param(stmt, bind);
    mysql_stmt_execute(stmt);

    mysql_stmt_close(stmt);

    return true;
}

// ======================================================
// UPDATE STATUS (SEGURADO)
// ======================================================
bool TicketRepository::updateStatus(int id, const std::string& status) {

    std::string query =
        "UPDATE tickets SET status=? WHERE id=?";

    MYSQL_STMT* stmt = mysql_stmt_init(conn_);
    if (!stmt) return false;

    mysql_stmt_prepare(stmt, query.c_str(), query.length());

    MYSQL_BIND bind[2];
    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char*)status.c_str();
    bind[0].buffer_length = status.size();

    bind[1].buffer_type = MYSQL_TYPE_LONG;
    bind[1].buffer = (char*)&id;

    mysql_stmt_bind_param(stmt, bind);
    mysql_stmt_execute(stmt);

    mysql_stmt_close(stmt);

    return true;
}

// ======================================================
// DELETE (SEGURADO)
// ======================================================
bool TicketRepository::remove(int id) {

    std::string query =
        "DELETE FROM tickets WHERE id=?";

    MYSQL_STMT* stmt = mysql_stmt_init(conn_);
    if (!stmt) return false;

    mysql_stmt_prepare(stmt, query.c_str(), query.length());

    MYSQL_BIND bind[1];
    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type = MYSQL_TYPE_LONG;
    bind[0].buffer = (char*)&id;

    mysql_stmt_bind_param(stmt, bind);
    mysql_stmt_execute(stmt);

    mysql_stmt_close(stmt);

    return true;
}