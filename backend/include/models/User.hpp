#pragma once

#include <string>

struct User {
    int id;
    std::string name;
    std::string email;
    std::string password;
    bool active;
    std::string role;
};