import { useEffect, useState } from "react";
import api from "../services/api";
import "./AdminTickets.css";

// ======================================================
// Painel Admin
// Visualizar e gerenciar chamados
// ======================================================

export default function AdminTickets() {
  // ======================================================
  // Estados
  // ======================================================
  const [tickets, setTickets] = useState([]);
  const [loading, setLoading] = useState(true);

  // ======================================================
  // Buscar chamados
  // ======================================================
  async function fetchTickets() {
    try {
      const response = await api.get("/admin/tickets");

      setTickets(response.data);
    } catch (error) {
      console.error("Erro ao carregar chamados:", error);
    } finally {
      setLoading(false);
    }
  }

  // ======================================================
  // Atualizar status chamado
  // ======================================================
  async function updateTicket(id, status, level) {
    try {
      await api.put(`/admin/tickets/${id}`, {
        status,
        level,
      });

      fetchTickets();
    } catch (error) {
      console.error("Erro atualizar chamado:", error);
    }
  }

  // ======================================================
  // Inicialização
  // ======================================================
  useEffect(() => {
    fetchTickets();
  }, []);

  return (
    <div className="admin-container">

      <div className="admin-header">
        <h1>Painel Administrativo</h1>
        <p>Gerencie os chamados do sistema</p>
      </div>

      {loading ? (
        <div className="loading">
          Carregando chamados...
        </div>
      ) : (
        <div className="tickets-grid">

          {tickets.length === 0 ? (
            <div className="empty-state">
              Nenhum chamado encontrado.
            </div>
          ) : (
            tickets.map((ticket) => (
              <div
                key={ticket.id}
                className="ticket-admin-card"
              >

                {/* Dados */}
                <div className="ticket-top">
                  <h3>{ticket.title}</h3>

                  <span className="ticket-status">
                    {ticket.status}
                  </span>
                </div>

                <p>
                  <strong>Usuário:</strong>{" "}
                  {ticket.user_name}
                </p>

                <p>
                  <strong>Email:</strong>{" "}
                  {ticket.user_email}
                </p>

                <p>
                  <strong>Categoria:</strong>{" "}
                  {ticket.category}
                </p>

                <p>
                  <strong>Prioridade:</strong>{" "}
                  {ticket.priority}
                </p>

                <p>
                  <strong>Descrição:</strong>
                </p>

                <div className="description-box">
                  {ticket.description}
                </div>

                {/* Controles */}
                <div className="admin-controls">

                  {/* Status */}
                  <select
                    defaultValue={ticket.status}
                    onChange={(e) =>
                      updateTicket(
                        ticket.id,
                        e.target.value,
                        ticket.level
                      )
                    }
                  >
                    <option value="Aberto">
                      Aberto
                    </option>

                    <option value="Em andamento">
                      Em andamento
                    </option>

                    <option value="Finalizado">
                      Finalizado
                    </option>
                  </select>

                  {/* Nível */}
                  <select
                    defaultValue={ticket.level || "N1"}
                    onChange={(e) =>
                      updateTicket(
                        ticket.id,
                        ticket.status,
                        e.target.value
                      )
                    }
                  >
                    <option value="N1">
                      Nível 1
                    </option>

                    <option value="N2">
                      Nível 2
                    </option>

                    <option value="N3">
                      Nível 3
                    </option>
                  </select>

                </div>

              </div>
            ))
          )}

        </div>
      )}

    </div>
  );
}