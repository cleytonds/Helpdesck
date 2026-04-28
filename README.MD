# 🚀 HelpDesk System - Enterprise Grade (C++ Backend + React Frontend + MySQL)

Sistema completo de HelpDesk inspirado em aplicações reais de mercado, com arquitetura modular, backend em C++ de alta performance e frontend moderno em React.

---

## 🏷️ Status do Projeto

![Status](https://img.shields.io/badge/status-em%20desenvolvimento-yellow)
![Backend](https://img.shields.io/badge/backend-C%2B%2B-blue)
![Frontend](https://img.shields.io/badge/frontend-React-61dafb)
![Database](https://img.shields.io/badge/database-MySQL-orange)

---

## 📌 Visão Geral

O sistema simula uma plataforma profissional de suporte técnico (HelpDesk), permitindo gerenciamento de chamados, usuários e filas de atendimento.

Ele foi desenvolvido com foco em:

* Arquitetura de software real
* Estruturas de dados aplicadas
* Comunicação backend/frontend via API
* Boas práticas de engenharia de software

---

## 🧠 Arquitetura do Sistema

```
Frontend (React)
      ↓ Axios (HTTP API)
Backend (C++ Server)
      ↓
MySQL Database
```

### 🧩 Diagrama Simplificado

```
[ React UI ] → [ API C++ Server ] → [ MySQL ]
```

---

## ⚙️ Tecnologias Utilizadas

### Backend (Core System)

* C++17
* MSYS2 / g++
* MySQL Connector C++
* Makefile build system
* Estruturas de dados:

  * Fila (Queue)
  * Pilha (Stack)
  * Lista encadeada
  * Árvore Binária de Busca (ABB)

### Frontend (UI Layer)

* React (Vite)
* Axios (HTTP requests)
* React Router DOM

### Banco de Dados

* MySQL

---

## 📁 Estrutura do Backend

```
src/
 ├── api.cpp
 ├── server.cpp
 ├── database.cpp
 ├── check.cpp
 ├── fila.cpp
 ├── lista.cpp
 ├── pilha.cpp
 ├── abb.cpp
 ├── ordenacao.cpp
 ├── main.cpp
```

### ▶️ Build & Run

```bash
make clean
make
./bin/servidor.exe
```

---

## 🌐 Frontend Architecture

```
src/
 ├── api/ (Axios config)
 ├── pages/
 │    ├── Login.jsx
 │    ├── Dashboard.jsx
 │    ├── Tickets.jsx
 ├── components/
 │    ├── Navbar.jsx
 │    ├── Sidebar.jsx
 ├── context/
 │    ├── AuthContext.jsx
```

### ▶️ Run Frontend

```bash
npm install
npm run dev
```

---

## 🔌 API Communication

Base URL:

```
http://localhost:3000
```

Exemplo de request:

```js
api.post('/login', { email, senha })
```

---

## 🔐 Funcionalidades do Sistema

### 👤 Usuário

* Login / autenticação
* Abertura de chamados
* Visualização de tickets

### 🛠️ Sistema

* Gerenciamento de filas (queue system)
* Processamento de dados com estruturas customizadas
* Integração com banco de dados MySQL

### 📊 Futuro (Roadmap)

* JWT Authentication
* Painel administrativo completo
* Sistema de permissões (roles)
* Notificações em tempo real
* Chat interno entre usuário e suporte

---

## 🧪 Status Técnico

| Camada      | Status                |
| ----------- | --------------------- |
| Backend C++ | ✅ Funcional           |
| API HTTP    | 🚧 Em evolução        |
| Frontend    | 🚧 Em desenvolvimento |
| Database    | ✅ Integrado           |

---

## 🐳 Docker (Futuro)

```bash
docker-compose up --build
```

Planejado:

* Backend containerizado
* Frontend containerizado
* MySQL isolado

---

## 📸 Screenshots (Adicionar depois)

```
/login.png
/dashboard.png
/tickets.png
```

---

## 🚀 Deploy (Futuro)

* Frontend: Vercel / Netlify
* Backend: VPS (Ubuntu + Nginx)
* Database: Cloud MySQL

---

## 👨‍💻 Autor

**Cleyton Silva**

* GitHub: [https://github.com/cleytonds](https://github.com/cleytonds)
* LinkedIn: [https://www.linkedin.com/in/cleytonds](https://www.linkedin.com/in/cleytonds)

---

## 🧠 Observação Final

Este projeto simula um sistema real de mercado e foi desenvolvido com foco em aprendizado avançado de backend, estruturas de dados e arquitetura full-stack moderna.

---

🔥 *Projeto em evolução constante para nível de portfólio profissional e vagas de estágio/desenvolvedor júnior.*
