drop table turista cascade;
drop table viaggio cascade;
drop table visita;

create table Turista(
codFiscale varchar (20) primary key,
cognome varchar(50),
a_nascita integer,
quantiviaggi integer
);

create table Viaggio ( 
	codice integer primary key ,
	anno integer,
	incasso integer
	
);

create table Visita(
 fisc_turista varchar(20) ,
 citta varchar (20) ,
 viaggio integer  ,
costo integer,
	constraint chiave primary key (fisc_turista, citta,viaggio),
check (costo > 0)
);

alter table viaggio add constraint vinc1 foreign key(codice) references Visita(viaggio) on delete cascade;
alter table viaggio add constraint vinc2 foreign key (codice) references Visita(viaggio) on update set default;

	
	insert into  Turista values
	('10', 'Rossi',1980),
	('20', 'Bianchi', 1990),
	('30', 'Verdi',1985),x
	('40', 'Gialli', 1995);

	insert into  viaggio values
	(1,2000),
	(2,2005), 
	(3,2010),
	(4,2012),
	(5,2017),
	(6,2020);

	insert into  Visita values
	('10','Roma',1,500),
	('10','Viterbo',1,200),
	('10','Napoli',2,100),
	('20','Roma',1,300),
	('30','Venezia',2,700),
	('30', 'Roma',3,400),
	('30', 'Torino',3,500),
	('40', 'Roma', 4,600),
	('40', 'Verona', 4,400),
	('40', 'Genova', 5,100),
	('40', 'Livorno',5,200),
	('40', 'Firenze',6,700);






