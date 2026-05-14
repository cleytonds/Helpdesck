#include "database/Database.hpp"

#include <iostream>

Database& Database::getInstance() {
    static Database instance;
    return instance;
}

Database::Database() {}

bool Database::connect() {

    std::cout << "[DB] ENTER CONNECT" << std::endl;

    std::lock_guard<std::mutex> lock(mtx);

    std::cout << "[DB] BEFORE MYSQL_INIT" << std::endl;

    conn = mysql_init(nullptr);

    std::cout << "[DB] AFTER MYSQL_INIT" << std::endl;

    if (!conn) {
        std::cerr << "[DB ERROR] mysql_init falhou" << std::endl;
        return false;
    }

    std::cout << "[DB] MYSQL INIT OK" << std::endl;

    // =========================
    // MYSQL OPTIONS
    // =========================

    unsigned int timeout = 10;
    mysql_options(conn, MYSQL_OPT_CONNECT_TIMEOUT, &timeout);

    mysql_options(conn, MYSQL_SET_CHARSET_NAME, "utf8");

    my_bool reconnect = 1;
    mysql_options(conn, MYSQL_OPT_RECONNECT, &reconnect);

    my_bool ssl = 0;
    mysql_options(conn, MYSQL_OPT_SSL_ENFORCE, &ssl);
    mysql_options(conn, MYSQL_OPT_SSL_VERIFY_SERVER_CERT, &ssl);

    std::cout << "[DB] Tentando conectar..." << std::endl;

    MYSQL* result = mysql_real_connect(
        conn,
        "127.0.0.1",
        "root",
        "root123",
        "helpdesk",
        3307,
        nullptr,
        CLIENT_MULTI_STATEMENTS | CLIENT_REMEMBER_OPTIONS
    );

    
    if (!result) {

        std::cerr << "[DB ERROR] mysql_real_connect falhou" << std::endl;

        if (conn) {
            std::cerr << "[MYSQL CODE] " << mysql_errno(conn) << std::endl;
            std::cerr << "[MYSQL MSG] " << mysql_error(conn) << std::endl;
        }

        return false;
    }

    conn = result;

    std::cout << "[OK] Database conectado" << std::endl;

    return true;
}

void Database::disconnect() {

    std::lock_guard<std::mutex> lock(mtx);

    if (conn) {
        mysql_close(conn);
        conn = nullptr;
    }
}

MYSQL* Database::getConnection() {
    return conn;
}

bool Database::isConnected() {
    return conn != nullptr;
}