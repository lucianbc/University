--Boaca Lucian
--Grupa 241
-- referat: cum folosesc auto increment

--1
create or replace view v_emp_zr1(cod, nume)
as select employee_id, last_name
from emp_0_zr1;

select * from v_emp_zr1;

delete from v_emp_zr1 where cod = 100;
select * from v_emp_zr1;
select * from emp_0_zr1 where employee_id = 100;
rollback;

insert into v_emp_zr1
values(1, '1bs');

--2
create or replace view v_emp_zr1 as
select  employee_id, first_name, last_name, email, hire_date,
        salary, job_id
from    emp_zr1;

select  * from v_emp_zr1;

select  * from emp_zr1;

insert  into v_emp_zr1
values  (400, 'nume', 'prenume', 'email', '18-apr-2017', 3000, 44);

update  v_emp_zr1
set     salary = salary + 1000
where   employee_id = 400;

delete  from v_emp_zr1
where   employee_id = 400;

--3
create view v_emp_dpt_zr1 as
select employee_id, last_name, email, hire_date, job_id,
       e.department_id, department_name
from   emp_zr1 e, dept_zr1 d
where  e.department_id = d.department_id;

insert into v_emp_dpt_zr1
values (500, 'N2', 'E2', sysdate, 'SA_REP', 30, 'Administrativ');

select  *
from    user_updatable_columns
where   table_name = upper('v_emp_dept_zr1');

alter table dept_zr1
add   constraint dept_zr1_pk primary key(department_id);

alter table emp_zr1
add   constraint emp_dept_zr1_fk foreign key(department_id)
      references dept_zr1(department_id);

create or replace view v_emp_dpt_zr1 as
select employee_id, last_name, email, hire_date, job_id,
       e.department_id, department_name
from   emp_zr1 e, dept_zr1 d
where  e.department_id = d.department_id;


--7
create view v_dept_zr1
as select * from dept_zr1
with read only;

--8
create view v_emp_info_zr1 (
    employee_id,
    first_name,
    last_name,
    emain unique disable novalidate,
    phone_number,
    constraint ccp_zr1 primary key (employee_id) disable novalidate
)
as
select employee_id, first_name, last_name, email, phone_number
from   emp_zr1;

--9
create view v_manager_zr1
as select * from employees
where   employee_id in (select distinct manager_id from employees);

alter view v_manager_zr1
add constraint cpp_v_manager primary key (employee_id) disable novalidate;

--10
describe user_views;

select * from user_views;

--11
create materialized view vm_dept_zr1
refresh on commit
as  select  e.department_id, department_name, count(*) nr_angajati,
            sum(salary) val_salarii
    from    emp_zr1 e, dept_zr1 d
    where   e.department_id = d.department_id
    group   by e.department_id, department_name;

select * from vm_dept_zr1;

insert into emp_zr1 (employee_id, last_name, email, hire_date, job_id, salary, department_id)
values (500, 'x', 'x', sysdate, 'x', 1000, 110);

select * from vm_dept_zr1;
select * from emp_zr1;
commit;

--12
create materialized view vm_dept_zr1_2
refresh start with sysdate next sysdate + 1 / 288
as select * from dept_zr1;

--13
create materialized view job_dep_sal_pnu
build immediate
refresh complete
as select d.department_name, j.job_title, sum(salary) suma_salarii
from employees e, departments d, jobs j
where e.department_id = d.department_id
and e.job_id = j.job_id
group by d.department_name, j.job_title;

--15
create sequence sec_zr1
increment by 10
start with 10
maxvalue 10000
nocycle;

select sec_zr1.currval
from dual;

select sec_zr1.nextval
from dual;

--16
create table emp_0_zr1 as select * from employees;
update  emp_0_zr1
set     employee_id = sec_zr1.nextval;

--17
insert into emp_zr1 (employee_id, last_name, email, hire_date, job_id)
values (sec_zr1.nextval, 'x', 'x', sysdate, 'x');

--18
select sec_zr1.currval valoare
from dual;

create sequence sec_dept_zr1
increment by 10
start with 200
maxvalue 20000
nocycle;

select * from user_sequences;
select * from dept_zr1;

update dept_zr1
set     department_id = sec_dept_zr1.nextval;

insert into dept_zr1
values (sec_dept_zr1.nextval, 'x', 207, 1700);

--19
create index emp_last_name_idx_zr1
on emp_zr1(last_name);

--20
create unique index emp_id_idx_zr1
on emp_zr1(employee_id);

create unique index emp_pers_data_idx_zr1
on emp_zr1(last_name, first_name, hire_date);

--21
create index emp_dept_fk_idx_zr1
on emp_zr1(department_id);

--22
create index upper_name_dept_zr1
on dept_zr1(upper(department_name));

drop index upper_name_dept_zr1;

--23
create public synonym se_zr1 for emp_zr1;

--24
create synonym s_v_dpt_zr1 for vm_dept_zr1;

