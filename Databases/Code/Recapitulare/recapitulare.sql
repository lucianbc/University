--Lucian Boaca
--Grupa 241
create table cititor_zr1 as select * from cititor;
create table domeniu_zr1 as select * from domeniu;
create table carte_zr1 as select * from carte;
create table imprumuta_zr1 as select * from imprumuta;

--1
select  titlu 
from    imprumuta_zr1 imp, carte_zr1 c
where   imp.cod_carte = c.id_carte
and     dataim = (
    select  min(dataim)
    from    imprumuta
);

--2
select  titlu, count(cod_carte) imprumuturi
from    imprumuta_zr1 imp, carte_zr1 c
where   imp.cod_carte(+) = c.id_carte
group   by titlu
order   by imprumuturi;

--3
select  denumire, count(*) nr_carti, 
        round(avg(pret)) avg_pret, sum(nrex) nr_exemplare 
from    carte_zr1 c, domeniu_zr1 d
where   c.cod_domeniu = d.id_domeniu
group   by denumire;

--4
select  count(distinct cod_carte)
from    imprumuta;

--5
with 
imprumutate as (
    select distinct cod_carte from imprumuta
)
select  titlu
from    carte
where   id_carte not in ( select * from imprumutate );

select  titlu
from    carte c, imprumuta imp
where   imp.cod_carte(+) = c.id_carte
and     cod_cititor is null;

--6
select  count(*) carti_nerestituite
from    (
    select  titlu
    from    carte c, imprumuta imp
    where   imp.cod_carte(+) = c.id_carte
    and     cod_cititor is null
);

--7
select  c.titlu, count(*)
from    carte c, imprumuta imp
where   imp.cod_carte = c.id_carte
group   by c.titlu
having  count(*) >= 2;

--8
select  count(*) nr_carti_imp
from    (
    select  c.titlu, count(*)
    from    carte c, imprumuta imp
    where   imp.cod_carte = c.id_carte
    group   by c.titlu
    having  count(*) >= 2
);

--9
desc imprumuta;
select  denumire, count(dataim)
from    domeniu d, carte c, imprumuta imp
where   imp.cod_carte(+) = c.id_carte
and     c.cod_domeniu(+) = d.id_domeniu
and     dataef is null
group   by denumire;

select * from imprumuta;

--10
--cel putin o carte
select  cod_cititor
from    imprumuta
where   datares < dataef
or      (dataef is null and sysdate > datares)
group   by cod_cititor
order   by cod_cititor;

--mai mult o carte
select  cod_cititor
from    imprumuta
where   datares < dataef
or      (dataef is null and sysdate > datares)
group   by cod_cititor
having  count(*) > 1
order   by cod_cititor;

--11
select  denumire
from    domeniu d, carte c
where   c.cod_domeniu(+) = d.id_domeniu
group   by denumire
having  count(id_carte) = 0;

--12
select  denumire, nvl(titlu, 'nu are carti')
from    domeniu d, carte c
where   c.cod_domeniu(+) = d.id_domeniu;

--13
select * from carte;
with
rep_price as (
    select  pret
    from    carte
    where   upper(autor) = upper('autor3')
    and     upper(titlu) = upper('carteinfo4')
) 
select  titlu, pret
from    carte
where   pret > (select * from rep_price);

--14

--15
select  distinct nume
from    cititor cit, imprumuta imp, carte car
where   imp.cod_carte = car.id_carte
and     imp.cod_cititor = cit.id_cititor
and     upper(autor) = upper('autor5');

--16
select  nume
from    cititor
minus
select  distinct nume
from    cititor cit, imprumuta imp, carte car
where   imp.cod_carte = car.id_carte
and     imp.cod_cititor = cit.id_cititor
and     upper(autor) = upper('autor5');

--17
--a
select  id_cititor, nume, count(*) 
from    cititor cit, imprumuta imp, carte car, domeniu d
where   imp.cod_carte = car.id_carte
and     car.cod_domeniu = d.id_domeniu
and     cit.id_cititor = imp.cod_cititor
and     d.denumire = 'Informatica'
group   by id_cititor, nume
having  count(*) > 1;

--b
select  id_cititor, nume, count(distinct titlu), count(*) 
from    cititor cit, imprumuta imp, carte car, domeniu d
where   imp.cod_carte = car.id_carte
and     car.cod_domeniu = d.id_domeniu
and     cit.id_cititor = imp.cod_cititor
and     d.denumire = 'Informatica'
group   by id_cititor, nume
having  count(distinct titlu) >= 1
order   by id_cititor;

--c
select  id_cititor, nume, count(distinct titlu), count(*) 
from    cititor cit, imprumuta imp, carte car, domeniu d
where   imp.cod_carte = car.id_carte
and     car.cod_domeniu = d.id_domeniu
and     cit.id_cititor = imp.cod_cititor
and     d.denumire = 'Informatica'
group   by id_cititor, nume
having  count(distinct titlu) = 1;

--18
select  cit.nume, car.titlu
from    cititor cit, imprumuta imp, carte car, domeniu d
where   cit.id_cititor = imp.cod_cititor
and     imp.cod_carte = car.id_carte
and     car.cod_domeniu = d.id_domeniu
and     d.denumire = 'Informatica'
order   by cit.id_cititor;

--19
select  titlu
from    imprumuta imp, carte car
where   imp.cod_carte = car.id_carte
and     dataef is null
group   by titlu, nrex
having  count(cod_carte) = nrex;

--20
select  cod_cititor, cod_carte
from    imprumuta imp
where   dataim = (
    select  max(dataim)
    from    imprumuta
    where   cod_cititor = imp.cod_cititor
);

--21
select  cit.nume
from    cititor cit, imprumuta imp, carte car, domeniu d
where   imp.cod_cititor = cit.id_cititor
and     imp.cod_carte = car.id_carte
and     car.cod_domeniu = d.id_domeniu
and     to_char(cit.data_nasterii, 'dd') = '23'
and     nrex = 1
and     d.denumire = 'Informatica';

--22
with
top_preturi as (
    select  *
    from    (
        select  distinct pret
        from    carte
        order   by pret desc
    )
    where   rownum <= 4
)
select  *
from    carte
where   pret in (select * from top_preturi);

--23
select  id_carte, titlu, pret,
        case when pret > 60 then 'Pret mare'
             when pret > 35 then 'Pret mediu'
             else 'Pret mic'
        end tag
from    carte;

--24
--intreaba aici
--a
select  sum(decode(denumire, 'Informatica', 1, 0)) "Informatica",
        sum(decode(denumire, 'Literatura', 1, 0)) "Literatura",
        sum(decode(denumire, 'Literatura', 1, 'Informatica', 1, 0)) "Info si Literatura",
        count(*) "Total Carti"
from    carte c, domeniu d
where   c.cod_domeniu = d.id_domeniu;

--b


--25
select  denumire, cod_cititor, count(*),
        decode(grouping(denumire), 1, 'Toate Domeniile', 0) grup_domeniu,
        decode(grouping(cod_cititor), 1, 'Toti Citotorii', 0) gup_cititor 
from    imprumuta imp, carte car, domeniu d
where   imp.cod_carte = car.id_carte
and     car.cod_domeniu = d.id_domeniu
group   by rollup(denumire, cod_cititor)
order   by denumire;

--26
select  denumire, cod_cititor, count(*),
        decode(grouping(denumire), 1, 'Toate Domeniile', 0) grup_domeniu,
        decode(grouping(cod_cititor), 1, 'Toti Citotorii', 0) gup_cititor 
from    imprumuta imp, carte car, domeniu d
where   imp.cod_carte = car.id_carte
and     car.cod_domeniu = d.id_domeniu
group   by cube(denumire, cod_cititor)
order   by denumire;

--27
select  denumire, cod_cititor, count(*),
        decode(grouping(denumire), 1, 'Toate Domeniile', 0) grup_domeniu,
        decode(grouping(cod_cititor), 1, 'Toti Citotorii', 0) gup_cititor 
from    imprumuta imp, carte car, domeniu d
where   imp.cod_carte = car.id_carte
and     car.cod_domeniu = d.id_domeniu
group   by grouping sets((denumire, cod_cititor), ())
order   by denumire;

--28
with carti_autor as (
    select  id_carte
    from    carte
    where   autor = 'Autor5'
)
select  * 
from    cititor c
where   not exists(
    select  * from carti_autor
    minus
    select  distinct cod_carte
    from    imprumuta
    where   cod_cititor = c.id_cititor
);

--29
select  *
from    carte c, domeniu d
where   c.cod_domeniu = d.id_domeniu
and     autor is null
and     d.denumire = 'Informatica'
and     not exists (
    select  *
    from    imprumuta
    where   cod_carte = c.id_carte
);

--30
delete  from domeniu_zr1 d
where   not exists(
    select  *
    from    carte
    where   cod_domeniu = d.id_domeniu
);

--31
update  carte_zr1
set     pret = (
    select  max(pret)
    from    carte_zr1
)
where   autor = 'Autor5';
rollback;

--32
--intreaba

--33
select * from domeniu_zr1;
insert into domeniu_zr1 values (500, 'SF');

select * from carte_zr1;
insert into carte_zr1 values (503, 'CarteSf1', 'AutorSf', 99, 3, 500); 

select * from cititor_zr1;
insert into cititor_zr1 values (11, 'CititorSf', '23-OCT-1997');

select * from imprumuta_zr1;
insert into imprumuta_zr1 values(11, 503, sysdate, null, sysdate + 30);

commit;

--34
delete from imprumuta_zr1;
insert into imprumuta_zr1 select * from imprumuta;
rollback;

--35

--37
select  * from carte_zr1;

variable id_carte number
begin
    insert  into carte_zr1
    values  (20, '&titlu', '&autor', &pret, &nrex, &cod_domeniu)
    returning id_carte into :id_carte;
end;
/
print id_carte;

--38
variable titlu_carte varchar2(20)
begin
    delete  from carte_zr1
    where   id_carte = :id_carte
    returning titlu into :titlu_carte;
end;
/
print titlu_carte

--39
variable tt varchar2(20)
begin
    update  carte
    set     pret = pret + 10
    where   id_carte = 101
    returning   titlu into :tt;
end;
/
print tt;

--40
select   * from carte_zr1;
rollback;
update  carte_zr1 c
set     nrex = 2 * nrex
where   (
    select  count(*)
    from    imprumuta_zr1
    where   cod_carte = c.id_carte
) = (
    select  max(count(*))
    from    imprumuta_zr1
    group   by cod_carte
);

--41

--42
--intreaba
--a
select  nume, count(*) * 2 "suma restanta"
from    imprumuta_zr1 imp, cititor_zr1 cit
where   imp.cod_cititor = cit.id_cititor
and     datares < dataef
or      (
    dataef is null 
    and
    datares < sysdate
)
group   by nume;

--b
select  nume, count(*) * 2 "suma restanta"
from    imprumuta_zr1 imp, cititor_zr1 cit
where   imp.cod_cititor = cit.id_cititor
and     dataef is null 
and     datares > sysdate
group   by nume;


--43
with carti_ref as (
    select  cod_carte
    from    imprumuta imp, cititor c
    where   imp.cod_cititor = c.id_cititor
    and     c.nume = 'Cititor4'
) 
select  *
from    cititor c
where   not exists (
    select  * from carti_ref
    minus
    select  cod_carte
    from    imprumuta
    where   cod_cititor = c.id_cititor
);

--44
with carti_ref as (
    select  cod_carte
    from    imprumuta imp, cititor c
    where   imp.cod_cititor = c.id_cititor
    and     c.nume = 'Cititor4'
) 
select  *
from    cititor c
where   not exists (
    select  cod_carte
    from    imprumuta
    where   cod_cititor = c.id_cititor
    minus
    select  * from carti_ref
);

--45
with carti_ref as (
    select  cod_carte
    from    imprumuta imp, cititor c
    where   imp.cod_cititor = c.id_cititor
    and     c.nume = 'Cititor4'
) 
select  *
from    cititor c
where   not exists (
    select  cod_carte
    from    imprumuta
    where   cod_cititor = c.id_cititor
    minus
    select  * from carti_ref
)
and     not exists (
    select  * from carti_ref
    minus
    select  cod_carte
    from    imprumuta
    where   cod_cititor = c.id_cititor    
);


--46
alter   table cititor_zr1
add     constraint cititor_zr1_pk primary key(id_cititor);

describe cititor_zr1;
alter   table cititor_zr1
modify  (
    nume varchar2(20) not null
);

--47
alter   table domeniu_zr1
add     constraint domeniu_zr1_pk primary key(id_domeniu);

alter   table domeniu_zr1
add     constraint domeniu_zr1_uq_den unique(denumire);

--48
alter   table carte_zr1
add     constraint carte_zr1_pk primary key(id_carte);

alter   table carte_zr1
add     constraint carte_zr1_domeniu_fk foreign key(cod_domeniu)
        references domeniu_zr1(id_domeniu);
        
--49
select  * from imprumuta_zr1;
alter   table imprumuta_zr1
add     constraint imprumuta_zr1_pk primary key(cod_cititor, cod_carte, dataim);

describe imprumuta_zr1;
alter   table imprumuta_zr1
modify  (
    dataim date default sysdate not null
);

--intreaba aici 
select  * from imprumuta_zr1 where datares < dataim;
select  * from imprumuta_zr1 where datares >= dataim;

alter   table imprumuta_zr1
add     constraint chk_imp_zr1 check (datares >= dataim);







