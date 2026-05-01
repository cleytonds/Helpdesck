import { useContext } from "react";
import { Link } from "react-router-dom";
import { AuthContext } from "../context/AuthContext";
import "./Dashboard.css";

// ======================================================
// Dashboard Principal
// Após login o usuário cai aqui
// ======================================================

export default function Dashboard() {
  const { user, logout } = useContext(AuthContext);

  // ======================================================
  // Logout
  // ======================================================
  function handleLogout() {
    logout();
    window.location.href = "/login";
  }

  return (
    <div className="dashboard-container">

      {/* Sidebar */}
      <aside className="sidebar">

        <div className="logo">
          <h2>HelpDesk</h2>
        </div>

        <nav className="menu">

          <Link to="/dashboard">
            Dashboard
          </Link>

          <Link to="/tickets">
            Abrir Chamado
          </Link>

          <Link to="/my-tickets">
            Meus Chamados
          </Link>

          {user?.role === "admin" && (
            <Link to="/admin/tickets">
              Painel Admin
            </Link>
          )}

        </nav>

        <button
          className="logout-btn"
          onClick={handleLogout}
        >
          Sair
        </button>

      </aside>

      {/* Conteúdo */}
      <main className="dashboard-content">

        <div className="welcome-card">

          <h1>
            Bem-vindo, {user?.name || "Usuário"}
          </h1>

          <p>
            Sistema profissional de gerenciamento de chamados.
          </p>

        </div>

        {/* Cards */}
        <div className="cards-grid">

          <div className="card">
            <h3>Chamados Abertos</h3>
            <span>12</span>
          </div>

          <div className="card">
            <h3>Em Atendimento</h3>
            <span>5</span>
          </div>

          <div className="card">
            <h3>Finalizados</h3>
            <span>24</span>
          </div>

        </div>

        {/* Atividade */}
        <div className="recent-activity">

          <h2>Atividade Recente</h2>

          <div className="activity-card">
            <p>
              Último login realizado com sucesso.
            </p>
          </div>

        </div>

      </main>

    </div>
  );
}