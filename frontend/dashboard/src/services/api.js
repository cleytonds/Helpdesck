// src/services/api.js

import axios from "axios";

// Instância global do Axios
// Responsável por conectar frontend ao backend C++
const api = axios.create({
  baseURL: "http://localhost:9090",
  headers: {
    "Content-Type": "application/json"
  }
});

export default api;