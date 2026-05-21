#ifndef JSONUTILS_HPP
#define JSONUTILS_HPP

#include "../include/json.hpp"
#include "../models/Requisicao.hpp"
#include <string>
#include <vector>

using json = nlohmann::json;

// ===========================================
// Helpers para construção de respostas JSON
// ===========================================
namespace JsonUtils {

    inline json successResponse(const std::string& mensagem, const json& dados = nullptr) {
        json resp = {
            {"status", "sucesso"},
            {"mensagem", mensagem}
        };
        if (!dados.is_null()) {
            resp["dados"] = dados;
        }
        return resp;
    }

    inline json errorResponse(const std::string& mensagem, int codigo = 400) {
        return json{
            {"status", "erro"},
            {"codigo", codigo},
            {"mensagem", mensagem}
        };
    }

    inline json toJson(const Requisicao& r) {
        return json{
            {"id", r.id},
            {"usuario", r.usuario},
            {"descricao", r.descricao},
            {"prioridade", r.prioridade}
        };
    }

    inline json toJsonArray(const std::vector<Requisicao>& lista) {
        json arr = json::array();
        for (const auto& r : lista) {
            arr.push_back(toJson(r));
        }
        return arr;
    }

} // namespace JsonUtils

#endif // JSONUTILS_HPP

