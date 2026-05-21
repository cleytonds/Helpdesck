#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <mutex>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>

// ======================================================
// Niveis de log
// ======================================================
enum class LogLevel {
    DEBUG = 0,
    INFO  = 1,
    WARN  = 2,
    ERROR = 3
};

// ======================================================
// Logger thread-safe com timestamps
// ======================================================
class Logger {
public:
    static Logger& getInstance();

    void setLevel(LogLevel level);

    void debug(const std::string& msg);
    void info (const std::string& msg);
    void warn (const std::string& msg);
    void error(const std::string& msg);

private:
    Logger() = default;
    LogLevel currentLevel_ = LogLevel::INFO;
    mutable std::mutex mutex_;

    void log(LogLevel level, const std::string& msg);
    std::string levelToString(LogLevel level) const;
    std::string currentTimestamp() const;
};

// Macros convenientes
#define LOG_DEBUG(msg) Logger::getInstance().debug(msg)
#define LOG_INFO(msg)  Logger::getInstance().info(msg)
#define LOG_WARN(msg)  Logger::getInstance().warn(msg)
#define LOG_ERROR(msg) Logger::getInstance().error(msg)

#endif

