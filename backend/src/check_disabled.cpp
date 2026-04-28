#include <iostream>
#include <string>
#include <map>
#include "../include/api.h"
#include "../include/database.h"
void check(const std::string &s) {
    std::cout << "check string: " << s << std::endl;
}

void check(const std::map<std::string,std::string> &m) {
    std::cout << "check map size: " << m.size() << std::endl;
}