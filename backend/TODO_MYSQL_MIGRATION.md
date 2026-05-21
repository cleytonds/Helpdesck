# TODO: Migração MariaDB → MySQL Connector/C (Oracle)

## Passo 1: Instalação MySQL Connector/C
- [ ] Baixar ZIP do MySQL Connector/C (Windows x64) em https://dev.mysql.com/downloads/connector/c/
- [ ] Extrair para `C:\mysql-connector-c`
- [ ] Converter libmysql.lib para libmysql.a (MinGW):
  ```bash
  cd /c/mysql-connector-c/lib
  gendef libmysql.dll
  dlltool -D libmysql.dll -d libmysql.def -l libmysql.a
  ```

## Passo 2: Ajustar backend/build.bat
- [ ] Alterar include: `-I"C:\msys64\ucrt64\include\mariadb"` → `-I"C:\mysql-connector-c\include"`
- [ ] Alterar libs: `-L"C:\msys64\ucrt64\lib" -lmariadbclient` → `-L"C:\mysql-connector-c\lib" -lmysql`
- [ ] Manter flags: `-lws2_32 -lssl -lcrypto -lz`

## Passo 3: Ajustar backend/Makefile
- [ ] Atualizar MYSQL_INCLUDE para `/c/mysql-connector-c/include`
- [ ] Atualizar MYSQL_LIB para `/c/mysql-connector-c/lib`
- [ ] Confirmar MYSQL_LINK como `-lmysql`
- [ ] Adicionar LIBS: `-lws2_32 -lssl -lcrypto -lz`

## Passo 4: Ajustar código Database.cpp
- [ ] Verificar include `<mysql.h>` compatível
- [ ] Garantir SSL desativado com `MYSQL_OPT_SSL_MODE` + `SSL_MODE_DISABLED`
- [ ] Adicionar `#include <string.h>` se necessário para `mysql_options`

## Passo 5: Testar compilação e execução
- [ ] Rodar `build.bat` ou `make`
- [ ] Executar `bin\servidor.exe`
- [ ] Verificar conexão ao MySQL XAMPP (127.0.0.1:3307) sem erro SSL 2026

