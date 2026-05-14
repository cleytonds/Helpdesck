#ifndef TICKET_REQUEST_HPP
#define TICKET_REQUEST_HPP

#include <string>
#include <optional>

// ======================================================
// DTO: Ticket Request
// ======================================================
struct TicketRequest {

    std::string title;
    std::string description;

    // baixa | media | alta
    std::string priority = "baixa";

    // ==================================================
    bool isValid() const {

        return !title.empty() &&
               !description.empty() &&
               (
                   priority == "baixa" ||
                   priority == "media" ||
                   priority == "alta"
               );
    }

    // ==================================================
    std::optional<std::string> validate() const {

        if (title.empty())
            return "Titulo obrigatorio";

        if (description.empty())
            return "Descricao obrigatoria";

        if (
            priority != "baixa" &&
            priority != "media" &&
            priority != "alta"
        ) {
            return "Prioridade invalida";
        }

        return std::nullopt;
    }
};

#endif