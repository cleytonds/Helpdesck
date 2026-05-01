// ======================================================
// Rota protegida (usuário logado)
// Bloqueia acesso sem token
// ======================================================

import { useContext } from "react";
import { Navigate } from "react-router-dom";
import { AuthContext } from "../context/AuthContext";

export default function PrivateRoute({ children }) {
  const { user, loading } = useContext(AuthContext);

  // Enquanto valida sessão
  if (loading) {
    return <div>Carregando...</div>;
  }

  // Se não estiver logado, redireciona
  if (!user) {
    return <Navigate to="/login" />;
  }

  // Se estiver logado, libera acesso
  return children;
}