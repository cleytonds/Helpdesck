import { useState } from "react";
import api from "../services/api";
import "./ForgotPassword.css";

// ======================================================
// Página: Recuperação de Senha
// - Envia email para backend
// - Backend é responsável por gerar token e enviar email
// ======================================================

export default function ForgotPassword() {
  // ======================================================
  // STATES
  // ======================================================
  const [email, setEmail] = useState("");
  const [message, setMessage] = useState("");
  const [loading, setLoading] = useState(false);

  // ======================================================
  // SUBMIT
  // ======================================================
  async function handleSubmit(e) {
    e.preventDefault();

    setMessage("");

    try {
      setLoading(true);

      // ==================================================
      // CHAMADA API
      // ==================================================
      const response = await api.post("/forgot-password", {
        email,
      });

      // ==================================================
      // SUCESSO
      // ==================================================
      setMessage(
        response.data?.message ||
        "Link de recuperação enviado para seu email."
      );

    } catch (err) {
      // ==================================================
      // ERRO
      // ==================================================
      setMessage(
        err.response?.data?.message ||
        "Erro ao enviar email. Tente novamente."
      );
    } finally {
      setLoading(false);
    }
  }

  // ======================================================
  // UI
  // ======================================================
  return (
    <div className="auth-container">
      <div className="auth-card">

        <h1>Recuperar Senha</h1>
        <p>Informe seu email para receber o link de recuperação</p>

        {/* Mensagem */}
        {message && (
          <div className="info-box">
            {message}
          </div>
        )}

        <form onSubmit={handleSubmit}>

          {/* Email */}
          <input
            type="email"
            placeholder="Seu email"
            value={email}
            onChange={(e) => setEmail(e.target.value)}
            required
          />

          {/* Botão */}
          <button disabled={loading}>
            {loading ? "Enviando..." : "Enviar link"}
          </button>

        </form>

      </div>
    </div>
  );
}