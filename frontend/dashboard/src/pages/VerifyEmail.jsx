import { useEffect, useState } from "react";
import { useNavigate, useParams } from "react-router-dom";
import api from "../services/api";
import "./VerifyEmail.css";

// ======================================================
// Página de verificação de email
// Fluxo:
// Usuário recebe link no email
// Ex:
// /verify-email/token123
// ======================================================

export default function VerifyEmail() {
  const { token } = useParams();
  const navigate = useNavigate();

  // ======================================================
  // Estados
  // ======================================================
  const [loading, setLoading] = useState(true);
  const [success, setSuccess] = useState(false);
  const [message, setMessage] = useState("");

  // ======================================================
  // Validar token
  // ======================================================
  useEffect(() => {
    async function verifyAccount() {
      try {
        const response = await api.get(
          `/verify-email/${token}`
        );

        setSuccess(true);

        setMessage(
          response.data.message ||
          "Conta ativada com sucesso."
        );

        // Redireciona para login
        setTimeout(() => {
          navigate("/login");
        }, 4000);

      } catch (error) {
        setSuccess(false);

        setMessage(
          error.response?.data?.message ||
          "Token inválido ou expirado."
        );
      } finally {
        setLoading(false);
      }
    }

    verifyAccount();
  }, [token, navigate]);

  return (
    <div className="verify-container">

      <div className="verify-card">

        {loading ? (
          <>
            <h1>Verificando conta...</h1>
            <p>Aguarde alguns segundos.</p>
          </>
        ) : success ? (
          <>
            <h1>Conta Ativada</h1>

            <div className="success-box">
              {message}
            </div>

            <p>
              Você será redirecionado para login.
            </p>
          </>
        ) : (
          <>
            <h1>Falha na Verificação</h1>

            <div className="error-box">
              {message}
            </div>

            <button
              onClick={() => navigate("/register")}
            >
              Criar nova conta
            </button>
          </>
        )}

      </div>

    </div>
  );
}