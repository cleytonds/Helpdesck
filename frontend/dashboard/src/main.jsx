// ======================================================
// Entrada principal do React (Vite)
// ======================================================
import React from "react";
import ReactDOM from "react-dom/client";
import App from "./App";

// Estilos globais (opcional)
import "./styles/global.css";

// Renderiza aplicação React
ReactDOM.createRoot(document.getElementById("root")).render(
  <React.StrictMode>
    <App />
  </React.StrictMode>
);