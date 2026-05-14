import { useState } from "react";
import { Link, useNavigate } from "react-router-dom";
import { useAuth } from "../context/AuthContext";
import "./Auth.css";

export default function Login() {
  const navigate = useNavigate();
  const { login } = useAuth();

  const [formData, setFormData] = useState({
    email: "",
    password: "",
  });

  const [loading, setLoading] = useState(false);
  const [error, setError] = useState("");

  function handleChange(e) {
    setFormData({
      ...formData,
      [e.target.name]: e.target.value,
    });
  }

  async function handleSubmit(e) {
    e.preventDefault();
    setError("");

    try {
      setLoading(true);

      const result = await login(
        formData.email,
        formData.password
      );

      // ❌ login falhou
      if (!result.success) {
        setError(result.message);
        return;
      }

      console.log("LOGIN RESULT:", result);

      const role = result.user?.role;
      console.log (role);

      // 🔥 REDIRECIONAMENTO CORRETO
      if (role === "admin") {
        navigate("/admin/dashboard");
      } else {
        navigate("/dashboard");
      }
    } catch (err) {
      console.error(err);
      setError("Erro ao realizar login.");
    } finally {
      setLoading(false);
    }
  }

  return (
    <div className="auth-container">
      <div className="auth-card">

        <h1>Login HelpDesk</h1>

        {error && (
          <div className="error-box">
            {error}
          </div>
        )}

        <form onSubmit={handleSubmit}>

          <input
            type="email"
            name="email"
            placeholder="Email"
            value={formData.email}
            onChange={handleChange}
            required
          />

          <input
            type="password"
            name="password"
            placeholder="Senha"
            value={formData.password}
            onChange={handleChange}
            required
          />

          <button disabled={loading}>
            {loading ? "Entrando..." : "Entrar"}
          </button>

        </form>

        <div className="auth-links">

          <Link to="/register">
            Criar conta
          </Link>

          <Link to="/forgot-password">
            Esqueci minha senha
          </Link>

        </div>

      </div>
    </div>
  );
}