#ifndef USER_SERVICE_HPP
#define USER_SERVICE_HPP

#include "repositories/UserRepository.hpp"
#include <optional>

// ======================================================
// Service: Logica de negocio para usuarios
// ======================================================
class UserService {
public:
    explicit UserService(UserRepository& userRepo);

    std::optional<User> getUserById(int id) const;
    std::optional<User> getUserByEmail(const std::string& email) const;

private:
    UserRepository& userRepo_;
};

#endif

