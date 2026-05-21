import { useEffect, useState, useContext } from "react";
import api from "../services/api";
import { AuthContext } from "../context/AuthContext";
import "./History.css";

export default function History() {
  const { user } = useContext(AuthContext);
  const [tickets, setTickets] = useState([]);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState("");

  async function loadHistory() {
    try {
      setError("");
      const res = await api.get("/tickets/history");
      setTickets(res.data?.tickets ?? []);
    } catch (err) {
      console.error("Erro ao buscar histórico:", err);
      setError(err.response?.data?.message || "Erro ao carregar histórico");
    } finally {
      setLoading(false);
    }
  }

  useEffect(() => {
    if (user?.id) {
      loadHistory();
    } else {
      setLoading(false);
    }
    // eslint-disable-next-line react-hooks/exhaustive-deps
  }, [user?.id]);

  if (loading) return <div className="loading">Carregando...</div>;
  if (error) return <div className="error">{error}</div>;

  return (
    <div className="history-container">
      <h1>Histórico</h1>
      <div className="cards-grid">
        {(tickets ?? []).map((ticket) => (
          <div key={ticket.id} className="card">
            <h3>{ticket.title}</h3>
            <p>{ticket.description}</p>
            <span>Status: {ticket.status}</span>
            <span className="priority">Prioridade: {ticket.priority}</span>
          </div>
        ))}
      </div>
    </div>
  );
}

