import { Clock, AlertCircle, CheckCircle2, PauseCircle } from "lucide-react";
import "../styles/variables.css";

const statusConfig = {
  aberto: { label: "Aberto", color: "#3b82f6", icon: Clock },
  em_andamento: { label: "Em andamento", color: "#f59e0b", icon: PauseCircle },
  resolvido: { label: "Resolvido", color: "#22c55e", icon: CheckCircle2 },
  urgente: { label: "Urgente", color: "#ef4444", icon: AlertCircle },
};

const priorityConfig = {
  baixa: { label: "Baixa", bg: "#dcfce7", color: "#166534" },
  media: { label: "Média", bg: "#fef9c3", color: "#854d0e" },
  alta: { label: "Alta", bg: "#fee2e2", color: "#991b1b" },
};

export default function TicketCard({ ticket }) {
  const status = statusConfig[ticket.status] || statusConfig.aberto;
  const priority = priorityConfig[ticket.prioridade] || priorityConfig.media;
  const StatusIcon = status.icon;

  return (
    <div className="ticket-card">
      <div className="ticket-header">
        <span className="ticket-id">#{ticket.id}</span>
        <span
          className="ticket-priority"
          style={{ background: priority.bg, color: priority.color }}
        >
          {priority.label}
        </span>
      </div>
      <h3 className="ticket-title">{ticket.titulo}</h3>
      <p className="ticket-desc">{ticket.descricao}</p>
      <div className="ticket-footer">
        <span className="ticket-status" style={{ color: status.color }}>
          <StatusIcon size={14} />
          {status.label}
        </span>
        <span className="ticket-date">{ticket.data}</span>
      </div>

      <style>{`
        .ticket-card {
          background: var(--card-bg);
          border: 1px solid var(--card-border);
          border-radius: var(--radius-md);
          box-shadow: var(--card-shadow);
          padding: 20px;
          display: flex;
          flex-direction: column;
          gap: 10px;
          transition: transform 0.15s, box-shadow 0.15s;
        }

        .ticket-card:hover {
          transform: translateY(-2px);
          box-shadow: 0 4px 12px rgba(0,0,0,0.1);
        }

        .ticket-header {
          display: flex;
          align-items: center;
          justify-content: space-between;
        }

        .ticket-id {
          font-size: 13px;
          font-weight: 600;
          color: var(--text-muted);
        }

        .ticket-priority {
          font-size: 12px;
          font-weight: 600;
          padding: 4px 10px;
          border-radius: 999px;
        }

        .ticket-title {
          font-size: 16px;
          font-weight: 600;
          color: var(--text-primary);
          line-height: 1.3;
        }

        .ticket-desc {
          font-size: 14px;
          color: var(--text-secondary);
          line-height: 1.4;
          display: -webkit-box;
          -webkit-line-clamp: 2;
          -webkit-box-orient: vertical;
          overflow: hidden;
        }

        .ticket-footer {
          display: flex;
          align-items: center;
          justify-content: space-between;
          margin-top: 4px;
        }

        .ticket-status {
          display: flex;
          align-items: center;
          gap: 6px;
          font-size: 13px;
          font-weight: 600;
        }

        .ticket-date {
          font-size: 12px;
          color: var(--text-muted);
        }
      `}</style>
    </div>
  );
}

