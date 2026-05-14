# TODO - Helpdesk C++ MVC + MySQL (compilação 100% funcional)

## Progresso
- [x] Planejado e iniciada coleta de contexto (TicketService/TicketController/server.cpp).
- [x] Identificados métodos “fantasmas” e incompatibilidades com estruturas (Fila/ABB/Lista/Pilha).

## Próximos passos (obrigatórios)
- [ ] Refatorar **TicketService.hpp** e **TicketService.cpp** para: 
  - [ ] não usar métodos inexistentes das estruturas
  - [ ] remover retornos inválidos (ex.: ABB/Lista não retornam `vector`)
  - [ ] garantir uso de `TicketRepository` como fonte de verdade
  - [ ] usar estruturas apenas como motor em memória
- [ ] Refatorar **TicketController.hpp** e **TicketController.cpp** para: 
  - [ ] implementar corretamente `getFila`, `getHistorico`, `getPrioridades`
  - [ ] adicionar `try/catch` no parse de JSON em endpoints que fazem parse
  - [ ] garantir compatibilidade total com `server.cpp`
- [ ] Refatorar **server.cpp** para:
  - [ ] remover chamadas inválidas (ex.: `updateTicket` se não existir no controller)
  - [ ] bater 100% com as assinaturas reais do controller
- [ ] Compilar com `g++ -std=c++17` e corrigir qualquer erro restante.

