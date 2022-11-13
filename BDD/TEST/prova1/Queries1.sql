
select distinct * 
from bambino as b 
full join  richiesta as r on r.codiceb = b.codice
full join  giocattolo as g on g.codice = r.codiceg
;
-- Query 1

select distinct b.codice, b.nome
from bambino as b join richiesta as r on r.codiceb = b.codice
where r.preferenza >= 4 and b.citta != 'Milano'
;

-- Query 2

with bg as (
	select distinct *
	from richiesta as r
	join giocattolo as g on r.codiceg = g.codice
)

select  b1.codiceb 
from bg as b1 
join bg as b2 on b1.codiceb = b2.codiceb
where b1.categoria != b2.categoria and b1 > b2 and b1.preferenza = b2.preferenza
order by b1.codiceb
;
-- Query 3

select distinct b.codice,b.citta, count(*)
from richiesta as r 
join bambino as b on b.codice = r.codiceb 
where r.preferenza = 1
group by b.codice

union

select distinct b.codice,b.citta, 0
from richiesta as r 
join bambino as b on b.codice = r.codiceb 
group by b.codice

;

-- Query 4

select distinct b.codice, g.codice, max(r.preferenza)
from bambino as b 
join giocattolo as g 
group by b.codice, g.codice

union 

select distinct b.codice, g.codice, 0
from bambino as b 
left join richiesta as r on r.codiceb = b.codice
join giocattolo as g on g.codice = r.codiceg
where g.codice is null
group by b.codice, g.codice










