--/*
drop table imprumuta cascade constraints;
drop table cititor cascade constraints;
drop table domeniu cascade constraints;
drop table carte cascade constraints;
--*/

create table domeniu (
   id_domeniu number(4) primary key,
   denumire varchar2(20));
					  
create table carte (
   id_carte number(4) primary key, 
   titlu varchar2(20), 
   autor varchar2(10), 
   pret number(4) default 10, 
   nrex number(2), 
   cod_domeniu number(4) references domeniu(id_domeniu));
				
create table cititor (
   id_cititor number(4) primary key, 
   nume varchar2(10), 
   data_nasterii date);

create table imprumuta (
   cod_cititor number(4), 
   cod_carte number(4), 
   dataim date,
   dataef date,
   datares date,
   constraint cp_imp primary key (cod_cititor, cod_carte, dataim),
   constraint ce_imp1 foreign key (cod_cititor) references cititor(id_cititor),
   constraint ce_imp2 foreign key (cod_carte) references carte(id_carte));
						
insert into domeniu values (100, 'Informatica');
insert into domeniu values (200, 'Literatura');
insert into domeniu values (300, 'Matematica');
insert into domeniu values (400, 'Biologie'); 

-- carti din domeniul informatica
insert into carte values (101,'CarteInfo1','Autor1',35,1,100);
insert into carte values (102,'CarteInfo2','Autor1',32,4,100);
insert into carte values (103,'CarteInfo3','Autor2',45,8,100);
insert into carte values (104,'CarteInfo4','Autor3',45,3,100);
insert into carte values (105,'CarteInfo5','Autor4',35,1,100);
insert into carte values (106,'CarteInfo6', null,   32,2,100); -- autor necunoscut
--carti din domeniul litaratura
insert into carte values (201,'CarteLit1','Autor5',35,7,200);
insert into carte values (202,'CarteLit2','Autor5',32,3,200);
--carti din domeniul matematica
insert into carte values (301,'CarteMate1','Autor1',30,2,300); -- autor care are carti 2 domenii: mate si info
insert into carte values (302,'CarteMate2','Autor7',30,5,300);
--carti din domeniul biologie
  -- domeniul nu are carti inregistrate
--carti cu domeniul necunoscut
insert into carte values (501,'Carte1','Autor8',90,2,null); 


-- cititori
insert into cititor values (1,'Cititor1',to_date('01-05-1978','dd-mm-yyyy'));
insert into cititor values (2,'Cititor2',to_date('23-05-1982','dd-mm-yyyy'));
insert into cititor values (3,'Cititor3',to_date('21-05-1980','dd-mm-yyyy'));
INSERT INTO cititor VALUES (4,'Cititor4',to_date('10-04-1985','dd-mm-yyyy'));
INSERT INTO cititor VALUES (5,'Cititor5',to_date('11-09-1970','dd-mm-yyyy'));
INSERT INTO cititor VALUES (6,'Cititor6',to_date('23-11-1984','dd-mm-yyyy'));
INSERT INTO cititor VALUES (7,'Cititor7',to_date('20-11-1984','dd-mm-yyyy'));
INSERT INTO cititor VALUES (8,'Cititor8',to_date('01-12-1980','dd-mm-yyyy'));
INSERT INTO cititor VALUES (9,'Cititor9',to_date('30-07-1980','dd-mm-yyyy'));
INSERT INTO cititor VALUES (10,'Cititor10',to_date('14-05-1979','dd-mm-yyyy'));

--imprumuturi
--carti imprumutate din domeniul informatica
--CarteInfo1: 1 exemplar; toate exemplarele imprumutate in prezent
insert into imprumuta values (2, 101,to_date('01-05-2017','dd-mm-yyyy'),to_date('11-05-2017','dd-mm-yyyy'),add_months(to_date('01-05-2017','dd-mm-yyyy'),1));
insert into imprumuta values (10,101,sysdate-60, sysdate-50, add_months(sysdate-60,1));
insert into imprumuta values (1, 101,sysdate, null, add_months(sysdate,1)); 
--CarteInfo2: 4 exemplare; niciun exemplar imprumutat in prezent
insert into imprumuta values (2,102,to_date('02-05-2017','dd-mm-yyyy'),to_date('11-05-2017','dd-mm-yyyy'),add_months(to_date('02-05-2017','dd-mm-yyyy'),1));
--CarteInfo3: 8 exemplare; toate exemplarele imprumutate in prezent
insert into imprumuta values (2,103,to_date('01-05-2017','dd-mm-yyyy'),to_date('11-05-2017','dd-mm-yyyy'),add_months(to_date('01-05-2017','dd-mm-yyyy'),1));
insert into imprumuta values (4,103,to_date('01-05-2017','dd-mm-yyyy'),to_date('04-05-2017','dd-mm-yyyy'),add_months(to_date('01-05-2017','dd-mm-yyyy'),1));
insert into imprumuta values (1,103,sysdate-90, null,add_months(to_date(sysdate-90,'dd-mm-yyyy'),1)); -- termen depasit
insert into imprumuta values (2,103,sysdate-90, null,add_months(to_date(sysdate-90,'dd-mm-yyyy'),1)); -- termen depasit
INSERT INTO imprumuta VALUES (4,103,sysdate-80, null,add_months(to_date(sysdate-80,'dd-mm-yyyy'),1)); -- termen depasit
INSERT INTO imprumuta VALUES (5,103,sysdate-80, null,add_months(to_date(sysdate-80,'dd-mm-yyyy'),1)); -- termen depasit
INSERT INTO imprumuta VALUES (6,103,sysdate-60, null,add_months(to_date(sysdate-60,'dd-mm-yyyy'),1)); -- termen depasit
INSERT INTO imprumuta VALUES (7,103,sysdate-50, null,add_months(to_date(sysdate-50,'dd-mm-yyyy'),1)); -- termen depasit
INSERT INTO imprumuta VALUES (9,103,sysdate-40, null,add_months(to_date(sysdate-40,'dd-mm-yyyy'),1)); -- termen depasit
insert into imprumuta values (10,103,sysdate,   null,add_months(to_date(sysdate,'dd-mm-yyyy'),1)); 
--CarteInfo4: 3 exemplare; niciun exemplar imprumutat in prezent
  -- nu are imprumuturi
--CarteInfo5: 1 exemplar; niciun exemplar imprumutat in prezent
  -- nu are imprumuturi
--CarteInfo6: 2 exemplare; niciun exemplar imprumutat in prezent
  -- nu are imprumuturi

--carti imprumutate din domeniul literatura
--CarteLit1: 7 exemplare; toate exemplarele imprumutate in prezent
INSERT INTO imprumuta VALUES (4,201,to_date('01-02-2018','dd-mm-yyyy'),null,add_months(to_date('01-03-2018','dd-mm-yyyy'),1)); -- termen depasit
INSERT INTO imprumuta VALUES (6,201,to_date('10-02-2018','dd-mm-yyyy'),null,add_months(to_date('10-03-2018','dd-mm-yyyy'),1)); -- termen depasit
INSERT INTO imprumuta VALUES (5,201,to_date('01-02-2018','dd-mm-yyyy'),null,add_months(to_date('01-03-2018','dd-mm-yyyy'),1)); -- termen depasit
INSERT INTO imprumuta VALUES (8,201,to_date('10-02-2018','dd-mm-yyyy'),null,add_months(to_date('10-03-2018','dd-mm-yyyy'),1)); -- termen depasit
insert into imprumuta values (1,201,to_date('28-02-2018','dd-mm-yyyy'),null,add_months(to_date('28-03-2018','dd-mm-yyyy'),1)); -- termen depasit
insert into imprumuta values (2,201,to_date('28-02-2018','dd-mm-yyyy'),null,add_months(to_date('28-03-2018','dd-mm-yyyy'),1)); -- termen depasit
insert into imprumuta values (10,201, sysdate, null, add_months(sysdate,1));
insert into imprumuta values (10,201, sysdate-60, sysdate-50, add_months(sysdate-60,1)); 
--CarteLit2: 3 exemplare; 2 exemplare imprumutate in prezent
insert into imprumuta values (1,202,to_date('09-01-2018','dd-mm-yyyy'),add_months(to_date('09-01-2018','dd-mm-yyyy'),1)+2, add_months(to_date('09-01-2018','dd-mm-yyyy'),1));
INSERT INTO imprumuta VALUES (5,202,to_date('01-02-2018','dd-mm-yyyy'),null,add_months(to_date('01-02-2018','dd-mm-yyyy'),1)); -- termen depasit
INSERT INTO imprumuta VALUES (9,202,to_date('10-02-2018','dd-mm-yyyy'),null,add_months(to_date('10-02-2018','dd-mm-yyyy'),1)); -- termen depasit
commit;

--carti imprumutate din domeniul matematica
--nicio carte imprumutata din acest domeniu

--carti imprumutate din domeniul biologie
--domeniul nu are carti inregistrate 
