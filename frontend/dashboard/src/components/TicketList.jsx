import TicketCard from "./TicketCard";
import "../styles/variables.css";

const mockTickets = [
  {
    id: 101,
    titulo: "Erro ao acessar relatórios",
    descricao: "Usuário não consegue gerar o relatório mensal de vendas no sistema.",
    status: "aberto",
    prioridade: "alta",
    data: "Hoje, 10:23",
  },
  {
    id: 102,
    titulo: "Solicitação de novo acesso",
    descricao: "Novo colaborador precisa de credenciais para acessar a plataforma interna.",
    status: "em_andamento",
    prioridade: "media",
    data: "Ontem, 16:45",
  },
  {
    id: 103,
    titulo: "Impressora não responde",
    descricao: "A impressora do setor financeiro está offline desde ontem de manhã.",
    status: "resolvido",
    prioridade: "baixa",
    data: "15 Jun, 09:10",
  },
  {
    id: 104,
    titulo: "Queda de conexão no servidor principal",
    descricao: "Intermitência na conexão com o servidor de banco de dados.",
    status: "urgente",
    prioridade: "alta",
    data: "Hoje, 08:05",
  },
  {
    id: 105,
    titulo: "Atualização de software",
    descricao: "Solicitação para atualizar o pacote Office em 15 máquinas.",
    status: "aberto",
    prioridade: "media",
    data: "14 Jun, 14:30",
  },
  {
    id: 106,
    titulo: "Troca de mouse defeituoso",
    descricao: "Mouse com duplo-clique automático no setor de RH.",
    status: "resolvido",
    prioridade: "baixa",
    data: "13 Jun, 11:20",
  },
];

export default function TicketList() {
  return (
    <div className="ticket-list">
      {mockTickets.map((ticket) => (
        <TicketCard key={ticket.id} ticket={ticket} />
      ))}

      <style>{`
        .ticket-list {
          display: grid;
          grid-template-columns: repeat(auto-fill, minmax(300px, 1fr));
          gap: 20px;
          padding: 24px 28px;
        }

        @media (max-width: 640px) {
          .ticket-list {
            grid-template-columns: 1fr;
            padding: 16px;
          }
        }
      `}</style>
    </div>
  );
}

