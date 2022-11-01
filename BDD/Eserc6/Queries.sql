--Query Utily

select * from
turista as t full join visita  v on v.fisc_turista = t.codfiscale
full join viaggio as vg on vg.codice = v.viaggio
;

-- Es 2


create or replace function citta_visitate(turista varchar)
returns table (citta varchar, tur varchar) as 
$$
	declare r record;
	begin
		return query
		select visita.citta , turista from visita where visita.fisc_turista = turista;
		
	end;
$$ language plpgsql;

select * from citta_visitate('10');

-- Es 3

create or replace function sum_viaggi() returns trigger as
$$
	declare r record ;
	begin
		for r in 
			select distinct t.codFiscale, count(v.viaggio) as counter 
			from turista as t 
			left join visita as v on v.fisc_turista = t.codFiscale
			group by t.codFiscale
			
			loop
			
			update turista set quantiviaggi = r.counter where turista.codFiscale = r.codFiscale;
		end loop;
		return null;
	end;
$$ language plpgsql;

create or replace trigger aggiorna_quantiviaggi after insert on turista
for each row execute procedure sum_viaggi();



-- Es 4

create or replace function upd_viaggio() returns trigger as 
$$
	declare r record;
	begin
		for r in 
			select distinct v.codice , sum(vis.costo) as somma 
			from viaggio as v left join visita as vis on vis.viaggio = v.codice
			group by v.codice
		loop
			update Viaggio set incasso = r.somma where codice = r.codice;
		end loop;
		return null;
		
	end;
$$ language plpgsql;




create or replace trigger i_incasso after insert on viaggio
for each row execute procedure upd_viaggio();


create or replace trigger d_incasso after delete on viaggio
for each row execute procedure upd_viaggio();


















