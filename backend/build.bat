@echo off
chcp 65001 >nul
setlocal

set PATH=C:\msys64\ucrt64\bin;C:\msys64\usr\bin;%PATH%
set PATH=C:\msys64\ucrt64\bin;C:\msys64\usr\bin;%PATH%
set PATH=%CD%\lib\bin;%PATH%

:: INCLUDE
set INC=-I. -Iinclude -Isrc ^
-I"C:\msys64\ucrt64\include" ^
-I"C:\msys64\ucrt64\include\mariadb"

:: FLAGS
set CFLAGS=-std=c++17 %INC%

if not exist obj mkdir obj
if not exist bin mkdir bin

echo ========================================
echo  BUILD - HelpDesk C++ REST API
echo ========================================
echo.

echo [MAIN]
g++.exe %CFLAGS% -c src/main.cpp -o obj/main.o
if %ERRORLEVEL% NEQ 0 goto erro

echo [1/5] Database...
g++.exe %CFLAGS% -c src/check_disabled.cpp -o obj/check_disabled.o
if %ERRORLEVEL% NEQ 0 goto erro

g++.exe %CFLAGS% -c src/database/Database.cpp -o obj/database.o
if %ERRORLEVEL% NEQ 0 goto erro

echo [2/5] Repositories...
g++.exe %CFLAGS% -c src/repositories/UserRepository.cpp -o obj/UserRepository.o
if %ERRORLEVEL% NEQ 0 goto erro

g++.exe %CFLAGS% -c src/repositories/TicketRepository.cpp -o obj/TicketRepository.o
if %ERRORLEVEL% NEQ 0 goto erro

echo [3/5] Controllers...
g++.exe %CFLAGS% -c src/controllers/AuthController.cpp -o obj/AuthController.o
if %ERRORLEVEL% NEQ 0 goto erro

g++.exe %CFLAGS% -c src/controllers/TicketController.cpp -o obj/TicketController.o
if %ERRORLEVEL% NEQ 0 goto erro

echo [4/5] Services...
g++.exe %CFLAGS% -c src/services/AuthService.cpp -o obj/AuthService.o
if %ERRORLEVEL% NEQ 0 goto erro

echo [5/5] Core...
g++.exe %CFLAGS% -c src/core/server/JWTService.cpp -o obj/JWTService.o
if %ERRORLEVEL% NEQ 0 goto erro

g++.exe %CFLAGS% -c src/core/middleware/JWTMiddleware.cpp -o obj/JWTMiddleware.o
if %ERRORLEVEL% NEQ 0 goto erro

echo [6/6] Server...
g++.exe %CFLAGS% -c src/server.cpp -o obj/server.o
if %ERRORLEVEL% NEQ 0 goto erro

echo.
echo [LINK]

g++.exe obj/*.o ^
-mconsole ^
-L"C:\msys64\ucrt64\lib" ^
-lmariadb ^
-lws2_32 ^
-lwsock32 ^
-lcrypt32 ^
-lssl ^
-lcrypto ^
-lz ^
-o bin/servidor.exe

if %ERRORLEVEL% NEQ 0 goto erro

echo.
echo ========================================
echo  BUILD OK!
echo ========================================
goto fim

:erro
echo.
echo ERRO NA COMPILACAO!
echo.

:fim
pause