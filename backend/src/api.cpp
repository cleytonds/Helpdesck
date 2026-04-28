#include "httplib.h"
#include <iostream>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <sstream>
#include "../include/api.h"
#include "../include/database.h"
#include "core/TicketManager.hpp"

TicketManager manager;

using namespace std;

string listarRequisicoes(sql::Connection* con) {

    sql::Statement* stmt = con->createStatement();

    sql::ResultSet* res = stmt->executeQuery(
        "SELECT id, usuario, descricao, prioridade, status, data_abertura FROM requisicoes"
    );

    stringstream json;

    json << "[";

    bool primeiro = true;

    while (res->next()) {

        if (!primeiro)
            json << ",";

        json << "{";
        json << "\"id\":" << res->getInt("id") << ",";
        json << "\"usuario\":\"" << res->getString("usuario") << "\",";
        json << "\"descricao\":\"" << res->getString("descricao") << "\",";
        json << "\"prioridade\":" << res->getInt("prioridade") << ",";
        json << "\"status\":\"" << res->getString("status") << "\",";
        json << "\"data_abertura\":\"" << res->getString("data_abertura") << "\"";
        json << "}";
    }

    json << "]";

    delete res;
    delete stmt;

    return json.str();
}

void criarRequisicao(
    sql::Connection* con,
    string usuario,
    string descricao,
    int prioridade
) {

    sql::PreparedStatement* pstmt = con->prepareStatement(
        "INSERT INTO requisicoes(usuario, descricao, prioridade) VALUES (?, ?, ?)"
    );

    pstmt->setString(1, usuario);
    pstmt->setString(2, descricao);
    pstmt->setInt(3, prioridade);

    pstmt->execute();

    delete pstmt;
}
