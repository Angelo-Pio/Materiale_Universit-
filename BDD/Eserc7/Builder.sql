
-- ===================================================================
-- Creazione delle tabelle 
-- ===================================================================

  CREATE TABLE musicista(
  codice                NUMERIC(5)    PRIMARY KEY,
  nome                  VARCHAR(20),
  ruolopreferito        VARCHAR(20)
  );
  
  CREATE TABLE band(
  id		NUMERIC(5)      PRIMARY KEY,
  nome        	VARCHAR(20),
  annoinizio	NUMERIC(4) 
  );
  
  CREATE TABLE composizione(
  codice  NUMERIC(5) references musicista,
  id      NUMERIC(5) references band,
  ruolo   VARCHAR(20),
  primary key (codice,id) 
  );

 
-- ====================================================================
-- Inserimento di istanze nelle tabelle
-- =====================================================================

INSERT INTO musicista (codice,nome,ruolopreferito) VALUES (1,'Grigi','bassista');
INSERT INTO musicista (codice,nome,ruolopreferito) VALUES (2,'Rossi','bassista');
INSERT INTO musicista (codice,nome,ruolopreferito) VALUES (3,'Bianchi','chitarrista');
INSERT INTO musicista (codice,nome,ruolopreferito) VALUES (4,'Rosi','tastierista');
INSERT INTO musicista (codice,nome,ruolopreferito) VALUES (5,'Azzurri','batterista');
INSERT INTO musicista (codice,nome,ruolopreferito) VALUES (6,'Neri','chitarrista');
INSERT INTO musicista (codice,nome,ruolopreferito) VALUES (7,'Marroni','tastierista');
INSERT INTO musicista (codice,nome,ruolopreferito) VALUES (8,'Verdi','cantante');
INSERT INTO musicista (codice,nome,ruolopreferito) VALUES (9,'Violi','batterista');
INSERT INTO musicista (codice,nome,ruolopreferito) VALUES (10,'Celesti','cantante');


INSERT INTO band (id,annoinizio,nome) VALUES (100,1965,'RollingStone');
INSERT INTO band (id,annoinizio,nome) VALUES (200,1964,'Beatles');
INSERT INTO band (id,annoinizio,nome) VALUES (300,1969,'The Band');
INSERT INTO band (id,annoinizio,nome) VALUES (400,1975,'Eagles');
INSERT INTO band (id,annoinizio,nome) VALUES (500,2001,'Depeche');
INSERT INTO band (id,annoinizio,nome) VALUES (600,2004,'NewRoll');
INSERT INTO band (id,annoinizio,nome) VALUES (700,2007,'Braves');


INSERT INTO composizione (codice,id,ruolo) VALUES (1,100,'tastierista');
INSERT INTO composizione (codice,id,ruolo) VALUES (1,200,'tastierista');
INSERT INTO composizione (codice,id,ruolo) VALUES (2,100,'batterista');
INSERT INTO composizione (codice,id,ruolo) VALUES (2,200,'chitarrista');
INSERT INTO composizione (codice,id,ruolo) VALUES (3,100,'chitarrista');
INSERT INTO composizione (codice,id,ruolo) VALUES (4,300,'cantante');
INSERT INTO composizione (codice,id,ruolo) VALUES (5,400,'tastierista');
INSERT INTO composizione (codice,id,ruolo) VALUES (6,500,'cantante');
INSERT INTO composizione (codice,id,ruolo) VALUES (6,200,'batterista');
INSERT INTO composizione (codice,id,ruolo) VALUES (6,300,'batterista');
INSERT INTO composizione (codice,id,ruolo) VALUES (7,700,'cantante');
INSERT INTO composizione (codice,id,ruolo) VALUES (9,500,'tastierista');
INSERT INTO composizione (codice,id,ruolo) VALUES (10,500,'chitarrista');



