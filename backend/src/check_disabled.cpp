#include <string>
#include <map>

// ======================================================
// Dummy check functions
// Necessário para linker do mysql connector
// ======================================================

void check(const std::string&) {
}

void check(const std::map<std::string, std::string>&) {
}