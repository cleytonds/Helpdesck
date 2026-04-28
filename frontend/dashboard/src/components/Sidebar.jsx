import { useState } from "react";
import { NavLink } from "react-router-dom";
import { LayoutDashboard, Ticket, Menu, X } from "lucide-react";
import "../styles/variables.css";

const navItems = [
  { to: "/", icon: LayoutDashboard, label: "Dashboard" },
  { to: "/tickets", icon: Ticket, label: "Tickets" },
];

export default function Sidebar() {
  const [open, setOpen] = useState(false);

  return (
    <>
      <button
        className="sidebar-toggle"
        onClick={() => setOpen(!open)}
        aria-label="Toggle menu"
      >
        {open ? <X size={24} /> : <Menu size={24} />}
      </button>

      <aside className={`sidebar ${open ? "open" : ""}`}>
        <div className="sidebar-brand">
          <h1>HelpDesk</h1>
        </div>
        <nav className="sidebar-nav">
          {navItems.map((item) => (
            <NavLink
              key={item.to}
              to={item.to}
              className={({ isActive }) =>
                `sidebar-link ${isActive ? "active" : ""}`
              }
              onClick={() => setOpen(false)}
            >
              <item.icon size={20} />
              <span>{item.label}</span>
            </NavLink>
          ))}
        </nav>
      </aside>

      <style>{`
        .sidebar {
          position: fixed;
          top: 0;
          left: 0;
          width: var(--sidebar-width);
          height: 100vh;
          background: var(--sidebar-bg);
          color: var(--sidebar-text);
          display: flex;
          flex-direction: column;
          padding: 24px 16px;
          z-index: 1000;
          transition: transform 0.3s ease;
        }

        .sidebar-brand h1 {
          font-size: 22px;
          font-weight: 700;
          letter-spacing: 0.5px;
          margin-bottom: 32px;
          padding: 0 8px;
        }

        .sidebar-nav {
          display: flex;
          flex-direction: column;
          gap: 8px;
        }

        .sidebar-link {
          display: flex;
          align-items: center;
          gap: 12px;
          padding: 12px 16px;
          border-radius: var(--radius-sm);
          color: rgba(255,255,255,0.85);
          font-size: 15px;
          font-weight: 500;
          transition: background 0.2s, color 0.2s;
        }

        .sidebar-link:hover {
          background: var(--sidebar-hover);
          color: #fff;
        }

        .sidebar-link.active {
          background: var(--sidebar-hover);
          color: #fff;
        }

        .sidebar-toggle {
          display: none;
          position: fixed;
          top: 16px;
          left: 16px;
          z-index: 1100;
          background: var(--sidebar-bg);
          color: #fff;
          padding: 10px;
          border-radius: var(--radius-sm);
          box-shadow: 0 2px 8px rgba(0,0,0,0.2);
        }

        @media (max-width: 768px) {
          .sidebar {
            transform: translateX(-100%);
          }
          .sidebar.open {
            transform: translateX(0);
          }
          .sidebar-toggle {
            display: block;
          }
        }
      `}</style>
    </>
  );
}

