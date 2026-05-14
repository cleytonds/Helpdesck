<section>
  <h2>Histórico de Chamados</h2>

  <div className="simple-grid">
    {historico.map((h) => (
      <div key={h.id} className="mini-card">

        <strong>Ticket #{h.ticket_id}</strong>
        <p>{h.ticket_title}</p>

        <p>
          {h.old_status} → {h.new_status}
        </p>

        <small>
          por {h.changed_by_name}
        </small>

        <br />

        <small>
          {h.changed_at}
        </small>

      </div>
    ))}
  </div>
</section>