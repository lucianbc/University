--Lucian Boaca
--Grupa 241
--1
-- with, varianta 1
with
dept_costuri as (
    select  department_name, sum(salary) dept_cost
    from    employees e, departments d
    where   e.department_id = d.department_id
    group   by department_name
)
select  * 
from    dept_costuri
where   dept_cost > (
    select avg(dept_cost) from dept_costuri
)
order   by dept_cost;

-- with, varianta 2
with
dept_costuri as (
    select  department_name, sum(salary) dept_cost
    from    employees e, departments d
    where   e.department_id = d.department_id
    group   by department_name
),
medie_cost as (
    select  avg(dept_cost) medie
    from    dept_costuri
)
select  *
from    dept_costuri, medie_cost
where   dept_cost > medie
order   by dept_cost;

--2
select  department_name, sum(salary) dept_cost
from    employees e, departments d
where   e.department_id = d.department_id
group   by department_name
having  sum(salary) > (
    select  avg(cst)
    from (
        select  sum(salary) cst
        from    employees
        group   by department_id
    )
)
order   by dept_cost;

--3
select  department_name, sum(salary) dept_cost
from    employees e, departments d
where   e.department_id = d.department_id
group   by department_name
having  sum(salary) > (
    select  avg(cst)
    from (
        select  sum(salary) cst
        from    employees
        where   department_id is not null
        group   by department_id
    )
)
order   by dept_cost;

--4
-- with, varianta 1
with
dept_costuri as (
    select  department_name, sum(salary) dept_cost
    from    employees e, departments d
    where   e.department_id = d.department_id(+)
    group   by department_name
)
select  * 
from    dept_costuri
where   dept_cost > (
    select avg(dept_cost) from dept_costuri
)
order   by dept_cost;

-- with, varianta 2
with
dept_costuri as (
    select  department_name, sum(salary) dept_cost
    from    employees e, departments d
    where   e.department_id = d.department_id(+)
    group   by department_name
),
medie_cost as (
    select  avg(dept_cost) medie
    from    dept_costuri
)
select  *
from    dept_costuri, medie_cost
where   dept_cost > medie
order   by dept_cost;

--5
-- gresita
select rownum, last_name, salary
from employees
where rownum <= 5
order by salary desc;

-- varianta 1
select *
from (
    select last_name, job_id, salary
    from employees
    order by salary desc
)
where rownum <= 5;

-- varianta 2
select last_name, job_id, salary
from employees e
where 5 > (
    select count(*)
    from employees
    where salary > e.salary
) order by salary desc;


select rownum, last_name, salary
from employees
where rownum = 1;

select rownum, last_name, salary
from employees
where rownum between 3 and 5;

--6
select  * 
from (
    select  department_name, count(*) nr_ang
    from    employees e, departments d
    where   e.department_id = d.department_id(+)
    group   by department_name
    order   by nr_ang desc
)
where   rownum <= 5;

--7
select  *
from (
    select  job_title, (min_salary + max_salary) / 2 medie
    from    jobs
    order   by medie asc
)
where   rownum <= 3;

select  *
from (
    select  job_title, avg(salary) medie
    from    employees e, jobs j
    where   e.job_id = j.job_id
    group   by job_title
    order   by medie asc
)
where   rownum <= 3;

--8
--fara sincronizare
select  last_name, salary, job_id, department_id
from    employees
where   (department_id, salary) in (
    select  department_id, min(salary)
    from    employees
    group   by department_id
)
order   by salary;

--cu sincronizare
select  last_name, salary, job_id, department_id
from    employees e
where   salary = (
    select  min(salary)
    from    employees
    where   department_id = e.department_id
)
order   by salary;

--9
--fara sincronizare
select  first_name, last_name, salary
from    employees
where   (job_id, salary) in (
    select  job_id, max(salary)
    from    employees
    group   by job_id
)
order   by salary;

--cu sincronizare
select  first_name, last_name, salary
from    employees e
where   salary = (
    select  max(salary)
    from    employees
    where   job_id = e.job_id
)
order   by salary;

--10

--11
select department_id, department_name 
from departments
where department_id not in (
    select department_id
    from employees
    where department_id is not null
);

select department_id, department_name 
from departments
--where department_id in (10, null);
--where department_id = 10 or department_id = null;
--where department_id not in (10, null);
where department_id <> 10 and department_id <> null;

--12
select  *
from    employees
where   employee_id not in (
    select  manager_id
    from    employees
    where   manager_id is not null
);

--13
select  * 
from    employees
where   salary > all (
    select  salary
    from    employees
    where   job_id like '%CLERK'
);

--14
select  first_name, last_name, salary
from    employees
where   salary > all (
    select  avg(salary)
    from    employees
    group   by department_id
);

select  first_name, last_name, salary
from    employees
where   salary > (
    select  max(slr)
    from    (
        select  avg(salary) slr
        from    employees
        group   by department_id
    )
);

--15
select  first_name, last_name, department_id
from    employees
where   (department_id, hire_date) in (
    select  department_id, min(hire_date)
    from    employees
    group   by department_id
);

--17
select  * from job_grades;

with lowest as (
    select  lowest_sal lowest
    from    job_grades
    where   grade_level = 1
),
highest as (
    select  highest_sal highest
    from    job_grades
    where   grade_level = 1
),
depts as (
    select  department_id
    from    employees
    where   department_id is not null
    and     salary >= (select * from lowest)
    and     salary <= (select * from highest)
    group   by department_id
    having  count(department_id) >= 2)
select  first_name, last_name, department_id
from    employees
where   department_id in (select * from depts);

--18
select count(*) from employees
union
select count(*) from employees where to_char(hire_date, 'YYYY') = '1997';

select count(*) nr_total, sum(decode(to_char(hire_date, 'YYYY'), 1997, 1, 0)) "nr 1997"
from employees;


--19
select  department_id, job_id, round(avg(salary))
from    employees
group   by department_id, job_id
union
select  department_id, null as job_id, round(avg(salary))
from    employees
group   by department_id, job_id
union
select  null as department_id, job_id, round(avg(salary))
from    employees
group   by department_id, job_id
union
select  null as department_id, null as job_id, round(avg(salary))
from    employees
order   by job_id;

--20
select * from job_history;

with
job_data as (
    select  employee_id, hire_date start_date, department_id, job_id
    from    employees
    union
    select  employee_id, start_date, department_id, job_id
    from    job_history
)
select  employee_id, job_title, department_name, start_date
from    job_data jd, departments d, jobs j
where   jd.department_id = d.department_id
and     jd.job_id = j.job_id;

--21
select  employee_id, last_name
from    employees
where   salary < 3000
intersect
select  employee_id, last_name
from    employees
where   department_id = 50;

--22
with 
ppl as (
    select  employee_id, job_id, department_id
    from    employees
    intersect
    select  employee_id, job_id, department_id
    from    job_history
)
select  employee_id, job_title, department_name
from    ppl pp, departments d, jobs j
where   pp.department_id = d.department_id
and     pp.job_id = j.job_id;

--23
with 
ppl as (
    select  employee_id, job_id, department_id
    from    employees
    intersect
    select  employee_id, job_id, department_id
    from    job_history
)
select  first_name, last_name, job_title, department_name
from    ppl pp, departments d, jobs j, employees e
where   pp.department_id = d.department_id
and     pp.job_id = j.job_id
and     pp.employee_id = e.employee_id;

with 
ppl as (
    select  employee_id, first_name, last_name, job_id, department_id
    from    employees
    intersect
    select  e.employee_id, first_name, last_name, jh.job_id, jh.department_id
    from    job_history jh, employees e
    where   e.employee_id = jh.employee_id
)
select  first_name, last_name, job_title, department_name
from    ppl pp, departments d, jobs j
where   pp.department_id = d.department_id
and     pp.job_id = j.job_id;

--24
select  department_id
from    departments
minus
select  distinct department_id
from    employees;

