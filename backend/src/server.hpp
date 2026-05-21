#pragma once

#include "httplib.h"
#include "controllers/AuthController.hpp"
#include "controllers/TicketController.hpp"

// Função que monta as rotas
void setupRoutes(httplib::Server& server,
                 AuthController& auth,
                 TicketController& ticket);
