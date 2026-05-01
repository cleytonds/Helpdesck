// ======================================================
// Configuração global do Axios
// ======================================================

import axios from "axios";

// ======================================================
// Instância principal API
// ======================================================

const api = axios.create({
  baseURL: "http://localhost:9090",
  headers: {
    "Content-Type": "application/json",
  },
  timeout: 10000, // evita request infinito
});

// ======================================================
// REQUEST INTERCEPTOR
// Adiciona JWT automaticamente
// ======================================================

api.interceptors.request.use(
  (config) => {
    const token = localStorage.getItem("token");

    if (token) {
      config.headers.Authorization = `Bearer ${token}`;
    }

    return config;
  },
  (error) => Promise.reject(error)
);

// ======================================================
// RESPONSE INTERCEPTOR
// Trata token expirado / backend offline
// ======================================================

api.interceptors.response.use(
  (response) => response,

  (error) => {
    // Token expirado
    if (error.response?.status === 401) {
      localStorage.removeItem("token");
      localStorage.removeItem("user");

      window.location.href = "/login";
    }

    // Backend offline
    if (error.code === "ECONNABORTED") {
      console.error("Timeout backend");
    }

    if (!error.response) {
      console.error("Backend indisponível");
    }

    return Promise.reject(error);
  }
);

export default api;