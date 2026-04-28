@echo off
chcp 65001 >nul
setlocal

:: Caminho do g++ no MSYS2 UCRT64
set PATH=C:\msys64\ucrt64\bin;C:\msys64\usr\bin;%PATH%

:: Diretórios de include
set INC=-I. -Iinclude -Isrc -Istructures -I"C:\mysql-connector-c++-9.7.0-winx64\mysql-connector-c++-9.7.0-winx64\include\jdbc"

:: Flags de compilação
set CFLAGS=-std=c++17 %INC%

:: Diretório de saída
if not exist obj mkdir obj
if not exist bin mkdir bin

echo ========================================
echo  BUILD - HelpDesk Server
echo ========================================
echo.

echo [1/5] Compilando objetos...

g++.exe %CFLAGS% -c src/main.cpp                          -o obj/main.o
if %ERRORLEVEL% NEQ 0 goto erro

g++.exe %CFLAGS% -c src/server.cpp                        -o obj/server.o
if %ERRORLEVEL% NEQ 0 goto erro

g++.exe %CFLAGS% -c src/api.cpp                           -o obj/api.o
if %ERRORLEVEL% NEQ 0 goto erro

g++.exe %CFLAGS% -c src/core/TicketManager.cpp            -o obj/TicketManager.o
if %ERRORLEVEL% NEQ 0 goto erro

g++.exe %CFLAGS% -c src/core/database/Database.cpp        -o obj/Database.o
if %ERRORLEVEL% NEQ 0 goto erro

g++.exe %CFLAGS% -c src/check_disabled.cpp                -o obj/check.o
if %ERRORLEVEL% NEQ 0 goto erro

g++.exe %CFLAGS% -c structures/FilaRequisicoes.cpp        -o obj/FilaRequisicoes.o
if %ERRORLEVEL% NEQ 0 goto erro

g++.exe %CFLAGS% -c structures/ListaRequisicoes.cpp       -o obj/ListaRequisicoes.o
if %ERRORLEVEL% NEQ 0 goto erro

g++.exe %CFLAGS% -c structures/ArvoreRequisicoes.cpp      -o obj/ArvoreRequisicoes.o
if %ERRORLEVEL% NEQ 0 goto erro

echo [2/5] Linkando servidor...

g++.exe obj/main.o obj/server.o obj/api.o obj/TicketManager.o obj/Database.o obj/check.o obj/FilaRequisicoes.o obj/ListaRequisicoes.o obj/ArvoreRequisicoes.o ^
  -L. -lmysqlcppconn -lws2_32 ^
  -o bin/servidor.exe

if %ERRORLEVEL% NEQ 0 goto erro

echo [3/5] Compilando teste de conexao MySQL...

g++.exe %CFLAGS% -c tests/test_database.cpp                    -o obj/test_database.o
if %ERRORLEVEL% NEQ 0 goto erro

g++.exe obj/test_database.o obj/Database.o ^
  -L. -lmysqlcppconn -lws2_32 ^
  -o bin/test_database.exe

if %ERRORLEVEL% NEQ 0 goto erro

echo.
echo ========================================
echo  BUILD CONCLUIDO COM SUCESSO!
echo ========================================
echo.
echo Executaveis gerados:
echo   - bin\servidor.exe
echo   - bin\test_mysql.exe
echo.
echo Comandos:
echo   bin\servidor.exe      - Inicia o servidor HTTP
echo   bin\test_mysql.exe    - Testa apenas a conexao MySQL
echo   curl http://localhost:8080/health
echo.
goto fim

:erro
echo.
echo ========================================
echo  ERRO NA COMPILACAO!
echo ========================================
echo.

:fim
endlocal
pause
