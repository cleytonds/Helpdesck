#include "httplib.h"

void registerAuthRoutes(httplib::Server& server);
void registerTicketRoutes(httplib::Server& server);
void registerAdminRoutes(httplib::Server& server);

int main()
{
    httplib::Server server;

    registerAuthRoutes(server);
    registerTicketRoutes(server);
    registerAdminRoutes(server);

    server.listen("0.0.0.0", 9090);
}