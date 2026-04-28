import TicketList from "../components/TicketList";
import "../styles/variables.css";

export default function Tickets() {
  return (
    <div className="tickets-page">
      <div className="tickets-header">
        <h1>Tickets</h1>
        <p>Gerencie todos os chamados do sistema</p>
      </div>
      <TicketList />

      <style>{`
        .tickets-header {
          padding: 28px 28px 0;
        }

        .tickets-header h1 {
          font-size: 24px;
          font-weight: 700;
          color: var(--text-primary);
          margin-bottom: 6px;
        }

        .tickets-header p {
          font-size: 14px;
          color: var(--text-secondary);
        }

        @media (max-width: 640px) {
          .tickets-header {
            padding: 20px 16px 0;
          }
        }
      `}</style>
    </div>
  );
}

