import { useEffect, useState } from "react";
import api from "../services/api";
import "../pages/AdminDashboard.css";
import { Link, useNavigate } from "react-router-dom";

export default function AdminTickets() {
  // ======================================================
  // ESTADOS
  // ======================================================
  const [tickets, setTickets] = useState([]);
  const [fila, setFila] = useState([]);
  const [historico, setHistorico] = useState([]);
  const [prioridades, setPrioridades] = useState([]);

  const [loading, setLoading] = useState(true);

  const navigate = useNavigate();

  // ======================================================
  // LOAD GERAL
  // ======================================================
  async function loadAll() {
    try {
      const [t, f, h, p] = await Promise.all([
        api.get("/admin/tickets"),
        api.get("/admin/fila"),
        api.get("/admin/historico"),
        api.get("/admin/prioridades"),
      ]);

      setTickets(t.data.tickets);
      setFila(f.data.tickets);
      setHistorico(h.data.tickets);
      setPrioridades(p.data.tickets);

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
      await api.put(`/admin/tickets/${id}`, {
        status,
        level,
      });

      loadAll();

    } catch (error) {
      console.error("Erro atualizar chamado:", error);
    }
  }

  // ======================================================
  // INIT
  // ======================================================
  useEffect(() => {
    loadAll();
  }, []);

  // ======================================================
  // RENDER
  // ======================================================
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

        <button
          onClick={() => navigate("/admin/tickets")}
          className="btn-admin-tickets"
        >
          📋 Tickets
        </button>

        <button
          className="logout-btn"
          onClick={() => navigate("/login")}
        >
          🚪 Sair
        </button>

      </div>

      

      {/* TICKETS */}
      <section>
        <h2>Todos os Chamados</h2>

        <div className="tickets-grid">
          {tickets.map((ticket) => (
            <div key={ticket.id} className="ticket-admin-card">

              {/* HEADER */}
              <div className="ticket-top">
                <h3>{ticket.title}</h3>

                <span className="ticket-status">
                  {ticket.status}
                </span>
              </div>

              {/* INFO */}
              <p><strong>Usuário:</strong> {ticket.user_name}</p>
              <p><strong>Email:</strong> {ticket.user_email}</p>
              <p><strong>Categoria:</strong> {ticket.category}</p>
              <p><strong>Prioridade:</strong> {ticket.priority}</p>

              <div className="description-box">
                {ticket.description}
              </div>

              {/* CONTROLES */}
              <div className="admin-controls">

                {/* STATUS */}
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

                {/* PRIORIDADE */}
                <select
                  value={ticket.priority}
                  onChange={(e) =>
                    updateTicket(ticket.id, ticket.status, e.target.value)
                  }
                >
                  <option value="baixa">Baixa</option>
                  <option value="media">Média</option>
                  <option value="alta">Alta</option>
                </select>

              </div>

            </div>
          ))}
        </div>
      </section>

      {/* FILA */}
      <section>
        <h2>Fila de Atendimento</h2>
        <div className="simple-grid">
          {fila.map((t, index) => (
            <div key={index} className="mini-card">
              {t.titulo} - {t.prioridade}
            </div>
          ))}
        </div>
      </section>

      {/* PRIORIDADES */}
      <section>
        <h2>Ordenado por Prioridade</h2>
        <div className="simple-grid">
          {prioridades.map((t, index) => (
            <div key={index} className="mini-card">
              {t.titulo} - {t.prioridade}
            </div>
          ))}
        </div>
      </section>

      {/* HISTÓRICO */}
      <section>
        <h2>Histórico de Atendimentos</h2>
        <div className="simple-grid">
          {historico.map((t, index) => (
            <div key={index} className="mini-card">
              {t.titulo} - {t.status}
            </div>
          ))}
        </div>
      </section>

    </div>
  );
}