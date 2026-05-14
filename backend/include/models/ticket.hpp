#pragma once

#include <string>

struct Ticket {
    int id;
    std::string title;
    std::string description;
    std::string priority;
    std::string status;
    int userId;
};