# TODO - Helpdesk C++ REST API Refactoring

## Analysis Complete

### Information Gathered:
- Project has partial MVC structure with repositories, services, routes
- Libraries: cpp-httplib, nlohmann/json, MySQL Connector/C++
- Existing: UserRepository, TicketRepository, AuthService, TicketService
- Issues: JWT middleware incomplete, missing DELETE endpoint, no controller pattern

## Plan

### Files to CREATE:
1. `src/controllers/AuthController.hpp` + `.cpp` - Handle register/login
2. `src/controllers/TicketController.hpp` + `.cpp` - Handle ticket CRUD
3. `src/middlewares/JWTAuthMiddleware.hpp` + `.cpp` - Full JWT validation
4. `src/utils/ResponseFactory.hpp` + `.cpp` - JSON response builder

### Files to MODIFY:
1. `src/core/server/JWTService.cpp` - Full JWT implementation
2. `src/routes/AuthRoutes.cpp` - Use controller
3. `src/routes/TicketRoutes.cpp` - Add PUT/DELETE
4. `src/repositories/TicketRepository` - Add delete
5. `main.cpp` - Entry point

### Endpoints:
- POST /register → AuthController
- POST /login → AuthController
- GET /tickets → TicketController
- POST /tickets → TicketController
- PUT /tickets/:id → TicketController
- DELETE /tickets/:id → TicketController
