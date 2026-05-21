import { useState } from "react";
import { NavLink } from "react-router-dom";
import { Menu, X, LayoutDashboard, Ticket, Shield } from "lucide-react";
import { useAuth } from "../context/AuthContext";
import "../styles/variables.css";

export default function Sidebar() {
  const [open, setOpen] = useState(false);
  const { user } = useAuth();

  // 🔥 MENU DINÂMICO
  const navItems =
    user?.role === "admin"
      ? [
          { to: "/admin", icon: Shield, label: "Painel Admin" },
        ]
      : [
          { to: "/dashboard", icon: LayoutDashboard, label: "Dashboard" },
          { to: "/tickets", icon: Ticket, label: "Tickets" },
        ];

  return (
    <>
      {/* BOTÃO MOBILE */}
      <button
        className="sidebar-toggle"
        onClick={() => setOpen(!open)}
      >
        {open ? <X size={24} /> : <Menu size={24} />}
      </button>

      {/* SIDEBAR */}
      <aside className={`sidebar ${open ? "open" : ""}`}>

        <div className="sidebar-header">
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
              <item.icon size={18} />
              <span>{item.label}</span>
            </NavLink>
          ))}
        </nav>

      </aside>

      {/* ESTILO */}
      <style>{`
        .sidebar {
          position: fixed;
          top: 0;
          left: 0;
          width: 240px;
          height: 100vh;
          background: #0f172a;
          color: #fff;
          padding: 20px;
          display: flex;
          flex-direction: column;
          z-index: 1000;
          transition: transform 0.3s ease;
        }

        .sidebar-header h1 {
          font-size: 22px;
          margin-bottom: 30px;
        }

        .sidebar-nav {
          display: flex;
          flex-direction: column;
          gap: 10px;
        }

        .sidebar-link {
          display: flex;
          align-items: center;
          gap: 10px;
          padding: 10px;
          border-radius: 8px;
          color: rgba(255,255,255,0.8);
          text-decoration: none;
        }

        .sidebar-link:hover {
          background: #1e293b;
          color: #fff;
        }

        .sidebar-link.active {
          background: #3b82f6;
          color: #fff;
        }

        .sidebar-toggle {
          position: fixed;
          top: 15px;
          left: 15px;
          z-index: 1100;
          background: #0f172a;
          color: #fff;
          border: none;
          padding: 8px;
          border-radius: 6px;
        }

        @media (max-width: 768px) {
          .sidebar {
            transform: translateX(-100%);
          }

          .sidebar.open {
            transform: translateX(0);
          }
        }
      `}</style>
    </>
  );
}