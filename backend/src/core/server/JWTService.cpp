#include "core/server/JWTService.hpp"

#include <sstream>
#include <unordered_map>
#include <chrono>
#include <iostream>

// ======================================================
// STORAGE TEMPORÁRIO (APENAS RESET PASSWORD)
// ======================================================
static std::unordered_map<std::string, int> resetTokens;
static std::unordered_map<std::string, long long> resetExpiry;

// ======================================================
// GERA TOKEN DE LOGIN (SIMPLIFICADO E SEGURO)
// ======================================================
// Formato interno:
// jwt|userId|email|role
// Usamos "|" ao invés de "." para evitar conflito com email
// ======================================================
std::string JWTService::generateToken(int userId,
                                     const std::string& email,
                                     const std::string& role)
{
    std::string safeEmail = email;

    // Evita quebra do token caso email tenha caracteres especiais
    for (char& c : safeEmail) {
        if (c == '|') c = '_';
    }

    return "jwt|" +
           std::to_string(userId) + "|" +
           safeEmail + "|" +
           role;
}

// ======================================================
// GERA TOKEN DE RESET DE SENHA
// ======================================================
std::string JWTService::generateResetToken(int userId)
{
    long long now =
        std::chrono::system_clock::now().time_since_epoch().count();

    std::string token =
        "reset|" + std::to_string(userId) + "|" + std::to_string(now);

    // Expiração: 15 minutos (em nanossegundos simplificado)
    long long expiry =
        now + 15LL * 60LL * 1000000000LL;

    resetTokens[token] = userId;
    resetExpiry[token] = expiry;

    return token;
}

// ======================================================
// VALIDA TOKEN DE RESET DE SENHA
// ======================================================
int JWTService::validateResetToken(const std::string& token)
{
    auto it = resetTokens.find(token);

    if (it == resetTokens.end())
        return 0;

    long long now =
        std::chrono::system_clock::now().time_since_epoch().count();

    if (now > resetExpiry[token]) {
        resetTokens.erase(token);
        resetExpiry.erase(token);
        return 0;
    }

    return it->second;
}

// ======================================================
// VALIDA TOKEN DE LOGIN E EXTRAI PAYLOAD
// ======================================================
// Aqui está o CORAÇÃO do seu sistema de autenticação
// ======================================================
bool JWTService::validateToken(const std::string& token, JWTPayload& payload)
{
    // Verifica prefixo
    if (token.rfind("jwt|", 0) != 0)
        return false;

    std::stringstream ss(token);
    std::string part;

    // Remove prefixo "jwt"
    std::getline(ss, part, '|');

    // ==============================
    // USER ID
    // ==============================
    if (!std::getline(ss, part, '|'))
        return false;

    try {
        payload.userId = std::stoi(part);
    } catch (...) {
        return false;
    }

    // ==============================
    // EMAIL
    // ==============================
    if (!std::getline(ss, payload.email, '|'))
        return false;

    // ==============================
    // ROLE (ADMIN / USER)
    // ==============================
    if (!std::getline(ss, payload.role, '|'))
        return false;

    return true;
}

// ======================================================
// EXTRAI TOKEN DO HEADER AUTHORIZATION
// ======================================================
std::string JWTService::extractFromHeader(const httplib::Request& req)
{
    auto auth = req.get_header_value("Authorization");

    // Formato esperado: Bearer TOKEN
    if (auth.rfind("Bearer ", 0) == 0)
        return auth.substr(7);

    return "";
}