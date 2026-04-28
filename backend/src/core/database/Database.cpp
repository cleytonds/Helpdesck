#include "Database.hpp"
#include "../../config/AppConfig.hpp"
#include <iostream>
#include <chrono>
#include "mysql_driver.h"
#include <cppconn/driver.h>

Database::~Database() {
    disconnect();
}

Database& Database::getInstance() {
    static Database instance;
    return instance;
}

bool Database::connect() {
    std::cout << "DEBUG: connect() FOI CHAMADO" << std::endl;
    std::lock_guard<std::mutex> lock(mutex_);
    std::cout << "Conectando ao banco..." << std::endl;

    if (connection_ != nullptr && !connection_->isClosed()) {
        return true;
    }

    try {
        sql::Driver* driver = get_driver_instance();
        connection_ = driver->connect(AppConfig::DB_HOST, AppConfig::DB_USER, AppConfig::DB_PASSWORD);
        connection_->setSchema(AppConfig::DB_SCHEMA);

        std::cout << "[OK] Banco conectado!" << std::endl;
        return true;

    } catch (sql::SQLException& e) {
        std::cout << "[ERRO MYSQL] " << e.what() << std::endl;
        connection_ = nullptr;
        return false;
    }
}

void Database::disconnect() {
    std::lock_guard<std::mutex> lock(mutex_);
    if (connection_ != nullptr) {
        connection_->close();
        delete connection_;
        connection_ = nullptr;
        std::cout << "[OK] Banco desconectado." << std::endl;
    }
}

sql::Connection* Database::getConnection() {
    std::lock_guard<std::mutex> lock(mutex_);
    return connection_;
}

bool Database::isConnected() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return connection_ != nullptr && !connection_->isClosed();
}

ConnectionTestResult Database::testConnection() {
    ConnectionTestResult result;
    std::lock_guard<std::mutex> lock(mutex_);

    // 1. Verificar se há conexão
    if (connection_ == nullptr) {
        result.success = false;
        result.message = "Conexao eh nullptr (nunca conectou ou foi desconectada)";
        result.errorCode = -1;
        std::cerr << "[FAIL] testConnection: " << result.message << std::endl;
        return result;
    }

    // 2. Verificar se não está fechada
    if (connection_->isClosed()) {
        result.success = false;
        result.message = "Conexao esta fechada (isClosed() = true)";
        result.errorCode = -2;
        std::cerr << "[FAIL] testConnection: " << result.message << std::endl;
        return result;
    }

    // 3. Executar SELECT 1 para validar comunicação ativa
    try {
        auto start = std::chrono::steady_clock::now();

        sql::Statement* stmt = connection_->createStatement();
        sql::ResultSet* res = stmt->executeQuery("SELECT 1 AS ping");

        auto end = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        if (res->next()) {
            int pingValue = res->getInt("ping");
            if (pingValue == 1) {
                result.success = true;
                result.message = "SELECT 1 OK (" + std::to_string(elapsed) + " ms)";
                result.errorCode = 0;
                std::cout << "[OK] testConnection: " << result.message << std::endl;
            } else {
                result.success = false;
                result.message = "SELECT 1 retornou valor inesperado: " + std::to_string(pingValue);
                result.errorCode = -3;
                std::cerr << "[FAIL] testConnection: " << result.message << std::endl;
            }
        } else {
            result.success = false;
            result.message = "SELECT 1 nao retornou nenhuma linha";
            result.errorCode = -4;
            std::cerr << "[FAIL] testConnection: " << result.message << std::endl;
        }

        delete res;
        delete stmt;

    } catch (sql::SQLException& e) {
        result.success = false;
        result.message = std::string("SQLException: ") + e.what();
        result.errorCode = e.getErrorCode();
        std::cerr << "[FAIL] testConnection: " << result.message
                  << " (codigo: " << result.errorCode << ")" << std::endl;
    }

    return result;
}

