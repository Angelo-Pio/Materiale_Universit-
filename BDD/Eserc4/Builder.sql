

create table Automobile(
	
	Targa varchar(20) primary key,
	Cilindrata integer,
	Citta varchar(20) not null,
	check(Cilindrata >= 0)

);

insert into Automobile (Targa,Cilindrata,Citta) values('A1',500,'Roma');
insert into Automobile (Targa,Cilindrata,Citta) values('A2',1200,'Roma');
insert into Automobile (Targa,Cilindrata,Citta) values('A3',900,'Milano');
insert into Automobile (Targa,Cilindrata,Citta) values('A4',1000,'Firenze');
insert into Automobile (Targa,Cilindrata,Citta) values('A5',2000,'Palermo');
insert into Automobile (Targa,Cilindrata,Citta) values('A6',3000,'Torino');
insert into Automobile (Targa,Cilindrata,Citta) values('A7',2000,'Torino');
insert into Automobile (Targa,Cilindrata,Citta) values('A8',4000,'Roma');
insert into Automobile (Targa,Cilindrata,Citta) values('A9',4000,'Napoli');


create table Garage(
	Codice varchar(10) primary key ,
	Citta varchar(20) 

);

insert into Garage (Codice,Citta) values('G1','Roma');
insert into Garage (Codice,Citta) values('G2','Firenze');
insert into Garage (Codice,Citta) values('G3','Firenze');
insert into Garage (Codice,Citta) values('G4','Milano');
insert into Garage (Codice,Citta) values('G5','Milano');
insert into Garage (Codice,Citta) values('G6','Palermo');
insert into Garage (Codice,Citta) values('G7','Roma');
insert into Garage (Codice,Citta) values('G8','Palermo');
insert into Garage (Codice,Citta) values('G9','Roma');
insert into Garage (Codice,Citta) values('G10','Milano');
insert into Garage (Codice,Citta) values('G11','Roma');

create table Custodita(

	TargaAuto varchar(20)  references Automobile(Targa),
	CodGarage varchar(10)  references Garage(Codice) not null,
	Numero int ,
	unique(TargaAuto,CodGarage)
);

insert into Custodita (TargaAuto,CodGarage,Numero) values ('A1','G1',2);
insert into Custodita (TargaAuto,CodGarage,Numero) values ('A1','G2',1);
insert into Custodita (TargaAuto,CodGarage,Numero) values ('A3','G5',1);
insert into Custodita (TargaAuto,CodGarage,Numero) values ('A2','G6',15);
insert into Custodita (TargaAuto,CodGarage,Numero) values ('A2','G7',17);
insert into Custodita (TargaAuto,CodGarage,Numero) values ('A5','G6',18);
insert into Custodita (TargaAuto,CodGarage,Numero) values ('A5','G1',2);
insert into Custodita (TargaAuto,CodGarage,Numero) values ('A4','G3',1);
insert into Custodita (TargaAuto,CodGarage,Numero) values ('A6','G1',1);
insert into Custodita (TargaAuto,CodGarage,Numero) values ('A5','G8',1);
insert into Custodita (TargaAuto,CodGarage,Numero) values ('A8','G9',null);
insert into Custodita (TargaAuto,CodGarage,Numero) values ('A8','G2',3);
insert into Custodita (TargaAuto,CodGarage,Numero) values ('A8','G2',3);






