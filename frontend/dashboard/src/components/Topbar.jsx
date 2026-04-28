import { Bell, User } from "lucide-react";
import "../styles/variables.css";

export default function Topbar({ title }) {
  return (
    <header className="topbar">
      <h2 className="topbar-title">{title}</h2>
      <div className="topbar-actions">
        <button className="topbar-btn" aria-label="Notificações">
          <Bell size={20} />
        </button>
        <button className="topbar-btn" aria-label="Perfil">
          <User size={20} />
        </button>
      </div>

      <style>{`
        .topbar {
          height: var(--topbar-height);
          background: var(--topbar-bg);
          border-bottom: 1px solid var(--topbar-border);
          display: flex;
          align-items: center;
          justify-content: space-between;
          padding: 0 28px;
          position: sticky;
          top: 0;
          z-index: 500;
        }

        .topbar-title {
          font-size: 20px;
          font-weight: 600;
          color: var(--text-primary);
        }

        .topbar-actions {
          display: flex;
          align-items: center;
          gap: 12px;
        }

        .topbar-btn {
          width: 38px;
          height: 38px;
          display: flex;
          align-items: center;
          justify-content: center;
          border-radius: var(--radius-sm);
          color: var(--text-secondary);
          background: transparent;
          transition: background 0.2s, color 0.2s;
        }

        .topbar-btn:hover {
          background: var(--main-bg);
          color: var(--text-primary);
        }
      `}</style>
    </header>
  );
}

