#ifndef AUTH_HPP
#define AUTH_HPP

#include <string>

class Auth {
public:
    Auth();

    bool login(const std::string& email, const std::string& senha);
};

#endif