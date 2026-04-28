#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/connection.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <memory>
#include <mutex>
#include <string>
#include "mysql_driver.h"

// ===========================================
// Resultado do teste de conexão
// ===========================================
struct ConnectionTestResult {
    bool success = false;
    std::string message;
    int errorCode = 0;
};

// ===========================================
// Gerenciador de conexão MySQL (Singleton)
// ===========================================
class Database {
public:
    static Database& getInstance();

    bool connect();
    void disconnect();
    sql::Connection* getConnection();
    bool isConnected() const;

    // Teste robusto de conexão: executa SELECT 1
    ConnectionTestResult testConnection();

    // Não permitir cópia/movimentação
    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;
    Database(Database&&) = delete;
    Database& operator=(Database&&) = delete;

private:
    Database() = default;
    ~Database();

    sql::Connection* connection_ = nullptr;
    mutable std::mutex mutex_;
};

#endif // DATABASE_HPP

