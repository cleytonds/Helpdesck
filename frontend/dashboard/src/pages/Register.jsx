import { useState } from "react";
import { useNavigate, Link } from "react-router-dom";
import api from "../services/api";
import "./Auth.css";

// ======================================================
// Página de Cadastro
// ======================================================

export default function Register() {
  const navigate = useNavigate();

  // Estados do formulário
  const [formData, setFormData] = useState({
    name: "",
    email: "",
    password: "",
    confirmPassword: "",
  });

  // Controle de loading
  const [loading, setLoading] = useState(false);

  // Mensagens
  const [message, setMessage] = useState("");
  const [error, setError] = useState("");

  // ======================================================
  // Atualiza campos do formulário
  // ======================================================
  function handleChange(e) {
    setFormData({
      ...formData,
      [e.target.name]: e.target.value,
    });
  }

  // ======================================================
  // Validação Email
  // ======================================================
  function validateEmail(email) {
    return /\S+@\S+\.\S+/.test(email);
  }

  // ======================================================
  // Submit cadastro
  // ======================================================
  async function handleSubmit(e) {
    e.preventDefault();

    setError("");
    setMessage("");

    // Validação email
    if (!validateEmail(formData.email)) {
      setError("Digite um email válido.");
      return;
    }

    // Senha mínima
    if (formData.password.length < 6) {
      setError("Senha deve ter no mínimo 6 caracteres.");
      return;
    }

    // Confirmar senha
    if (formData.password !== formData.confirmPassword) {
      setError("As senhas não coincidem.");
      return;
    }

    try {
      setLoading(true);

      await api.post("/register", {
        name: formData.name,
        email: formData.email,
        password: formData.password,
      });

      setMessage(
        "Cadastro realizado com sucesso. Verifique seu email para ativar sua conta."
      );

      // Redireciona após alguns segundos
      setTimeout(() => {
        navigate("/login");
      }, 3000);

    } catch (err) {
      setError(
        err.response?.data?.message ||
        "Erro ao cadastrar usuário."
      );
    } finally {
      setLoading(false);
    }
  }

  return (
    <div className="auth-container">
      <div className="auth-card">

        <h1>Cadastro HelpDesk</h1>
        <p>Crie sua conta para abrir chamados</p>

        {error && <div className="error-box">{error}</div>}
        {message && <div className="success-box">{message}</div>}

        <form onSubmit={handleSubmit}>

          {/* Nome */}
          <div className="input-group">
            <label>Nome</label>
            <input
              type="text"
              name="name"
              placeholder="Digite seu nome"
              value={formData.name}
              onChange={handleChange}
              required
            />
          </div>

          {/* Email */}
          <div className="input-group">
            <label>Email</label>
            <input
              type="email"
              name="email"
              placeholder="Digite seu email"
              value={formData.email}
              onChange={handleChange}
              required
            />
          </div>

          {/* Senha */}
          <div className="input-group">
            <label>Senha</label>
            <input
              type="password"
              name="password"
              placeholder="Digite sua senha"
              value={formData.password}
              onChange={handleChange}
              required
            />
          </div>

          {/* Confirmar senha */}
          <div className="input-group">
            <label>Confirmar Senha</label>
            <input
              type="password"
              name="confirmPassword"
              placeholder="Repita sua senha"
              value={formData.confirmPassword}
              onChange={handleChange}
              required
            />
          </div>

          {/* Botão */}
          <button type="submit" disabled={loading}>
            {loading ? "Cadastrando..." : "Criar Conta"}
          </button>

        </form>

        <div className="auth-footer">
          <p>
            Já possui conta? <Link to="/login">Entrar</Link>
          </p>
        </div>

      </div>
    </div>
  );
}