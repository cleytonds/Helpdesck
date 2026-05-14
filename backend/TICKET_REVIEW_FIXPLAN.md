# Plano de correções (compiláveis) para Helpdesk backend

## Objetivo
Gerar versões corrigidas e compiláveis (C++17) de:
- `TicketService.hpp`
- `TicketService.cpp`
- `TicketController.hpp`
- `TicketController.cpp`
- `src/server.cpp` (apenas rotas corrigidas)

Mantendo stack e estruturas existentes.

## Premissas
1. O controller atual não implementa rotas admin que `server.cpp` chama.
2. O `TicketService` usa um conjunto de métodos nas estruturas que provavelmente não bate com a API real de `backend/structures/*.hpp` (fila/pilha/abb/lista).
3. Para compilar sem mexer nas estruturas, vamos adaptar o service para usar exatamente a API real das estruturas via `backend/fila.h`, `backend/pilha.h`, `backend/abb.h`, `backend/lista.h`.

## Passos
1. Inspecionar headers reais das estruturas usadas:
   - `backend/include/fila.h`
   - `backend/include/pilha.h`
   - `backend/include/abb.h`
   - `backend/include/lista.h`
2. Inspecionar `TicketRepository.hpp` e `TicketRequest.hpp` e `models/ticket.hpp` para alinhar tipos.
3. Reescrever `TicketService.hpp/.cpp` para:
   - chamar apenas métodos existentes nas estruturas
   - manter o motor “fila/pilha/ABB/lista” sem alterar as estruturas
   - corrigir inconsistências (ex.: nomes de métodos enqueue/enfileirar vs push/pop)
4. Reescrever `TicketController.hpp/.cpp` para:
   - implementar `getFila`, `getHistorico`, `getPrioridades` (compatível com `server.cpp`)
   - adicionar try/catch em `json::parse` (robustez)
   - retornar JSON consistente (`success`, `message` etc.)
5. Ajustar `src/server.cpp` apenas nas rotas admin para apontar para os métodos que existirão.
6. Validar compilação (opcional executar g++ se o projeto estiver pronto para compilar no ambiente).

## Entregáveis
Após implementar, entregar os arquivos com conteúdo final completo.

