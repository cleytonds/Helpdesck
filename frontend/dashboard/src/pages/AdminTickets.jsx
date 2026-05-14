import { useEffect, useState } from "react";
import api from "../services/api";
import "./AdminDashboard.css";
import { useNavigate } from "react-router-dom";

export default function AdminTickets() {
  const [tickets, setTickets] = useState([]);
  const [fila, setFila] = useState([]);
  const [historico, setHistorico] = useState([]);
  const [prioridades, setPrioridades] = useState([]);
  const [loading, setLoading] = useState(true);

  const navigate = useNavigate();

  // ======================================================
  // LOAD
  // ======================================================
  async function loadAll() {
    try {
      const [t, f, h, p] = await Promise.all([
        api.get("/tickets"),            // 🔥 CORRIGIDO
        api.get("/admin/fila"),
        api.get("/admin/historico"),
        api.get("/admin/prioridades"),
      ]);

      setTickets(t.data.tickets || []);
      setFila(f.data.tickets || []);
      setHistorico(h.data.tickets || []);
      setPrioridades(p.data.tickets || []);

    } catch (error) {
      console.error("Erro admin:", error);
    } finally {
      setLoading(false);
    }
  }

  // ======================================================
  // UPDATE STATUS
  // ======================================================
  async function updateTicket(id, status, level) {
    try {
      await api.put(`/tickets/${id}`, {   // 🔥 CORRIGIDO
        status,
        level,
      });

      loadAll();

    } catch (error) {
      console.error("Erro atualizar chamado:", error);
    }
  }

  useEffect(() => {
    loadAll();
  }, []);

  if (loading) {
    return <div className="loading">Carregando painel...</div>;
  }

  return (
    <div className="admin-container">

      <div className="admin-title">
        <h1>Painel Inteligente</h1>
        <p>Central de controle administrativo</p>
      </div>

      <div className="admin-actions">

        <button onClick={() => navigate("/admin/tickets")}>
          📋 Tickets
        </button>

        <button onClick={() => navigate("/dashboard")}>
          🚪 Sair
        </button>

      </div>

      {/* TODOS TICKETS */}
      <section>
        <h2>Todos os Chamados</h2>

        <div className="tickets-grid">
          {tickets.map((ticket) => (
            <div key={ticket.id} className="ticket-admin-card">

              <h3>{ticket.title}</h3>

              <p><strong>Usuário:</strong> {ticket.user_name}</p>
              <p><strong>Email:</strong> {ticket.user_email}</p>
              <p><strong>Prioridade:</strong> {ticket.priority}</p>

              <div>{ticket.description}</div>

              <select
                value={ticket.status}
                onChange={(e) =>
                  updateTicket(ticket.id, e.target.value, ticket.priority)
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

      {/* FILA */}
      <section>
        <h2>Fila de Atendimento</h2>
        <div className="simple-grid">
          {fila.map((t) => (
            <div key={t.id}>
              {t.title} - {t.priority}
            </div>
          ))}
        </div>
      </section>

      {/* PRIORIDADE */}
      <section>
        <h2>Prioridades</h2>
        <div className="simple-grid">
          {prioridades.map((t) => (
            <div key={t.id}>
              {t.title} - {t.priority}
            </div>
          ))}
        </div>
      </section>

      {/* HISTÓRICO */}
      <section>
        <h2>Histórico</h2>
        <div className="simple-grid">
          {historico.map((t) => (
            <div key={t.id}>
              {t.title} - {t.status}
            </div>
          ))}
        </div>
      </section>

    </div>
  );
}