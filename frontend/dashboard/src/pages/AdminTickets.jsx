import { useEffect, useState } from "react";
import api from "../services/api";
import "./AdminDashboard.css";
import { useNavigate } from "react-router-dom";

export default function AdminTickets() {
  const [tickets, setTickets] = useState([]);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState(null);

  const navigate = useNavigate();

  // ==============================
  // LOAD
  // ==============================
  async function loadTickets() {
    setLoading(true);
    setError(null);

    try {
      const res = await api.get("/tickets");
      setTickets(res.data?.tickets ?? []);
    } catch (err) {
      console.error(err);
      setError("Erro ao carregar tickets");
    } finally {
      setLoading(false);
    }
  }

  // ==============================
  // UPDATE
  // ==============================
  async function updateTicket(id, status, level) {
    try {
      await api.put(`/tickets/${id}`, {
        status,
        level,
      });

      loadTickets();
    } catch (err) {
      console.error(err);
      setError("Erro ao atualizar ticket");
    }
  }

  useEffect(() => {
    loadTickets();
  }, []);

  if (loading) return <div className="loading">Carregando...</div>;
  if (error) return <div className="error">{error}</div>;

  return (
    <div className="admin-container">

      <div className="admin-title">
        <h1>Tickets</h1>
      </div>

      <div className="admin-actions">
        <button onClick={() => navigate("/admin/dashboard")}>
          📊 Dashboard
        </button>

        <button onClick={() => navigate("/login")}>
          🚪 Sair
        </button>
      </div>

      <div className="tickets-grid">
        {(tickets ?? []).map((ticket) => (
          <div key={ticket.id} className="ticket-card">

            <h3>{ticket.title}</h3>

            <p><strong>User:</strong> {ticket.user_name}</p>
            <p><strong>Email:</strong> {ticket.user_email}</p>

            <div>{ticket.description}</div>

            <select
              value={ticket.status}
              onChange={(e) =>
                updateTicket(ticket.id, e.target.value, ticket.level)
              }
            >
              <option value="aberto">Aberto</option>
              <option value="andamento">Em andamento</option>
              <option value="resolvido">Resolvido</option>
            </select>

            <select
              value={ticket.level || "N1"}
              onChange={(e) =>
                updateTicket(ticket.id, ticket.status, e.target.value)
              }
            >
              <option value="N1">N1</option>
              <option value="N2">N2</option>
              <option value="N3">N3</option>
            </select>

          </div>
        ))}
      </div>

    </div>
  );
}