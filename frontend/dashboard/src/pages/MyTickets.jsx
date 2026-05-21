import { useEffect, useState, useContext } from "react";
import api from "../services/api";
import { AuthContext } from "../context/AuthContext";
import "./MyTickets.css";

export default function MyTickets() {
  const { user } = useContext(AuthContext);
  const [tickets, setTickets] = useState([]);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState("");

  async function loadMyTickets() {
    try {
      setError("");
      const res = await api.get("/tickets/me");
      setTickets(res.data?.tickets ?? []);
    } catch (err) {
      console.error("Erro ao buscar chamados:", err);
      setError(err.response?.data?.message || "Erro ao carregar chamados");
    } finally {
      setLoading(false);
    }
  }

  useEffect(() => {
    if (user?.id) {
      loadMyTickets();
    } else {
      setLoading(false);
    }
    // eslint-disable-next-line react-hooks/exhaustive-deps
  }, [user?.id]);

  if (loading) return <h2>Carregando...</h2>;
  if (error) return <div className="error">{error}</div>;

  return (
    <div className="mytickets-container">
      <h1>Meus Chamados</h1>
      <div className="tickets-grid">
        {(tickets ?? []).map((ticket) => (
          <div key={ticket.id} className="ticket-card">
            <h3>{ticket.title}</h3>
            <p>{ticket.description}</p>
            <p>
              <strong>Status:</strong> {ticket.status}
            </p>
            <p>
              <strong>Prioridade:</strong> {ticket.priority}
            </p>
          </div>
        ))}
      </div>
    </div>
  );
}
