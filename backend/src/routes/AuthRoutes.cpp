#pragma once

#include "httplib.h"
#include "json.hpp"
#include "../database/Database.h"

#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <regex>
#include <memory>

using json = nlohmann::json;

// ========================================
// REGISTRO DAS ROTAS DE AUTENTICAÇÃO
// ========================================
void registerAuthRoutes(httplib::Server& server)
{
    // ========================================
    // ROTA DE CADASTRO
    // POST /register
    // ========================================
    server.Post("/register", [](const httplib::Request& req, httplib::Response& res)
    {
        try
        {
            // Converte JSON recebido
            json body = json::parse(req.body);

            std::string name = body["name"];
            std::string email = body["email"];
            std::string password = body["password"];

            // ========================================
            // VALIDAÇÃO DE EMAIL
            // ========================================
            std::regex emailRegex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
            
            if (!std::regex_match(email, emailRegex))
            {
                res.status = 400;

                json response;
                response["success"] = false;
                response["message"] = "Email inválido";

                res.set_content(response.dump(), "application/json");
                return;
            }

            // ========================================
            // CONEXÃO MYSQL
            // ========================================
            sql::Connection* conn = Database::getConnection();

            // ========================================
            // VERIFICAR EMAIL EXISTENTE
            // ========================================
            std::unique_ptr<sql::PreparedStatement> checkStmt(
                conn->prepareStatement(
                    "SELECT id FROM users WHERE email=?"
                )
            );

            checkStmt->setString(1, email);

            std::unique_ptr<sql::ResultSet> result(
                checkStmt->executeQuery()
            );

            if (result->next())
            {
                delete conn;

                res.status = 409;

                json response;
                response["success"] = false;
                response["message"] = "Email já cadastrado";

                res.set_content(response.dump(), "application/json");
                return;
            }

            // ========================================
            // INSERT USER
            // ========================================
            std::unique_ptr<sql::PreparedStatement> stmt(
                conn->prepareStatement(
                    "INSERT INTO users(name,email,password_hash,active,role) VALUES(?,?,?,?,?)"
                )
            );

            stmt->setString(1, name);
            stmt->setString(2, email);

            // OBS:
            // Depois iremos trocar por HASH REAL
            stmt->setString(3, password);

            stmt->setBoolean(4, true);
            stmt->setString(5, "user");

            stmt->execute();

            delete conn;

            json response;
            response["success"] = true;
            response["message"] = "Usuário cadastrado";

            res.status = 201;
            res.set_content(response.dump(), "application/json");
        }
        catch (...)
        {
            res.status = 500;

            json response;
            response["success"] = false;
            response["message"] = "Erro interno";

            res.set_content(response.dump(), "application/json");
        }
    });

    // ========================================
    // LOGIN
    // POST /login
    // ========================================
    server.Post("/login", [](const httplib::Request& req, httplib::Response& res)
    {
        try
        {
            json body = json::parse(req.body);

            std::string email = body["email"];
            std::string password = body["password"];

            sql::Connection* conn = Database::getConnection();

            std::unique_ptr<sql::PreparedStatement> stmt(
                conn->prepareStatement(
                    "SELECT * FROM users WHERE email=?"
                )
            );

            stmt->setString(1, email);

            std::unique_ptr<sql::ResultSet> result(
                stmt->executeQuery()
            );

            if (result->next())
            {
                std::string dbPassword = result->getString("password_hash");

                if (dbPassword == password)
                {
                    json response;

                    response["success"] = true;
                    response["user_id"] = result->getInt("id");
                    response["name"] = result->getString("name");
                    response["email"] = result->getString("email");
                    response["role"] = result->getString("role");

                    res.set_content(response.dump(), "application/json");
                }
                else
                {
                    res.status = 401;

                    json response;
                    response["success"] = false;
                    response["message"] = "Senha incorreta";

                    res.set_content(response.dump(), "application/json");
                }
            }
            else
            {
                res.status = 404;

                json response;
                response["success"] = false;
                response["message"] = "Usuário não encontrado";

                res.set_content(response.dump(), "application/json");
            }

            delete conn;
        }
        catch (...)
        {
            res.status = 500;

            json response;
            response["success"] = false;
            response["message"] = "Erro interno";

            res.set_content(response.dump(), "application/json");
        }
    });
}