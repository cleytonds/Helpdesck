#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <cppconn/connection.h>
#include <mutex>

struct ConnectionTestResult {
    bool success;
    std::string message;
    int errorCode;
};

class Database {
private:
    sql::Connection* connection_ = nullptr;
    mutable std::mutex mutex_;

    Database() = default;

public:
    ~Database();

    static Database& getInstance();

    bool connect();
    void disconnect();

    sql::Connection* getConnection();

    bool isConnected() const;

    ConnectionTestResult testConnection();
};

#endif