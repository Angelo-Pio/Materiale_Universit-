-- Utility 

select * from composizione c full join band as b on b.id = c.id full join musicista as m on m.codice = c.codice;

-- Query 1

select distinct m.codice , m.nome 
from musicista as m join composizione as c on c.codice = m.codice
where m.ruolopreferito = c.ruolo

;

--Query 2

select distinct m.codice , m.ruolopreferito , count( distinct c.id)
from musicista as m left join composizione as c on c.codice = m.codice
where m.ruolopreferito = 'chitarrista' or m.ruolopreferito = 'bassista'
group by m.codice

;
-- Query 3

select distinct m.codice , m.nome 
from musicista as m join composizione as c on c.codice = m.codice
join band as b on b.id = c.id
where b.annoinizio > 2000
;
-- Query 4

select distinct m.codice, count(distinct c.id)
from musicista as m join composizione as c on c.codice = m.codice
where c.ruolo = m.ruolopreferito
group by m.codice

;

-- Query 5

select distinct m.codice
from musicista as m 
join composizione as c on c.codice = m.codice
where m.ruolopreferito != c.ruolo 
and m.codice not in (

	select distinct m.codice
	from musicista as m 
	join composizione as c on c.codice = m.codice
	join composizione as c2 on c2.codice = m.codice 
	where 
	c2.ruolo != c.ruolo and c2.codice = c.codice 

)
;
-- Query 6

select distinct b.id , b.nome
from band as b join composizione as c on c.id = b.id
where b.annoinizio > 2000
group by b.id
having count(distinct c.codice) >= 3

;

--Query 7

with ban_3 as (
	
	select distinct b.id , b.nome
from band as b join composizione as c on c.id = b.id
group by b.id
having count(distinct c.codice) >= 3


)

select distinct  c1.codice, c2.codice
from composizione as c1 
join composizione as c2 on c1.codice != c2.codice and c1.id = c2.id
join ban_3 as b on b.id = c1.id and b.id = c2.id
where c1.codice < c2.codice
order by c1.codice
;
-- QUery 8

with mus_band as (
select distinct m.codice, b.annoinizio
from musicista as m 
left join composizione as c on c.codice = m.codice
left join band as b on b.id = c.id 
)

select b2.codice , max(b2.annoinizio)
from mus_band as b2
group by b2.codice
order by b2.codice
;
-- Query 9

select distinct b.id, count( distinct m.codice)
from band as b 
left join composizione as c on c.id = b.id 
left join musicista as m on m.codice = c.codice
where c.ruolo = m.ruolopreferito
group by b.id

union 


select distinct b.id, 0
from band as b 
left join composizione as c on c.id = b.id 
left join musicista as m on m.codice = c.codice
where 	b.id not in (
		
		select distinct c.id
		from musicista as m 
		join composizione as c on c.codice = m.codice
		where c.ruolo = m.ruolopreferito
		group by c.id 
	)
	
;

-- Query 10








