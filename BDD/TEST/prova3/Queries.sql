-- Utility Queries 

select distinct citta.id, citta.nome, citta.regione, centralina.codice, centralina.tipo, rilevazione.giorno,rilevazione.valore from citta 
full join centralina on citta.id = centralina.citta
full join rilevazione on rilevazione.codice = centralina.codice
order by citta.nome
;

-- Query 1

select r.codice , r.giorno, r.valore
from rilevazione as r
join centralina as c on r.codice = c.codice
join citta as ci on ci.id = c.citta
where r.valore < 1100 and c.tipo = 200 and c.citta != 'Milano'

;

-- Query 2

select distinct c.nome
from citta as c 
join centralina as cent on cent.citta = c.id
join centralina as c2 on c2.citta !=cent.citta and c2.tipo = cent.tipo
join centralina as c3 on c3.citta != c2.citta and c3.citta != cent.citta and c3.tipo = cent.tipo

;
-- Query 3

with cnt as (select distinct codice, count( *) as cnt from rilevazione group by codice)


select distinct cent.codice , cit.regione, r.cnt
from centralina as cent left join citta as cit on cit.id = cent.citta 
left join cnt as r on r.codice = cent.codice



-- OPPURE/MEGLIO

select c.codice, ci.regione, count(*)
from rilevazione r join centralina c on r.codice = c.codice
join citta ci on ci.id = c.citta
group by c.codice, ci.regione

union

select c1.codice, ci1.regione, 0
from centralina c1 join citta ci1 on c1.citta = ci1.id
where c1.codice not in (select r1.codice from rilevazione r1)
;

--Query 4

select distinct c.codice
from centralina as c left join rilevazione as r on r.codice = c.codice
where c.codice not in 
(
	select distinct c.codice
	from centralina as c left join rilevazione as r on r.codice = c.codice
	where r.giorno >= 1 and r.giorno <= 31
)

-- Query 5

