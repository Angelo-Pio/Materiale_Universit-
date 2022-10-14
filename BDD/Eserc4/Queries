/* Query 1 */
select Custodita.TargaAuto,Custodita.CodGarage, Garage.Citta
from Custodita join Garage on Custodita.CodGarage = Garage.Codice
where numero = 1
order by Custodita.TargaAuto;

/* Debug Queries */
select * from Garage;
select * from Custodita;
select * from Automobile;

select * from Automobile 
full join Custodita on Automobile.Targa = Custodita.TargaAuto
full join Garage on Custodita.CodGarage = Garage.Codice;

/* Query 2 */
select distinct Garage.Citta, Automobile.Targa
from Automobile,Garage,Custodita
where Automobile.Cilindrata > 100 
and Custodita.Numero > 10
and Custodita.TargaAuto = Automobile.Targa
and Custodita.CodGarage = Garage.Codice;

/* Query 3 */
select Custodita.CodGarage, sum(Custodita.Numero)
from Custodita
where Custodita.Numero >= 1
group by Custodita.CodGarage;


/* Query 4 */
select Custodita.CodGarage, sum(Custodita.Numero)
from Custodita
where Custodita.Numero >= 1 or Custodita.Numero is null
group by Custodita.CodGarage
having sum(Custodita.Numero) > 10 or sum(Custodita.Numero) is null;

/* Query 5 */
select Custodita.TargaAuto,sum(Custodita.Numero) 
from 
Garage join Automobile on Garage.citta = Automobile.citta
join Custodita on Garage.Codice = Custodita.CodGarage and Automobile.Targa = Custodita.TargaAuto
where Custodita.Numero >= 1
group by Custodita.TargaAuto;

/* Query 6 */
select distinct Custodita.CodGarage
from Custodita join Automobile 
on Custodita.TargaAuto = Automobile.Targa
join Garage on Custodita.CodGarage = Garage.Codice


except 

select distinct Custodita.CodGarage
from Custodita join Automobile 
on Custodita.TargaAuto = Automobile.Targa
join Garage on Custodita.CodGarage = Garage.Codice
where Automobile.citta = 'Roma';

/* Query 7 */

select distinct Garage.Codice
from Custodita 
full join  Automobile on Custodita.TargaAuto = Automobile.Targa 
full join  Garage on Custodita.CodGarage = Garage.Codice 
where Automobile.citta = Garage.citta or Automobile.citta is null

except

select distinct Custodita.CodGarage
from Custodita 
join Automobile on Custodita.TargaAuto = Automobile.Targa
join Garage on Custodita.CodGarage = Garage.Codice
group by Custodita.codgarage
having count(Custodita.codgarage) > 1  ;

/* Query 8 */
select distinct Automobile.targa as Targa , Garage.citta as Citta
from Automobile
join Custodita on Custodita.targaauto = Automobile.targa
, Garage

except

select Custodita.targaauto as Targa, Garage.citta as Citta
from Custodita 
join Garage on Custodita.codgarage = Garage.codice
;

/* Query 9 */
select distinct Automobile.targa , count(distinct g1.citta)
from Automobile 
left join Custodita on Automobile.targa = Custodita.targaauto
join Garage as g1 on g1.codice = Custodita.codgarage
group by Automobile.targa
order by Automobile.targa;


/* Query 10 */

select Custodita.targaauto as Targa , count(distinct Custodita.codgarage)
from Custodita
group by Custodita.targaauto
order by Custodita.targaauto





















