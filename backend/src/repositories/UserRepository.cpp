#include "repositories/UserRepository.hpp"

UserRepository::UserRepository(st_mysql* conn)
    : conn_(conn) {}

std::optional<User> UserRepository::findByEmail(const std::string& email) {
    // simulado (depois conecta MySQL real)
    return std::nullopt;
}

bool UserRepository::existsByEmail(const std::string& email) {
    return false;
}

int UserRepository::create(const User& user) {
    return 1;
}

bool UserRepository::resetPasswordByToken(const std::string& token, const std::string& password) {
    return true;
}