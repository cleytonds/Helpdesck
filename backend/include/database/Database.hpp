#pragma once

#include <memory>
#include <mutex>

#include <mysql/mysql.h>

class Database {
public:
    static Database& getInstance();

    bool connect();
    void disconnect();

    MYSQL* getConnection();
    bool isConnected();

private:
    Database();

    MYSQL* conn = nullptr;
    std::mutex mtx;
};