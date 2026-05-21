#ifndef API_H
#define API_H

#pragma once

#include <string>

// ======================================================
// MYSQL C API
// ======================================================

#include <mysql/mysql.h>

// ======================================================
// NOVA ARQUITETURA MVC
// ======================================================

#include "repositories/TicketRepository.hpp"
#include "services/TicketService.hpp"
#include "controllers/TicketController.hpp"

#endif