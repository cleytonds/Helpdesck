#include <iostream>
#include "core/database/Database.hpp"
#include "config/AppConfig.hpp"
#include "api.h"
#include "Database.hpp"

using namespace std;

int main() {
    cout << "========================================" << endl;
    cout << "  HELPDESK SERVER - v1.0" << endl;
    cout << "========================================" << endl;
    cout << "[1/4] Iniciando sistema..." << endl;

    // ==========================================
    // PASSO 1: Conectar ao banco (OBRIGATÓRIO)
    // ==========================================
    cout << "[2/4] Tentando conectar ao MySQL..." << endl;
    cout << "      Host: " << AppConfig::DB_HOST << endl;
    cout << "      User: " << AppConfig::DB_USER << endl;
    cout << "      Schema: " << AppConfig::DB_SCHEMA << endl;

    bool conectado = Database::getInstance().connect();

    if (!conectado) {
        cerr << "[FALHA] Nao foi possivel conectar ao banco de dados!" << endl;
        cerr << "[FALHA] Servidor NAO sera iniciado." << endl;
        return 1;
    }

    cout << "[OK] Banco conectado com sucesso!" << endl;

    // ==========================================
    // PASSO 2: Verificar conexao ativa
    // ==========================================
    if (!Database::getInstance().isConnected()) {
        cerr << "[FALHA] Conexao perdida imediatamente apos conectar!" << endl;
        return 1;
    }

    cout << "[3/4] Conexao verificada e ativa." << endl;

    // ==========================================
    // PASSO 3: Teste robusto de conexão no banco
    // ==========================================
    cout << "[3/4] Executando teste de conexao (SELECT 1)..." << endl;

    ConnectionTestResult testResult = Database::getInstance().testConnection();
    if (!testResult.success) {
        cerr << "[FALHA] Teste de conexao falhou: " << testResult.message << endl;
        cerr << "[FALHA] Codigo do erro: " << testResult.errorCode << endl;
        cerr << "[FALHA] Servidor NAO sera iniciado." << endl;
        return 1;
    }

    cout << "[OK] Teste de conexao passou: " << testResult.message << endl;

    // ==========================================
    // PASSO 4: Iniciar servidor HTTP
    // ==========================================
    cout << "[4/4] Iniciando servidor HTTP..." << endl;
    iniciarServidor();

    // Cleanup ao sair
    Database::getInstance().disconnect();
    cout << "[OK] Sistema encerrado." << endl;

    return 0;
}
