import TicketList from "../components/TicketList";
import "../styles/variables.css";

export default function Dashboard() {
  return (
    <div className="dashboard-page">
      <div className="dashboard-header">
        <h1>Tickets</h1>
        <p>Visão geral dos chamados mais recentes</p>
      </div>
      <TicketList />

      <style>{`
        .dashboard-header {
          padding: 28px 28px 0;
        }

        .dashboard-header h1 {
          font-size: 24px;
          font-weight: 700;
          color: var(--text-primary);
          margin-bottom: 6px;
        }

        .dashboard-header p {
          font-size: 14px;
          color: var(--text-secondary);
        }

        @media (max-width: 640px) {
          .dashboard-header {
            padding: 20px 16px 0;
          }
        }
      `}</style>
    </div>
  );
}

