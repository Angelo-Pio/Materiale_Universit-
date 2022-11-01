-- Query Utils

select * from firma full join giornalista on giornalista.codice = firma.codice
full join testata on testata.nome = firma.nome
order by firma.codice;

-- QUery 1

select distinct g.codice ,g.cittanascita
from firma as f join giornalista as g on g.codice = f.codice
where f.anno >= 2000
;

-- Query 2

select distinct t.nome
from testata as t join firma as f on f.nome = t.nome
;


--Query 3

select distinct g.codice , sum(f.articoli)
from giornalista as g left join firma as f on f.codice = g.codice 
left join testata as t on t.nome = f.nome
where t.citta = g.cittanascita
group by g.codice
;

-- Query 4



select distinct t.nome
from testata as t left join firma as f on f.nome = t.nome
left join giornalista as g on g.codice = f.codice
where g.codice not in (select codice from giornalista where orientamento != 'sinistra'
)
;
-- Query 5

select distinct t.nome , f.anno
from testata as t left join firma as f  on f.nome = t.nome
where f.codice = t.direttore


select q.nome , max(.)

from (
	select f.anno, f.articoli, t.nome
	from firma as f right join testata as t on t.nome = 
) as q





















