/*Utilty Query*/

select * 
from comune
full join utente on utente.comune = comune.nome
full join segue on segue.follower = utente.id;


/* Query 1 */

select distinct u.id as follower , s.utente as utente
from utente as u 
left join segue as s on u.id = s.follower
where s.utente in 
(
 select utente.id
 from utente 
 left join comune on utente.comune = comune.nome
 where comune.regione = 'Lazio'

) order by u.id;

/* Query 2 */


select distinct u.id as follower , u2.id as utente
from utente as u
left join segue as s on s.follower = u.id
right join utente as u2 on u2.id = s.utente
where (u2.eta < u.eta and u2.comune != u.comune)
order by u.id;

/* Query 3 */

with mutualfollow as (
select distinct ut1.id as u1, ut1.comune as u1_c , ut2.id as u2, ut2.comune as u2_c
	from segue as s1
	join segue as s2 on s1.utente = s2.follower and s2.utente = s1.follower
	join utente as ut1 on ut1.id = s1.follower 
	join utente as ut2 on ut2.id = s2.follower
)

select m.u1 , m.u2
from mutualfollow as m
join comune as c1 on c1.nome = m.u1_c
join comune as c2 on c2.nome = m.u2_c
where c1.provincia != c2.provincia and c1.regione = c2.regione and m.u1 < m.u2
;

/* Query 4 */

(

select utente.id , count(distinct segue.follower) as cnt
from utente
left join segue on utente.id = segue.utente 
group by utente.id

) order by id
;


/* Query 5 */



select distinct u.id , count(distinct segue.follower) as cnt
from utente as u
left join segue on u.id = segue.utente 
where u.eta > (
	select eta
	from utente as u2 
	where u2.id = segue.follower
) and
u.comune = (
	select u2.comune
	from utente as u2
	where u2.id = segue.follower
)
group by u.id

;
/* Query 6 */

with ut_regione as (
select distinct u.id , c.nome , c.regione
from utente as u
left join comune as c on c.nome = u.comune

)
(
select distinct reg1.id
from ut_regione as reg1
left join segue as s on s.utente = reg1.id

except 

select distinct reg1.id
from ut_regione as reg1
 join segue as s on s.utente = reg1.id
left join ut_regione as reg2 on s.follower = reg2.id
where reg2.regione != reg1.regione) order by id
;
/* Query 7 */

with regione as 
(
	select distinct regione
	from comune

)


select distinct regione, avg(num_com)
from (
	select provincia, regione.regione, count(comune.nome) as num_com
	from comune 
	join regione on regione.regione = comune.regione
	group by provincia, regione.regione) as prov
group by regione
order by regione

;


/* Query 8 */
with folfedele as (
	select distinct s.follower as id 
	from segue as s
	group by s.follower
	having count(s.utente) = 1
	order by s.follower
)





-- right join?

select  distinct u.id
	from segue as s
	join utente as u on s.utente = u.id
	
	where s.follower in (
		select id
		from folfedele	
	)
	
	except

-- utenti che hanno follower non fedeli
	select  distinct u.id
	from segue as s
	join utente as u on s.utente = u.id
	
	where s.follower in (
		-- follower non fedeli
		select follower
		from segue as s 

		except 

		select id
		from folfedele	
	)

;
/* Query 9 */

-- per ottenere numero di residenti in una regione
with res_regione as 
(
	select distinct c.regione, count(distinct u.id) as num_res
	from comune as c join utente as u on u.comune = c.nome
	group by c.regione
),num_foll as (
	
	select u.id , c2.regione , count(distinct u2.id ) as cnt
	from utente as u join segue as s on s.utente = u.id
	join utente as u2 on s.follower = u2.id
	join comune as c on c.nome = u.comune
	join comune as c2 on c2.nome = u2.comune
	where c.regione = c2.regione
	group by u.id,  c2.regione
	
)
	
select n.id , n.regione
from res_regione as r join num_foll as n on n.regione =r.regione
where (cast (n.cnt as float)/ cast(r.num_res as float)*100) >= 75
;
/* Query 10 */


select u1.id, count(distinct c2.regione) as regioni , count( distinct c2.provincia) as provincie
from 
utente as u1 left join segue as s on s.utente = u1.id
left join utente as u2 on s.follower = u2.id
left join comune as c1 on c1.nome = u1.comune
left join comune as c2 on c2.nome = u2.comune
group by u1.id
;

	
	
	
	
	
	
	
				
	
	












