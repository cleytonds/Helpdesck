# TODO: Refatoração MySQL C API → MySQL Connector/C++ 8.0

✅ **Passo 0**: Criado este TODO

## Passo 1: Verificar/Preparar MySQL C++ Connector
- [ ] Confirmar que `backend/libmysqlcppconn.a` está funcional
- [ ] Verificar headers em `backend/lib/mysql-connector-cpp/include`
- [ ] Copiar DLL `mysqlcppconn-10-vs14.dll` para `backend/bin/`

## Passo 2: Refatorar Database Layer
- [ ] `backend/include/database/Database.hpp`: Trocar `MYSQL*` por `mysqlx::Session`
- [ ] `backend/src/database/Database.cpp`: Usar `mysqlx::Session("mysqlx://root:@127.0.0.1:3307/helpdesk")`

## Passo 3: Refatorar Repositories
- [ ] `UserRepository.hpp/cpp`: Receber `mysqlx::Session&`, usar `session.sql("SELECT...").bind(email).execute()`
- [ ] `TicketRepository.hpp/cpp`: Prepared statements para todas queries

## Passo 4: Atualizar Build
- [ ] `backend/Makefile`: `-Ibackend/lib/mysql-connector-cpp/include -L. -lmysqlcppconn`
- [ ] `backend/build.bat`: Adicionar flags do C++ connector

## Passo 5: Testar
- [ ] `make clean && make`
- [ ] `bin/servidor.exe`
- [ ] Testar endpoints de auth/tickets

## Comando g++ Final (depois da refatoração)
```bash
g++ -std=c++17 *.cpp -Ibackend/lib/mysql-connector-cpp/include -L. -lmysqlcppconn -lws2_32 -lssl -lcrypto -lz -o servidor.exe
```

