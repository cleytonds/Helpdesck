import { useState } from "react";
import api from "../services/api";
import "./Tickets.css";

// ======================================================
// Página de abertura de chamados
// ======================================================

export default function Tickets() {
  // ======================================================
  // Estados
  // ======================================================
  const [ticket, setTicket] = useState({
    title: "",
    category: "",
    priority: "Normal",
    description: "",
  });

  const [loading, setLoading] = useState(false);
  const [message, setMessage] = useState("");
  const [error, setError] = useState("");

  // ======================================================
  // Atualiza campos
  // ======================================================
  function handleChange(e) {
    setTicket({
      ...ticket,
      [e.target.name]: e.target.value,
    });
  }

  // ======================================================
  // Enviar chamado
  // ======================================================
  async function handleSubmit(e) {
    e.preventDefault();

    setError("");
    setMessage("");

    try {
      setLoading(true);

      await api.post("/tickets", {
        title: ticket.title,
        category: ticket.category,
        priority: ticket.priority,
        description: ticket.description,
      });

      setMessage("Chamado aberto com sucesso.");

      // Limpa formulário
      setTicket({
        title: "",
        category: "",
        priority: "Normal",
        description: "",
      });

    } catch (err) {
      setError(
        err.response?.data?.message ||
        "Erro ao abrir chamado."
      );
    } finally {
      setLoading(false);
    }
  }

  return (
    <div className="tickets-container">

      <div className="ticket-card">

        <h1>Abrir Chamado</h1>
        <p>Descreva o problema para suporte</p>

        {error && (
          <div className="error-box">
            {error}
          </div>
        )}

        {message && (
          <div className="success-box">
            {message}
          </div>
        )}

        <form onSubmit={handleSubmit}>

          {/* Título */}
          <div className="input-group">
            <label>Título</label>
            <input
              type="text"
              name="title"
              placeholder="Ex: Erro no sistema"
              value={ticket.title}
              onChange={handleChange}
              required
            />
          </div>

          {/* Categoria */}
          <div className="input-group">
            <label>Categoria</label>

            <select
              name="category"
              value={ticket.category}
              onChange={handleChange}
              required
            >
              <option value="">
                Selecione
              </option>

              <option value="Hardware">
                Hardware
              </option>

              <option value="Software">
                Software
              </option>

              <option value="Rede">
                Rede
              </option>

              <option value="Acesso">
                Acesso
              </option>

            </select>
          </div>

          {/* Prioridade */}
          <div className="input-group">
            <label>Prioridade</label>

            <select
              name="priority"
              value={ticket.priority}
              onChange={handleChange}
            >
              <option value="Baixa">
                Baixa
              </option>

              <option value="Normal">
                Normal
              </option>

              <option value="Alta">
                Alta
              </option>

              <option value="Crítica">
                Crítica
              </option>

            </select>
          </div>

          {/* Descrição */}
          <div className="input-group">
            <label>Descrição</label>

            <textarea
              name="description"
              rows="6"
              placeholder="Explique o problema detalhadamente..."
              value={ticket.description}
              onChange={handleChange}
              required
            />
          </div>

          {/* Botão */}
          <button
            type="submit"
            disabled={loading}
          >
            {loading
              ? "Enviando..."
              : "Abrir Chamado"}
          </button>

        </form>

      </div>

    </div>
  );
}