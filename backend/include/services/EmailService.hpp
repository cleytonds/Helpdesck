#pragma once

#include <string>

// ======================================================
// EMAIL SERVICE
// - Responsável por enviar emails via microserviço Node
// ======================================================
void sendEmail(const std::string& email,
               const std::string& link);