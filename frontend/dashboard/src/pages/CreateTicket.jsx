// src/pages/CreateTicket.jsx

import { useState } from "react";
import api from "../services/api";

export default function CreateTicket() {
  const [title, setTitle] = useState("");
  const [description, setDescription] = useState("");

  async function handleSubmit(e) {
    e.preventDefault();

    try {
      await api.post("/tickets", {
        title,
        description
      });

      alert("Chamado criado com sucesso");

      setTitle("");
      setDescription("");
    } catch (error) {
      console.error(error);
    }
  }

  return (
    <div>
      <h1>Novo Chamado</h1>

      <form onSubmit={handleSubmit}>
        <input
          type="text"
          placeholder="Título"
          value={title}
          onChange={(e) => setTitle(e.target.value)}
        />

        <textarea
          placeholder="Descrição"
          value={description}
          onChange={(e) => setDescription(e.target.value)}
        />

        <button type="submit">Criar Chamado</button>
      </form>
    </div>
  );
}