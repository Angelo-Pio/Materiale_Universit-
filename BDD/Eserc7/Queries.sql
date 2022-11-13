-- Utility Query

select distinct * from rilevazione r full join centralina c on c.codice = r.codice
full join citta as cit on cit.id = c.citta
order by cit.id

;

--Query 1

select distinct r.codice, r.valore, r.giorno
from rilevazione as r 
join centralina as c on c.codice = r.codice
join citta as cit on cit.id = c.citta
where r.valore < 1100 and cit.nome != 'Milano' and c.tipo = 200

;

--Query 2 

select distinct cit.nome
from citta as cit 
join centralina as c1 on c1.citta = cit.id
join centralina as c2 on c2.citta = cit.id 
where c1.codice != c2.codice
and c1.tipo = c2.tipo

;

-- Query 3

with cen_cit as 
(
	select distinct * 
	from citta as cit full join centralina as c on c.citta = cit.id
)

select distinct c.codice , c.regione , count( * )
from cen_cit as c 
left join rilevazione as r on c.codice = r.codice
group by c.codice, c.regione
order by c.codice 
;
-- Query 4

with rilv_gen as (

	select distinct * 
	from rilevazione where giorno >= 1 and giorno <= 31 
)

select  distinct c.codice
from rilevazione as r right join centralina as c on c.codice = r.codice
where c.codice not in (select distinct codice from rilv_gen )

;

-- Query 5 



select distinct cit.nome , min(r.giorno)
from citta as cit
join centralina as c on c.citta = cit.id
join rilevazione as r on r.codice = c.codice 
where r.valore > 500 
group by cit.nome

union

select citta.nome, null
from citta
where citta.id not in 
(
	select c1.citta
from centralina c1
join rilevazione r2 on c1.codice = r2.codice where r2.valore >
500
)

;



















