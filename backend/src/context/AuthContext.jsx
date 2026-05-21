import { createContext, useContext, useState } from "react";
import api from "../services/api";

const AuthContext = createContext();

export function AuthProvider({ children }) {

  const [user, setUser] = useState(() => {
    const storedUser = localStorage.getItem("user");
    return storedUser ? JSON.parse(storedUser) : null;
  });

  const [token, setToken] = useState(() => {
    return localStorage.getItem("token") || null;
  });

  // ======================================================
  // LOGIN
  // ======================================================
  async function login(email, password) {
    try {
      const response = await api.post("/login", {
        email,
        password,
      });

      const data = response.data;

      if (!data.success) {
        return {
          success: false,
          message: data.message,
        };
      }

      const userData = data.user;
      const tokenData = data.token;

      setToken(tokenData);
      setUser(userData);

      localStorage.setItem("token", tokenData);
      localStorage.setItem("user", JSON.stringify(userData));

      return {
        success: true,
        user: userData,
        token: tokenData
      };

    } catch (error) {
      return {
        success: false,
        message: "Erro ao conectar com servidor",
      };
    }
  }

  // ======================================================
  // LOGOUT
  // ======================================================
  function logout() {
    setUser(null);
    setToken(null);

    localStorage.removeItem("token");
    localStorage.removeItem("user");
  }

  return (
    <AuthContext.Provider value={{
      user,
      token,
      login,
      logout
    }}>
      {children}
    </AuthContext.Provider>
  );
}

export function useAuth() {
  return useContext(AuthContext);
}