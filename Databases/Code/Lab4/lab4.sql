--7
select min(hire_date) from employees;

select min(start_date) from job_history;

select hire_date, start_date, end_date, jh.department_id
from employees e, job_history jh
where e.employee_id = jh.employee_id
and e.employee_id = 200;
--daca hire_date ar insemna data job si departament curent

select min(data)
from (
    select min(hire_date) data from employees
    union
    select min(start_date) from job_history
);

select last_name
from employees
where hire_date = (
    select min(hire_date) from employees
);

select last_name
from employees
where hire_date = (
    select min(data)
from (
        select min(hire_date) data from employees
        union
        select min(start_date) from job_history
    )
);

-- cum ne dam seama ca avem rollup:
-- pt fiecare (a, b)
-- pt fiecare a
-- pt toti
select department_id, manager_id, count(employee_id)
from employees
where manager_id is not null and department_id is not null
group by rollup (department_id, manager_id)
order by 1, 2;

select department_id, manager_id, count(employee_id)
from employees
where manager_id is not null and department_id is not null
group by (department_id, manager_id)
union
select department_id, null, count(employee_id)
from employees
where manager_id is not null and department_id is not null
group by (department_id)
union
select null, null, count(employee_id)
from employees
where manager_id is not null and department_id is not null
order by 1, 2;

--
--ROllup, grouping sets, cube, care e mai bun, referat

--Cube (a, b):
--(a, b)
--(a), (b)
--()
--Cube(a, b, c)
--(a, b, c)
--(a, b)
--(a)
--(a, c)
--(b, c)
--(b)
--(c)
--()

select department_id, manager_id, count(employee_id)
from employees
where manager_id is not null and department_id is not null
group by cube (department_id, manager_id)
order by 1, 2;

--28
--Grouping
select department_id, manager_id, count(employee_id),
        decode(grouping(department_id), 1, 'ind de dept', 0) dept,
        decode(grouping(manager_id), 1, 'ind de mgr', 0) mgr
from employees
--where manager_id is not null and department_id is not null
group by cube (department_id, manager_id)
order by 1, 2;

-- Tema: ce face group_id









