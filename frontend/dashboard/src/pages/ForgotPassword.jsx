import { useState } from "react";
import api from "../services/api";
import "./ForgotPassword.css";

// ======================================================
// Página de recuperação de senha
// ======================================================

export default function ForgotPassword() {
  const [email, setEmail] = useState("");
  const [message, setMessage] = useState("");
  const [loading, setLoading] = useState(false);

  async function handleSubmit(e) {
    e.preventDefault();

    try {
      setLoading(true);

      await api.post("/auth/forgot-password", {
        email,
      });

      setMessage("Email enviado! Verifique sua caixa de entrada.");

    } catch (err) {
      setMessage("Erro ao enviar email.");
    } finally {
      setLoading(false);
    }
  }

  return (
    <div className="auth-container">
      <div className="auth-card">

        <h1>Recuperar Senha</h1>

        {message && <p>{message}</p>}

        <form onSubmit={handleSubmit}>

          <input
            type="email"
            placeholder="Seu email"
            value={email}
            onChange={(e) => setEmail(e.target.value)}
          />

          <button disabled={loading}>
            {loading ? "Enviando..." : "Enviar"}
          </button>

        </form>

      </div>
    </div>
  );
}