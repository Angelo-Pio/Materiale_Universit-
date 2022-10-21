/* Utilities Queries */

select * 
from Giocatore
full join Giocato
on Giocato.codiceg = Giocatore.codice
full join Squadra
on Squadra.nome = Giocato.nomes ;

select * from Squadra where prestigio < 3;

/* Query 1 */

select distinct Giocatore.codice
from Giocatore
join Giocato on Giocatore.codice = Giocato.codiceg
where 
Giocato.nomes in (
	
	select nome
	from Squadra 
	where prestigio < 3

);

/* Query 2 */

select distinct Giocatore.codice , Giocatore.cognome
from Giocatore
join Giocato as gol on Giocatore.codice = gol.codiceg
where gol.nomes in (
	select nome from Squadra where prestigio >= 4
) and gol > 20;

/* Query 3*/
/* Mai fatto un gol in assoluto? */
select Giocatore.codice , Giocatore.cognome
from Giocatore
join Giocato on Giocatore.codice = Giocato.codiceg
where giocato.gol = 0;

/* Query 4 */


select prest3.nome , count(distinct Giocato.codiceg) 
from Squadra as prest3
join Giocato on prest3.nome = Giocato.nomes
where Giocato.codiceg in 
(
	select distinct codiceg from Giocato
	where gol > 10 and nomes = prest3.nome
) and prest3.prestigio < 3
group by prest3.nome;

/* Query 5 */


select Squadra.nome , avg(Giocato.gol)
from Squadra
join Giocato on Giocato.nomes = Squadra.nome
where Squadra.prestigio >= 4
group by Squadra.nome;

/* Query 6 */

select Giocatore.codice , avg(Giocato.gol)
from Giocatore
join Giocato on Giocato.codiceg = Giocatore.codice
where Giocatore.eta >= 28
group by Giocatore.codice
having avg(Giocato.gol) > 15;

/* Query 7 */

select g1.codice , g1.cognome , gioc.gol 
from Giocatore as g1 
join Giocato as gioc on g1.codice = gioc.codiceg
where gioc.codiceg not in
(
	select codiceg from Giocato where nomes != 'Milan'
);

/* Query 8*/

with maxSquadra as 
(select distinct nomes , max(gol) as gol
	from Giocato 
	group by nomes )
 
select g.nomes, g.codiceg, g.gol
from Giocato as g
join maxSquadra on g.gol = maxSquadra.gol and g.nomes = maxSquadra.nomes
;
/* Query 9 */

with pl as (
	select codiceg, count(distinct nomes) as counter
	from Giocato
	group by codiceg
)

select distinct g1.codiceg, g2.codiceg
from Giocato as g1 
join Giocato as g2 
on g1.nomes = g2.nomes and g1.codiceg != g2.codiceg
join pl as pl1 on g1.codiceg = pl1.codiceg 
join pl as pl2 on g2.codiceg = pl2.codiceg
where g1 < g2 and pl1.counter = pl2.counter















