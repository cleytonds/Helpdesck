# TODO — HelpDesk Full Stack

> Planejamento profissional e técnico, **coerente com o código real** do repositório.

---

## Como ler este TODO
- ✅ **Implementado**: já existe no código.
- 🟧 **Em progresso**: já há base/rascunho e falta consolidar.
- 🟥 **A fazer**: melhoria/refatoração com impacto.

---

## Status: Backlog geral
### ✅ Implementado (evidenciado no código)
#### Backend
- ✅ Auth:
  - `POST /register`, `POST /login`
  - `POST /forgot-password`, `POST /reset-password`
  - token via `JWTService::generateToken`
- ✅ Tickets (fluxo real em `backend/src/server.cpp`):
  - `POST /tickets` (JWT)
  - `GET /tickets`, `GET /tickets/me`, `GET /tickets/history`
  - `PUT /tickets/:id`, `DELETE /tickets/:id`
- ✅ Admin (endpoints reais em `server.cpp`):
  - fila, histórico global e prioridades
- ✅ Persistência MySQL via repositories:
  - `UserRepository.cpp`
  - `TicketRepository.cpp`
- ✅ Históricos:
  - `ticket_history` inserido em `TicketRepository::updateStatus`

#### Frontend (dashboard)
- ✅ Axios interceptors:
  - injeta `Authorization: Bearer <token>`
  - redireciona em `401`
- ✅ Sessão:
  - `localStorage` no `AuthContext.jsx`
- ✅ Rotas:
  - `PrivateRoute` e `AdminRoute`

---

## ⏳ Em progresso / consolidação
### Backend
- 🟧 Unificar contratos e DTOs entre frontend e backend:
  - `frontend/dashboard/src/pages/Tickets.jsx` envia `category` e `userId`
  - backend real `TicketController::createTicket()` espera `title`, `description`, `priority` e `userId` via JWT.

### Segurança
- 🟧 Revisar consistência de autenticação:
  - `AuthMiddleware` é placeholder.
  - O fluxo real de tickets usa `JWTMiddleware`.

---

## 🟥 A fazer (prioridades)
### 1) Refatorações técnicas (Backend)
- 🟥 Remover/evitar divergência de rotas stub:
  - `backend/src/routes/TicketRoutes.cpp` e `backend/src/routes/AdminRoutes.cpp` retornam dados fake.
  - Fluxo principal usa `backend/src/server.cpp`.
- 🟥 Sanitização de SQL:
  - `TicketRepository::create`, `updateStatus`, `remove` usam concatenação de strings em partes.
  - Preferir prepared statements em todas as operações sensíveis.
- 🟥 Password hashing e consistência:
  - revisar o fluxo real de login/cadastro (comparações de senha no `AuthService`).

### 2) Melhorias de segurança
- 🟥 JWT:
  - tornar o token “real” (assinatura/expiração) ao invés do parsing simplificado atual.
- 🟥 Forgot/reset password:
  - evitar qualquer log sensível e garantir coerência entre armazenamento (tabela `password_resets`) e validação.

### 3) Melhorias Frontend (UX/UI e integração)
- 🟥 Ajustar payload do formulário de tickets para bater com o backend real:
  - remover `category`/`userId` do payload se o backend não consumir.
- 🟥 Melhorar tratamento de erro:
  - padronizar mensagens JSON e UX de falha.

---

## Roadmap profissional
### Backend
| Etapa | Objetivo | Prioridade |
|---|---|---|
| JWT real | expiração/assinatura + validação robusta | Alta |
| SQL seguro | prepared statements em todos os CRUD | Alta |
| Rotas | remover stubs e consolidar roteador | Média |
| DTOs | validar/normalizar payloads frontend↔backend | Média |

### Frontend
| Etapa | Objetivo | Prioridade |
|---|---|---|
| Contrato | garantir payload consistente | Alta |
| UX | estados de loading/erro por endpoint | Média |
| Admin | telas admin alinhadas ao contrato real | Média |

### Segurança
| Etapa | Objetivo |
|---|---|
| Hash de senha | implementar hashing real e verificar no login |
| Segurança DB | prepared statements + validação e limites |

### Deploy / DevOps (futuro)
| Etapa | Objetivo |
|---|---|
| Containerização | docker-compose (C++ backend + MySQL + React) |
| Config | baseURL via `.env` |

---

## Testes (automatizados)
- 🟥 Unit tests (JWTService parsing/validate)
- 🟥 Integração (repositories com MySQL)
- 🟥 E2E (login → abrir ticket → resolver → histórico)

---

## Observabilidade / Logs
- 🟥 Unificar logging no backend (existe `Logger.hpp`), e padronizar por request
- 🟥 Adicionar correlation-id nos logs

---

## Documentação futura
- 🟥 Validar e documentar o schema MySQL diretamente pelo arquivo SQL (`database/helpdesk.sql`).
- 🟥 Gerar automaticamente tabelas/diagramas a partir do contrato de endpoints.

---

## Arquivos de referência (do repositório)
- `backend/TODO.md`
- `backend/TODO_AUTH_REFACTOR.md`
- `backend/TODO_MYSQL_CPP_REFATOR.md`
- `frontend/dashboard/TODO.md`

