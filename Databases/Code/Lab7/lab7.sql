-- Boaca Lucian
-- Grupa 241

--1
CREATE TABLE timp_zr1
    (
        data1 DATE,
        data2 TIMESTAMP(5),
        data3 TIMESTAMP(5) WITH TIME ZONE
    );

INSERT  INTO timp_zr1
VALUES  (sysdate,systimestamp,systimestamp);

select  * from timp_zr1;

--2
CREATE TABLE salariat_zr1 (
    cod_ang NUMBER(4) NOT NULL,
    nume VARCHAR2(25),
    prenume VARCHAR2(25),
    functia VARCHAR2(20),
    sef NUMBER(4),
    data_angajarii DATE DEFAULT SYSDATE,
    varsta NUMBER(2),
    email CHAR(20),
    salariu NUMBER(9,2) DEFAULT 0 NOT NULL
);

describe    salariat_zr1;

--3
--a
insert  into salariat_zr1
values  (
    1, 'n1', 'p1', 'director', null, 
    to_date('12-02-2017', 'dd-mm-yyyy'),
    30, 'el', 5500
);

--b
insert  into salariat_zr1
(
    cod_ang, nume, functia, sef, varsta, email
)
values
(
    2, 'n2', 'economist', 1, 55, 'e2' 
);

select * from salariat_zr1;

--c
insert  into salariat_zr1
values  (&cod_ang, '&nume', '&prenume', '&functia', &sef, &data_angajarii, &varsta, '&email', &salariu);

--4
create  table economist_zr1
as      
    select  cod_ang, nume, salariu * 12 sal_an, data_angajarii
    from    salariat_zr1
    where   functia='economist';

desc economist_zr1;

--5
alter   table salariat_zr1
add     ( data_nasterii date ); 

--6
describe salariat_zr1;
alter   table salariat_zr1
modify  (
    nume    varchar2(30),
    salariu number(12, 3)
);

--7
alter   table salariat_zr1
modify  (
    email   varchar(20)
);

--8
alter   table salariat_zr1
modify  (
    data_angajarii  date default sysdate + 1
);

--9
alter   table salariat_zr1
rename  column varsta to varsta_ang;

describe salariat_zr1;

--10
alter   table salariat_zr1
drop    column varsta_ang;

--11
select * from timp_zr1;

truncate table timp_zr1;

rollback;
--nu contine date deoarece comanda truncate face auto commit

--12
rename economist_zr1 to eco_zr1;

--13
drop table salariat_zr1;

create table salariat_zr1 (
    cod_ang         number(4)   primary key,
    nume            varchar(25) not null,
    prenume         varchar(25),
    data_nasterii   date,
    functia         varchar(9)  not null,
    sef             number(4)   references salariat_zr1(cod_ang),
    data_angajarii  date        default sysdate,
    email           varchar(20) unique,
    salariu         number(12, 3),
    cod_dept        number(4),
    constraint      ck1_zr1 check(salariu > 0),
    constraint      ck2_zr1 check(data_angajarii > data_nasterii),
    constraint      u_zr1   unique(nume, prenume, data_nasterii)
);

--15
--a
create  table departament_zr1 (
    cod_dep number(4)   primary key,
    nume    varchar(20),
    oras    varchar(25) not null
);

--b
alter   table departament_zr1
modify  nume not null;

--c
alter   table departament_zr1
modify  oras null;

describe departament_zr1;

--16
select * from salariat_zr1;
insert  into salariat_zr1
values  (2, 'n2', 'p2', '11-jun-1960', 'director', null, sysdate, 'e2', 20000, 10);

--17
select * from salariat_zr1;
alter   table salariat_zr1
add     constraint fk2_zr1 foreign key(cod_dept) references departament_zr1(cod_dep);

--18
insert into departament_zr1 values (10, 'Economic', 'Bucuresti');

--19
insert into departament_zr1 values (20, 'Juridic', 'Constanta');
insert into salariat_zr1 values (3, 'n3', 'p3', '11-jun-1967', 'jurist', 2, sysdate, 'e3', 5000, 20);

--20
select * from departament_zr1;
delete from departament_zr1 where cod_dep = 20;

--21
alter table salariat_zr1
drop constraint fk2_zr1;

describe salariat_zr1;
alter table salariat_zr1
rename column cod_dept to cod_dep;

alter table salariat_zr1
add constraint fk2_zr1 foreign key(cod_dep) references
                departament_zr1(cod_dep) on delete cascade;

--22
delete from departament_zr1 where cod_dep = 20;
select * from salariat_zr1;

--23
alter   table salariat_zr1
drop    constraint fk2_zr1;

alter   table salariat_zr1
add     constraint fk2_zr1 foreign key (cod_dep)
        references departament_zr1(cod_dep) on delete set null;

--24
delete  from departament_zr1
where   cod_dep = 10;

select * from salariat_zr1;

--25
--a
create table work_zr1 as 
select * from work where 0 = 1;

create table projects_zr1 as
select * from projects where 0 = 1;

--b
describe work_zr1;
describe emp_zr1;

alter   table emp_zr1
add     constraint emp_zr1_pk primary key(employee_id);

alter   table work_zr1
add     constraint work_emp_fk_zr1 foreign key(employee_id)
        references emp_zr1(employee_id);

alter   table projects_zr1
add     constraint projects_zr1_pk primary key(project_id);

alter   table work_zr1
add     constraint work_proj_fk foreign key(project_id)
        references projects_zr1(project_id);

--c
alter   table work_zr1
add     constraint work_zr1_pk primary key(employee_id, project_id);

--d
alter   table work_zr1
drop    primary key;

--e
alter   table work_zr1
add     constraint work_zr1_pk primary key(employee_id, project_id, start_work);

--28
describe USER_TABLES;
select table_name from USER_TABLES;

--29
desc COLS;

select  column_name 
from    COLS 
where   table_name = upper('dept_zr1'); 

--30
desc USER_CONSTRAINTS;

select  CONSTRAINT_NAME, CONSTRAINT_TYPE, 
        DELETE_RULE, STATUS, VALIDATED,
        INDEX_NAME
from    USER_CONSTRAINTS
where   table_name = upper('departments');

--31
--a
desc USER_CONS_COLUMNS;
--b
select  constraint_name, table_name, column_name
from    USER_CONS_COLUMNS
where   constraint_name = upper('fk2_zr1');
--c
select  ucc.constraint_name, ucc.table_name, column_name
        constraint_type, search_condition, delete_rule, status
from    USER_CONS_COLUMNS ucc, user_constraints uc
where   ucc.constraint_name = uc.constraint_name
and     ucc.constraint_name = upper('fk2_zr1');

-- mini referat : load value si by value






