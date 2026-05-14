# MySQL Connector/C Migration Guide

## Visão Geral

Este guia detalha como migrar do MariaDB Connector para o MySQL Connector/C oficial da Oracle no ambiente MSYS2 UCRT64.

## Pré-requisitos

- MSYS2 UCRT64 instalado
- MySQL (XAMPP) rodando em 127.0.0.1:3307
- C++17 compiler

## Etapa 1: Baixar MySQL Connector/C

1. Acesse: https://dev.mysql.com/downloads/connector/c/
2. Selecione: **Windows (x86, 64-bit), ZIP Archive**
3. Extraia para: `C:\mysql-connector-c`

## Etapa 2: Converter biblioteca para MinGW

Abra o terminal MSYS2 UCRT64 e execute:

```bash
cd /c/mysql-connector-c/lib
gendef libmysql.dll
dlltool -D libmysql.dll -d libmysql.def -l libmysql.a
```

Isso cria `libmysql.a` compatível com MinGW/g++.

## Etapa 3: Arquivos atualizados

### build.bat (atualizado)
- Include: `-I"C:\mysql-connector-c\include"`
- Link: `-L"C:\mysql-connector-c\lib" -lmysql -lws2_32 -lssl -lcrypto -lz`

### Makefile (atualizado)
- MYSQL_INCLUDE = `-I"/c/mysql-connector-c/include"`
- MYSQL_LIB = `-L"/c/mysql-connector-c/lib"`
- MYSQL_LINK = `-lmysql`

### Database.hpp
```cpp
#include <mysql.h>
class Database {
public:
    static Database& getInstance();
    bool connect();
    void disconnect();
    MYSQL* getConnection();
    bool isConnected() const;
    ConnectionTestResult testConnection();
    ~Database();
};
```

### Database.cpp
- Usa `mysql_init()`, `mysql_real_connect()`, `mysql_options()`
- SSL desativado: `MYSQL_OPT_SSL_MODE` = `SSL_MODE_DISABLED`
- TCP forçado: `MYSQL_OPT_PROTOCOL` = `MYSQL_PROTOCOL_TCP`

## Etapa 4: Compilar

### Via build.bat
```cmd
cd backend
build.bat
```

### Via Makefile
```bash
cd backend
make MODE=debug
```

### Via linha de comando
```bash
g++ -std=c++17 -Iinclude -I"C:\mysql-connector-c\include" \
    -c src/server.cpp -o obj/server.o

g++ obj/server.o -L"C:\mysql-connector-c\lib" -lmysql \
    -lws2_32 -lssl -lcrypto -lz -o bin/servidor.exe
```

## Etapa 5: Executar

```bash
./bin/servidor.exe
```

Saída esperada:
```
========================================
      HELPDESK BACKEND SERVER
========================================
[1] Conectando ao banco...
[DB] Conectando ao MySQL...
[DB] Conectado ao MySQL (127.0.0.1:3307)
[OK] Banco conectado.
[OK] Conexao ativa.
[OK] Ponteiro MYSQL* valido.
[3] Backend iniciado com sucesso.
[OK] Encerrado.
```

## Solução de Problemas

### Erro SSL 2026
- O código já configura `SSL_MODE_DISABLED`
- Garanta que o MySQL não exige SSL forçado
- Verifique se a porta 3307 está correta no AppConfig.hpp

### Erro "cannot find -lmysql"
- Execute o comando de conversão da lib (etapa 2)
- Verifique o caminho: `C:\mysql-connector-c\lib\libmysql.a`

### Erro "No such file or directory"
- Verifique se extraiu o MySQL Connector/C para `C:\mysql-connector-c`
- O diretório deve conter `include/mysql.h` e `lib/libmysql.dll`

## Estrutura do Código (C API Puro)

```cpp
#include <mysql.h>

MYSQL* conn = mysql_init(nullptr);

// Desativar SSL
enum mysql_ssl_mode ssl_mode = SSL_MODE_DISABLED;
mysql_options(conn, MYSQL_OPT_SSL_MODE, &ssl_mode);

// Conectar
mysql_real_connect(conn, host, user, password, database, port, nullptr, 0);

// Query
mysql_query(conn, "SELECT 1");
MYSQL_RES* res = mysql_store_result(conn);

// Cleanup
mysql_free_result(res);
mysql_close(conn);
```

## Arquivos Modificados

- `backend/build.bat` - Includes e libs MySQL Connector/C
- `backend/Makefile` - Configuração de build
- `backend/include/database/Database.hpp` - Header class
- `backend/src/database/Database.cpp` - Implementação C API
- `backend/src/server.cpp` - Teste de conexão
- `backend/tests/test_database.cpp` - Testes unitários

## Conexão sem SSL (XAMPP Local)

O código configura:
```cpp
enum mysql_ssl_mode ssl_mode = SSL_MODE_DISABLED;
mysql_options(conn_, MYSQL_OPT_SSL_MODE, &ssl_mode);

unsigned int protocol = MYSQL_PROTOCOL_TCP;
mysql_options(conn_, MYSQL_OPT_PROTOCOL, &protocol);
```

Isso garente conexão local XAMPP sem necessidade de certificados SSL.
