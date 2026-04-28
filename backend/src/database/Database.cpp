#include "database/Database.hpp"
#include "config/AppConfig.hpp"

#include <iostream>
#include <chrono>
#include <memory>

#include "mysql_driver.h"
#include <cppconn/driver.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>

// ======================================================
// DESTRUTOR
// ======================================================
Database::~Database() {
    disconnect();
}

// ======================================================
// SINGLETON
// ======================================================
Database& Database::getInstance() {
    static Database instance;
    return instance;
}

// ======================================================
// CONECTAR
// ======================================================
bool Database::connect() {
    std::lock_guard<std::mutex> lock(mutex_);

    std::cout << "[DB] Conectando ao banco..." << std::endl;

    if (connection_ && !connection_->isClosed()) {
        return true;
    }

    try {
        sql::Driver* driver = get_driver_instance();

        connection_ = driver->connect(
            AppConfig::DB_HOST,
            AppConfig::DB_USER,
            AppConfig::DB_PASSWORD
        );

        connection_->setSchema(AppConfig::DB_SCHEMA);

        std::cout << "[OK] Banco conectado!" << std::endl;
        return true;

    } catch (sql::SQLException& e) {
        std::cerr << "[ERRO MYSQL] " << e.what() << std::endl;
        connection_ = nullptr;
        return false;
    }
}

// ======================================================
// DESCONECTAR
// ======================================================
void Database::disconnect() {
    std::lock_guard<std::mutex> lock(mutex_);

    if (connection_) {
        connection_->close();
        delete connection_;
        connection_ = nullptr;

        std::cout << "[OK] Banco desconectado." << std::endl;
    }
}

// ======================================================
// PEGAR CONEXÃO
// (SOMENTE REUTILIZAÇÃO - NÃO CRIA NOVA)
// ======================================================
sql::Connection* Database::getConnection() {
    std::lock_guard<std::mutex> lock(mutex_);
    return connection_;
}

// ======================================================
// STATUS
// ======================================================
bool Database::isConnected() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return connection_ && !connection_->isClosed();
}

// ======================================================
// TESTE DE CONEXÃO
// ======================================================
ConnectionTestResult Database::testConnection() {
    ConnectionTestResult result;

    std::lock_guard<std::mutex> lock(mutex_);

    if (!connection_) {
        result.success = false;
        result.message = "Conexao nula";
        result.errorCode = -1;
        return result;
    }

    if (connection_->isClosed()) {
        result.success = false;
        result.message = "Conexao fechada";
        result.errorCode = -2;
        return result;
    }

    try {
        auto start = std::chrono::steady_clock::now();

        std::unique_ptr<sql::Statement> stmt(connection_->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT 1 AS ping"));

        auto end = std::chrono::steady_clock::now();

        if (res->next() && res->getInt("ping") == 1) {
            result.success = true;
            result.message = "SELECT 1 OK";
            result.errorCode = 0;
        } else {
            result.success = false;
            result.message = "Falha no ping";
            result.errorCode = -3;
        }

    } catch (sql::SQLException& e) {
        result.success = false;
        result.message = e.what();
        result.errorCode = e.getErrorCode();
    }

    return result;
}