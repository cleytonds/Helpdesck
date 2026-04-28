// ==========================================
// TESTE MÍNIMO ISOLADO - MySQL Connector C++
// Compilar: g++ -std=c++17 -I. -Isrc -Iinclude -Istructures -I"C:\mysql-connector-c++-9.7.0-winx64\include\jdbc" test_mysql.cpp src/core/database/Database.cpp -L. -lmysqlcppconn -lws2_32 -o test_mysql.exe
// ==========================================
#include <iostream>
#include "database/Database.hpp"
#include "config/AppConfig.hpp"

using namespace std;

int main() {
    cout << "========================================" << endl;
    cout << "  TESTE ISOLADO - MySQL Connection" << endl;
    cout << "========================================" << endl;

    cout << "[INFO] Host: " << AppConfig::DB_HOST << endl;
    cout << "[INFO] User: " << AppConfig::DB_USER << endl;
    cout << "[INFO] Schema: " << AppConfig::DB_SCHEMA << endl;
    cout << endl;

    cout << "[1] Chamando Database::getInstance().connect()..." << endl;
    bool ok = Database::getInstance().connect();

    if (!ok) {
        cerr << "[FALHA] connect() retornou FALSE" << endl;
        return 1;
    }

    cout << "[OK] connect() retornou TRUE" << endl;

    cout << "[2] Verificando isConnected()..." << endl;
    if (!Database::getInstance().isConnected()) {
        cerr << "[FALHA] isConnected() retornou FALSE!" << endl;
        return 1;
    }
    cout << "[OK] isConnected() retornou TRUE" << endl;

    cout << "[3] Testando getConnection()..." << endl;
    sql::Connection* con = Database::getInstance().getConnection();
    if (con == nullptr) {
        cerr << "[FALHA] getConnection() retornou nullptr!" << endl;
        return 1;
    }
    cout << "[OK] getConnection() retornou ponteiro valido" << endl;

    cout << "[4] Executando SELECT 1..." << endl;
    try {
        sql::Statement* stmt = con->createStatement();
        sql::ResultSet* res = stmt->executeQuery("SELECT 1 as ok, COUNT(*) as total FROM requisicoes");

        if (res->next()) {
            cout << "[OK] Query executada!" << endl;
            cout << "      MySQL respondeu: " << res->getInt("ok") << endl;
            cout << "      Total requisicoes: " << res->getInt("total") << endl;
        } else {
            cerr << "[FALHA] ResultSet vazio!" << endl;
        }

        delete res;
        delete stmt;

    } catch (sql::SQLException& e) {
        cerr << "[FALHA] SQLException: " << e.what() << endl;
        return 1;
    }

    cout << endl;
    cout << "[5] Desconectando..." << endl;
    Database::getInstance().disconnect();
    cout << "[OK] Teste concluido com sucesso!" << endl;

    return 0;
}
