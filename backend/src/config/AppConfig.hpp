#ifndef APPCONFIG_HPP
#define APPCONFIG_HPP

#include <string>

// ===========================================
// Configuração centralizada da aplicação
// ===========================================
struct AppConfig {
    // MySQL
    static constexpr const char* DB_HOST     = "tcp://127.0.0.1:3307";
    static constexpr const char* DB_USER     = "root";
    static constexpr const char* DB_PASSWORD = "";
    static constexpr const char* DB_SCHEMA   = "helpdesk";

    // HTTP Server
    static constexpr const char* SERVER_HOST = "0.0.0.0";
    static constexpr int         SERVER_PORT = 8080;

    // CORS
    static constexpr const char* CORS_ORIGIN  = "*";
    static constexpr const char* CORS_METHODS = "GET, POST, OPTIONS";
    static constexpr const char* CORS_HEADERS = "Content-Type";
};

#endif // APPCONFIG_HPP

