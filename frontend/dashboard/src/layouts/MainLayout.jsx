import { Outlet, useLocation } from "react-router-dom";
import Sidebar from "../components/Sidebar";
import Topbar from "../components/Topbar";
import "../styles/variables.css";

const titles = {
  "/": "Dashboard",
  "/tickets": "Tickets",
};

export default function MainLayout() {
  const location = useLocation();
  const title = titles[location.pathname] || "HelpDesk";

  return (
    <div className="main-layout">
      <Sidebar />
      <div className="main-content">
        <Topbar title={title} />
        <main className="page-area">
          <Outlet />
        </main>
      </div>

      <style>{`
        .main-layout {
          display: flex;
          width: 100%;
          min-height: 100vh;
        }

        .main-content {
          flex: 1;
          margin-left: var(--sidebar-width);
          display: flex;
          flex-direction: column;
          min-height: 100vh;
        }

        .page-area {
          flex: 1;
          background: var(--main-bg);
        }

        @media (max-width: 768px) {
          .main-content {
            margin-left: 0;
          }
        }
      `}</style>
    </div>
  );
}

