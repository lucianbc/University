--Lucian Boaca
--Grupa 241
--1
create  table test_zr1 as 
select  * from departments;
select  * from test_zr1;
savepoint a;
delete  from test_zr1;
insert  into test_zr1 values (300, 'Economic', 100, 1000);
insert  into test_zr1 values (300, 'Cercetare', 200, 2000);
savepoint b;
insert  into test_zr1 values (400, 'Juridic', 150, 3000);
select  * from test_zr1;
rollback to b;
rollback to a;
commit;
select * from test_zr1;
drop table test_zr1;

--2
create table emp_zr1 as select * from employees;
create table dept_zr1 as select * from departments;

--3
select * from emp_zr1;
select * from dept_zr1;

--4
delete from emp_zr1;
delete from dept_zr1;

--5
describe employees;
describe emp_zr1;

--6
describe dept_zr1;
insert  into dept_zr1 (department_name, location_id)
values  ('dep_zr1_1', 2000);
select * from dept_zr1;

insert  into departments (department_name, location_id)
values  ('dep_zr1_1', 2000);
select * from dept_zr1;

rollback;

--7
select * from emp_zr1;
insert  into emp_zr1
select  *
from    employees
where   commission_pct > 0.25;
rollback;
commit;

--8
create table emp1_zr1 as select * from employees where 0 = 1;
create table emp2_zr1 as select * from employees where 0 = 1;
create table emp3_zr1 as select * from employees where 0 = 1;

insert all
when salary <= 6000 then into emp1_zr1
when salary between 6000 and 10000 then into emp2_zr1
else into emp3_zr1
select * from employees;

select * from emp1_zr1;

rollback;

--9
create table emp0_zr1 as select * from employees where 0 = 1;

insert all
when department_id = 80 then into emp0_zr1
when salary <= 6000 and department_id <> 80 then into emp1_zr1
when salary between 6001 and 10000 and department_id <> 80 then into emp2_zr1
when salary > 10000 and department_id <> 80 then into emp3_zr1
select * from employees;

select * from emp0_zr1;

rollback;
--10
select * from dept_zr1;
accept  dept_id number prompt 'Dept Id'
accept  dept_name char prompt 'Dept name'
accept  mgr_id number prompt 'Manager Id'
accept  loc_id number prompt 'Location Id'

insert  into dept_zr1
values  (&dept_id, &dept_name, &mgr_id, &loc_id);

--11
variable v_nume varchar2(20)

begin
    select  last_name
    into    :v_nume
    from    employees
    where   employee_id = 100;
end;
/
print v_nume

variable dept_id number
begin
    insert  into dept_zr1
    values  (300, 'nume', 20, 20)
    returning department_id into :dept_id;
end;
/
print dept_id

rollback;

--12
delete from emp_zr1;
delete from dept_zr1;

insert into emp_zr1 (select * from employees);
insert into dept_zr1 (select * from departments);

commit;

--13
delete  from dept_zr1
where   department_id not in (
    select  department_id
    from    emp_zr1
    where   department_id is not null
);

rollback;

--14
delete  from emp_zr1
where   employee_id not in (
    select  manager_id
    from    departments
    where   manager_id is not null
    union
    select  employee_id
    from    employees
    where   employee_id not in (
        select  distinct manager_id from employees where manager_id is not null
    )
    minus
    select  employee_id
    from    job_history
);

rollback;

--15
variable v_nume varchar2(20)
begin
    delete from emp_zr1
    where employee_id = &id
    returning last_name into :v_nume;
end;
/
print v_nume

--16
update  emp_zr1
set     salary = 1.05 * salary;

rollback;

--18
-- adaug in history
-- sterg pe 201
update  emp_zr1
set     manager_id = 199
where   manager_id = 201;

delete  from emp_zr1
where   employee_id = 201;

-- adaug in history pe 199 si consideram ca nu este deja acolo
create table job_history_zr1 as select * from job_history;

insert  into job_history_zr1
select  employee_id, hire_date, sysdate - 1, job_id, department_id
from    emp_zr1
where   employee_id = 199;

rollback;

--19
update  emp_zr1
set     (job_id, department_id) = (
            select  job_id, department_id
            from    emp_zr1
            where   employee_id = 205
)
where   employee_id = 114;
rollback;

--20
update  emp_zr1
set     (salary, commission_pct) = (
    select  salary, commission_pct
    from    emp_zr1
    where   manager_id is null
)
where   salary = (
    select  min(salary)
    from    emp_zr1
);

rollback;

--21
update  emp_zr1 e
set     salary = (select round(avg(salary)) from emp_zr1)
where   hire_date = (
    select  min(hire_date)
    from    emp_zr1
    where   department_id = e.department_id
);

rollback;

--22
update  emp_zr1 e
set     email = substr(first_name, 1, 1) || '_' || last_name
where   salary = (
    select  max(salary)
    from    emp_zr1
    where   department_id = e.department_id
);

select  *
from    emp_zr1
order   by department_id, salary desc;

rollback;

--23
variable email_23 varchar2(50)
variable name_23 varchar2(50)

begin
    update  emp_zr1
    set     email = substr(first_name, 1, 1) || '_' || last_name
    where   employee_id = 200
    returning last_name, email into :name_23, :email_23;
end;
/
print email_23
print name_23

rollback;

--24
update  emp_zr1
set     salary = salary + 1000
where   employee_id = &idd;
rollback;

--25
--a
delete  from emp_zr2
where   department_id = 80;

--b
update  emp_zr2
set     salary = salary * 0.95
where   department_id = 50;

merge into emp_zr2 a
using employees b
on (a.employee_id = b.employee_id)
when matched then
update set
a.first_name = b.first_name,
a.last_name = b.last_name,
a.email = b.email,
a.phone_number = b.phone_number,
a.hire_date = b.hire_date,
a.job_id = b.job_id,
a.salary = b.salary,
a.commission_pct = b.commission_pct,
a.manager_id= b.manager_id,
a.department_id= b.department_id
WHEN NOT MATCHED THEN
INSERT VALUES(b.employee_id, b.first_name, b.last_name, b.email,
b.phone_number, b.hire_date, b.job_id, b.salary,
b.commission_pct, b.manager_id, b.department_id);


--23 modificat
variable v_mail varchar2(30)
variable v_nume varchar2(20)
begin
    update emp_zr1
    set email = 'e', last_name = 'n'
    where employee_id = 200
    returning last_name, email
    into :v_nume, :v_mail;
end;
/
print v_mail
print v_nume;

