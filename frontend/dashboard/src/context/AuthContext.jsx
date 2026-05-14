import { createContext, useContext, useEffect, useState } from "react";
import api from "../services/api";
import { loginRequest } from "../services/authService";

export const AuthContext = createContext();
export const useAuth = () => useContext(AuthContext);

export const AuthProvider = ({ children }) => {
  const [user, setUser] = useState(null);
  const [loading, setLoading] = useState(true);

  // ==============================
  // Carregar sessão salva
  // ==============================
  useEffect(() => {
    const token = localStorage.getItem("token");

    if (token) {
      api.defaults.headers.Authorization = `Bearer ${token}`;

      const savedUser = localStorage.getItem("user");

      if (savedUser) {
        const parsedUser = JSON.parse(savedUser);
        console.log("USER RESTAURADO:", parsedUser); // DEBUG
        setUser(parsedUser);
      }
    }

    setLoading(false);
  }, []);

  // ==============================
  // LOGIN
  // ==============================
  const login = async (email, password) => {
    try {
      const response = await loginRequest({ email, password });

      console.log("🔥 RESPONSE:", response.data);

      // ❌ LOGIN FALHOU
      if (!response.data.success) {
        return {
          success: false,
          message: response.data.message
        };
      }

      const { token, user } = response.data;

      // 🔥 VALIDAÇÃO REAL
      if (!user || !user.role) {
        console.error("ERRO: user inválido vindo do backend");
        return {
          success: false,
          message: "Erro interno (user inválido)"
        };
      }

      localStorage.setItem("token", token);
      localStorage.setItem("user", JSON.stringify(user));

      api.defaults.headers.Authorization = `Bearer ${token}`;

      setUser(user);

      return {
        success: true,
        user
      };

    } catch (error) {
      return {
        success: false,
        message: error.response?.data?.message || "Erro ao fazer login",
      };
    }
  };
  // ==============================
  // LOGOUT
  // ==============================
  const logout = () => {
    localStorage.removeItem("token");
    localStorage.removeItem("user");

    delete api.defaults.headers.Authorization;

    setUser(null);
  };

  return (
    <AuthContext.Provider
      value={{
        user,
        login,
        logout,
        isAuthenticated: !!user,
      }}
    >
      {!loading && children}
    </AuthContext.Provider>
  );
};