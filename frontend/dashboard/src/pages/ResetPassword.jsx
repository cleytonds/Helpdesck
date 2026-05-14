import { useState } from "react";
import { useParams, useNavigate } from "react-router-dom";
import api from "../services/api";
import "./Auth.css";

export default function ResetPassword() {
  const { token } = useParams();
  const navigate = useNavigate();

  const [password, setPassword] = useState("");
  const [confirmPassword, setConfirmPassword] = useState("");
  const [message, setMessage] = useState("");
  const [error, setError] = useState("");
  const [loading, setLoading] = useState(false);

  async function handleSubmit(e) {
    e.preventDefault();

    setError("");
    setMessage("");

    if (password.length < 6) {
      setError("Senha deve ter no mínimo 6 caracteres");
      return;
    }

    if (password !== confirmPassword) {
      setError("As senhas não coincidem");
      return;
    }

    try {
      setLoading(true);

      await api.post("/reset-password", {
        token,
        password,
      });

      setMessage("Senha redefinida com sucesso!");

      setTimeout(() => {
        navigate("/login");
      }, 2000);

    } catch (err) {
      setError("Erro ao redefinir senha.");
    } finally {
      setLoading(false);
    }
  }

  return (
    <div className="auth-container">
      <div className="auth-card">

        <h1>Nova Senha</h1>
        <p>Digite sua nova senha</p>

        {error && <div className="error-box">{error}</div>}
        {message && <div className="success-box">{message}</div>}

        <form onSubmit={handleSubmit}>

          <input
            type="password"
            placeholder="Nova senha"
            value={password}
            onChange={(e) => setPassword(e.target.value)}
            required
          />

          <input
            type="password"
            placeholder="Confirmar senha"
            value={confirmPassword}
            onChange={(e) => setConfirmPassword(e.target.value)}
            required
          />

          <button disabled={loading}>
            {loading ? "Redefinindo..." : "Redefinir senha"}
          </button>

        </form>

      </div>
    </div>
  );
}