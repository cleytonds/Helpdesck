import { Navigate, BrowserRouter, Routes, Route } from "react-router-dom";

// Context
import { AuthProvider } from "./context/AuthContext";

// Pages
import Login from "./pages/Login";
import Register from "./pages/Register";
import Dashboard from "./pages/Dashboard";
import Tickets from "./pages/Tickets";
import MyTickets from "./pages/MyTickets";
import History from "./pages/History";

import AdminDashboard from "./pages/AdminDashboard";
import AdminTickets from "./pages/AdminTickets";
import VerifyEmail from "./pages/VerifyEmail";
import ForgotPassword from "./pages/ForgotPassword";
import ResetPassword from "./pages/ResetPassword";


// Routes protegidas
import PrivateRoute from "./routes/PrivateRoute";
import AdminRoute from "./routes/AdminRoute";

export default function App() {
  return (
    <AuthProvider>
      <BrowserRouter>
        <Routes>

          {/* ===================== */}
          {/* REDIRECT INICIAL */}
          {/* ===================== */}
          <Route path="/" element={<Navigate to="/login" replace />} />

          {/* ===================== */}
          {/* PUBLIC */}
          {/* ===================== */}
          <Route path="/login" element={<Login />} />
          <Route path="/register" element={<Register />} />
          <Route path="/verify-email/:token" element={<VerifyEmail />} />
          <Route path="/forgot-password" element={<ForgotPassword />} />
          <Route path="/reset-password" element={<ResetPassword />} />
          <Route path="/admin/tickets" element={<AdminTickets />} />

          {/* ===================== */}
          {/* USER (LOGADO) */}
          {/* ===================== */}
          <Route
            path="/dashboard"
            element={
              <PrivateRoute>
                <Dashboard />
              </PrivateRoute>
            }
          />

          <Route
            path="/tickets"
            element={
              <PrivateRoute>
                <Tickets />
              </PrivateRoute>
            }
          />

          {/* ===================== */}
          {/* USER PAGES */}
          {/* ===================== */}
          <Route
            path="/my-tickets"
            element={
              <PrivateRoute>
                <MyTickets />
              </PrivateRoute>
            }
          />

          <Route
            path="/tickets/history"
            element={
              <PrivateRoute>
                <History />
              </PrivateRoute>
            }
          />

          {/* ===================== */}
          {/* ADMIN DASHBOARD */}
          {/* ===================== */}
          <Route
            path="/admin/dashboard"
            element={
              <AdminRoute>
                <AdminDashboard />
              </AdminRoute>
            }
          />


          {/* ===================== */}
          {/* ADMIN TICKETS */}
          {/* ===================== */}
          <Route
            path="/admin/tickets"
            element={
              <AdminRoute>
                <AdminTickets />
              </AdminRoute>
            }
          />

          {/* ===================== */}
          {/* FALLBACK */}
          {/* ===================== */}
          <Route path="*" element={<Navigate to="/login" replace />} />

        </Routes>
      </BrowserRouter>
    </AuthProvider>
  );
}