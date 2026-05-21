#ifndef TICKET_CONTROLLER_HPP
#define TICKET_CONTROLLER_HPP

#include "httplib.h"
#include "services/TicketService.hpp"

class TicketController {
public:
    explicit TicketController(TicketService& service);

    // USER/CRUD
    void getAllTickets(const httplib::Request&, httplib::Response&);
    void getTicketById(const httplib::Request&, httplib::Response&);
    void createTicket(const httplib::Request&, httplib::Response&);
    void updateTicketStatus(const httplib::Request&, httplib::Response&);
    void deleteTicket(const httplib::Request&, httplib::Response&);

    // ADMIN MOTOR ENDPOINTS (NÃO ALTERAR ROTAS /ADMIN)
    void getFila(const httplib::Request&, httplib::Response&);
    void getHistorico(const httplib::Request&, httplib::Response&);
    void getPrioridades(const httplib::Request&, httplib::Response&);

    // USER: MEUS CHAMADOS / HISTÓRICO
    void getMyActiveTickets(const httplib::Request&, httplib::Response&);
    void getMyHistory(const httplib::Request&, httplib::Response&);

private:
    TicketService& service_;
};

#endif

