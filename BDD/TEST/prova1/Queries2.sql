-- Query 1

select g.nome, g.codice
from (
	select nome, codice from giocattolo where categoria != 5
) as g 
join richiesta as r on r.codiceg = g.codice
where r.preferenza <= 4

;

--Query 2

select r1.codiceg
from richiesta as r1 
join richiesta as r2 on r1.codiceb = r2.codiceb
where r1.codiceg = r2.codiceg and r1.preferenza != r2.preferenza
;

-- Query 3

select g.codice, g.categoria, avg(r.preferenza)
from richiesta as r join giocattolo as g on g.codice = r.codiceg  
group by g.codice, g.categoria

;

-- Query 4

select t.codice, avg(t.preferenza)
from ((select codice
       from bambino b1
       except
       select codiceb
       from richiesta r1 join giocattolo g1 on r1.codiceg = g1.codice and categoria <> 1) s 
	  left join richiesta r2 on r2.codiceb = s.codice) t
group by t.codice

