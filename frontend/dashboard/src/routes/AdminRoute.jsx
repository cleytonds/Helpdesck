// ======================================================
// Rota protegida para ADMIN
// Somente usuários com role = "admin"
// ======================================================

import { useContext } from "react";
import { Navigate } from "react-router-dom";
import { AuthContext } from "../context/AuthContext";

export default function AdminRoute({ children }) {
  const { user, loading } = useContext(AuthContext);

  // Enquanto carrega sessão
  if (loading) {
    return <div>Carregando...</div>;
  }

  // Se não estiver logado
  if (!user) {
    return <Navigate to="/login" />;
  }

  // Se não for admin
  if (user.role !== "admin") {
    return <Navigate to="/dashboard" />;
  }

  // Libera acesso admin
  return children;
}