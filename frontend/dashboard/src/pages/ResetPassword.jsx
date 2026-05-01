import { useState } from "react";
import { useSearchParams, useNavigate } from "react-router-dom";
import api from "../services/api";

export default function ResetPassword() {
  const [searchParams] = useSearchParams();
  const navigate = useNavigate();

  const token = searchParams.get("token");

  const [password, setPassword] = useState("");
  const [message, setMessage] = useState("");

  async function handleSubmit(e) {
    e.preventDefault();

    try {
      await api.post("/auth/reset-password", {
        token,
        password,
      });

      setMessage("Senha redefinida com sucesso!");

      setTimeout(() => {
        navigate("/login");
      }, 2000);

    } catch (err) {
      setMessage("Erro ao redefinir senha.");
    }
  }

  return (
    <div className="auth-container">
      <div className="auth-card">

        <h1>Nova Senha</h1>

        {message && <p>{message}</p>}

        <form onSubmit={handleSubmit}>

          <input
            type="password"
            placeholder="Nova senha"
            value={password}
            onChange={(e) => setPassword(e.target.value)}
          />

          <button>
            Redefinir senha
          </button>

        </form>

      </div>
    </div>
  );
}