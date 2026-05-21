import { useEffect, useState } from "react";
import api from "../services/api";
import "./AdminDashboard.css";
import { useNavigate } from "react-router-dom";

export default function AdminDashboard() {
  const [tickets, setTickets] = useState([]);
  const [fila, setFila] = useState([]);
  const [historico, setHistorico] = useState([]);
  const [prioridades, setPrioridades] = useState([]);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState(null);

  const navigate = useNavigate();

  // ==============================
  // LOAD CENTRALIZADO
  // ==============================
    async function loadAll() {
    setLoading(true);
    setError(null);

    try {
      const [t, f, h, p] = await Promise.all([
        api.get("/tickets"),
        api.get("/admin/fila"),
        api.get("/admin/historico"),
        api.get("/admin/prioridades"),
      ]);

      setTickets(t.data?.tickets ?? []);

      setFila(f.data?.tickets ?? []);

      // CORREÇÃO
      setHistorico(h.data?.historico ?? []);

      setPrioridades(p.data?.prioridades ?? []);

    } catch (err) {

      console.error(err);

      setError("Erro ao carregar dados do painel");

    } finally {

      setLoading(false);

    }
  }
  // ==============================
  // UPDATE TICKET
  // ==============================
  async function updateTicket(id, status, level) {
    try {
      await api.put(`/tickets/${id}`, {
        status,
        level,
      });

      loadAll();
    } catch (err) {
      console.error(err);
      setError("Erro ao atualizar ticket");
    }
  }

  useEffect(() => {
    loadAll();
  }, []);

  // ==============================
  // UPDATE TICKET
  // ==============================
    async function updateTicket(id, status, level) {

    try {

      setLoading(true);

      await api.put(`/tickets/${id}`, {
        status,
        level,
      });

      await loadAll();

    } catch (err) {

      console.error(err);

      setError("Erro ao atualizar ticket");

    } finally {

      setLoading(false);

    }
  }

  // ==============================
  // DELETE TICKET
  // ==============================
    async function deleteTicket(id) {

    try {

      setLoading(true);

      await api.delete(`/tickets/${id}`);

      await loadAll();

    } catch (err) {

      console.error(err);

      setError("Erro ao excluir ticket");

    } finally {

      setLoading(false);

    }
  }

  // ==============================
  // STATES UI
  // ==============================
  if (loading) {
    return <div className="loading">Carregando painel...</div>;
  }

  if (error) {
    return <div className="error">{error}</div>;
  }

  return (
    <div className="admin-container">

      {/* HEADER */}
      <div className="admin-title">
        <h1>Admin Dashboard</h1>
        <p>Central de controle do sistema</p>
      </div>

      {/* ACTIONS */}
      <div className="admin-actions">
        <button onClick={() => navigate("/admin/tickets")}>
          📋 Tickets
        </button>

        <button onClick={() => navigate("/login")}>
          🚪 Sair
        </button>
      </div>

      {/* ===================== TICKETS ===================== */}
      <section>
        <h2>Todos os Chamados</h2>

        <div className="tickets-grid">
          {(tickets ?? []).map((ticket) => (
            <div key={ticket.id} className="ticket-card">

              <h3>{ticket.title}</h3>

              <p><strong>Usuário:</strong> {ticket.user_name}</p>
              <p><strong>Email:</strong> {ticket.user_email}</p>
              <p><strong>Status:</strong> {ticket.status}</p>

              <div className="description">
                {ticket.description}
              </div>

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
      </section>

      {/* ===================== FILA ===================== */}
      <section>
        <h2>Fila de Atendimento</h2>

        <div className="simple-grid">
          {(fila ?? []).map((t) => (
            <div key={t.id} className="mini-card">
              {t.title} - {t.priority}
            </div>
          ))}
        </div>
      </section>

      {/* ===================== PRIORIDADES ===================== */}
      <section>
        <h2>Prioridades</h2>

        <div className="simple-grid">
          {(prioridades ?? []).map((t) => (
            <div key={t.id} className="mini-card">
              {t.title} - {t.priority}
            </div>
          ))}
        </div>
      </section>

      {/* ===================== HISTÓRICO ===================== */}
      <section>
        <h2>Histórico</h2>

        <div className="simple-grid">
          {(historico ?? []).map((t) => (
            <div key={t.id} className="mini-card">

              <strong>{t.title}</strong>

              <p>{t.description}</p>

              <p>Status: {t.status}</p>

              <button
                onClick={() => deleteTicket(t.id)}
              >
                Excluir
              </button>

            </div>
          ))}
        </div>
      </section>

    </div>
  );
}