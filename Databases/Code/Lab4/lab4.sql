--Lucian Boaca
--Grupa 241

--1
select  min(salary) "Minim", max(salary) "Maxim",
        sum(salary) "Suma", round(avg(salary)) "Media"
from    employees;

--2
select  count(*) nr_total_angajati
from    employees;

select  count(*) nr_angajati_cu_manager
from    employees
where   manager_id is not null;

select  count(distinct manager_id) numar_manageri
from    employees;

--3
select  max(salary) - min(salary) "Diferenta"
from    employees;

--4
select  count(*)
from    employees
where   department_id = 50;

--5
select  count(*)
from    employees
where   department_id = 80
and     COMMISSION_PCT is not null;

--6
select  avg(salary), sum(salary)
from    EMPLOYEES
where   JOB_ID in ('SA_MAN', 'SA_REP');

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

--8
select  job_id, count(employee_id) nr_angajati
from    employees
group   by job_id;

--9
select  department_id, min(e.salary) mmin, max(e.salary), 
        sum(e.salary), round(avg(salary))
from    employees e
group   by department_id
order   by mmin; 

select  d.department_name, min(e.salary) mmin, max(e.salary), 
        sum(e.salary), round(avg(salary))
from    employees e, departments d
where   e.department_id = d.department_id(+)
group   by d.department_name
order   by mmin;

--10
select  department_id, job_id, round(avg(salary))
from    employees
group   by department_id, job_id;

--11
--a
select  department_id, min(salary)
from    employees
group   by department_id
having  min(salary) > 5000;

--b
select  d.department_name, min(salary)
from    employees e, departments d
where   e.department_id = d.department_id(+)
group   by d.department_name
having  min(salary) > 5000;

--c
select  d.department_name, min(salary), l.city 
from    employees e, departments d, locations l
where   e.department_id = d.department_id(+)
and     d.location_id = l.location_id(+)
group   by d.department_name, l.city
having  min(salary) > 5000;

--12
select  e.department_id, count(employee_id)
from    employees e
group   by e.department_id
having  count(*) >= 10;

--13
select  count(count(employee_id))
from    employees
group   by department_id
having  count(*) >= 10;

--14
select  department_id, sum(salary)
from    employees
where   commission_pct is not null
group   by department_id
having  count(*) > 5;

--15
select  e.last_name
from    employees e, job_history jh
where   jh.employee_id = e.employee_id
group   by e.last_name
having  count(jh.employee_id) >= 2;

--16
--intrebare aici
select  e.job_id, avg(e.salary), j.MIN_SALARY
from    employees e, jobs j
group   by e.job_id, j.MIN_SALARY
having  avg(e.salary) = j.min_salary;


select  *
from    jobs j, (
        select  job_id, avg(salary) medie
        from    employees
        group   by job_id
) av
where   j.job_id = av.job_id
and     j.min_salary =  av.medie;

select  min_salary from jobs where job_id = 'MK_REP';

--17
select  *
from    (
        select  department_id, avg(salary)
        from    employees
        group   by department_id
        order   by avg(salary)
)
where rownum = 1;

--18
--a
select  d.department_id, department_name, a.suma
from    departments d, (
            select  department_id, sum(salary) suma
            from    employees
            group   by department_id
) a
where   d.department_id = a.department_id;

--b
select  e.department_id, d.department_name, sum(e.salary)
from    employees e, departments d
where   e.department_id = d.department_id
group   by e.department_id, d.department_name
order   by e.department_id;

--19
--a
select  department_name "Departament",
        (
            select  count(employee_id)
            from    employees
            where   department_id = d.department_id
        ) "Nr. angajati",
        (
            select  avg(salary)
            from    employees
            where   department_id = d.department_id
        ) "Salariu mediu"
from    departments d;

--b
select  d.department_name, nr_ang "Nr. angajati", avs "Salariu mediu"
from    departments d,
        (
            select  e.department_id, count(e.EMPLOYEE_ID) nr_ang, avg(e.salary) avs
            from    employees e
            group   by e.department_id
        ) tmp
where   d.department_id = tmp.department_id(+);

--20
select  distinct job_id,
        (
            select  sum(salary)
            from    employees
            where   job_id = e.job_id and department_id = 10
            group   by job_id 
        ) dep10,
        (
            select  sum(salary)
            from    employees
            where   job_id = e.job_id and department_id = 20
        ) dep20,
        (
            select  sum(salary)
            from    employees
            where   job_id = e.job_id and department_id = 30
        ) dep30,
        (
            select  sum(salary)
            from    employees
            where   job_id = e.job_id and department_id in (10, 20, 30)
            group   by job_id
        ) total
from employees e;

--21
select  sum(decode(to_char(hire_date, 'yyyy'), 1997, 1, 0)) "1997",
        sum(decode(to_char(hire_date, 'yyyy'), 1998, 1, 0)) "1998",
        sum(decode(to_char(hire_date, 'yyyy'), 1999, 1, 0)) "1999",
        sum(decode(to_char(hire_date, 'yyyy'), 2000, 1, 0)) "2000",
        count(employee_id) "Total"
from    employees;

select  to_char(hire_date, 'yyyy'), count(employee_id)
from    employees
group   by rollup(to_char(hire_date, 'yyyy'));

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

--22
select  department_id, manager_id, count(employee_id)
from    employees
where   manager_id is not null and department_id is not null
group   by rollup(department_id, manager_id);

--23
select  department_id, manager_id, count(employee_id)
from    employees
where   manager_id is not null and department_id is not null
group   by cube(department_id, manager_id);

--24
select  department_id, job_id, 
        to_char(hire_date, 'yyyy'), count(employee_id)
from    employees
where   department_id is not null and job_id is not null
group   by rollup(department_id, job_id, to_char(hire_date, 'yyyy'));

--25
select  sum(salary), job_id, department_id
from    employees
where   department_id is not null and job_id is not null
group   by cube(job_id, department_id);

--26
select  department_name, job_title, round(avg(e.salary)),
        grouping(department_name), grouping(job_title)
from    employees e, jobs j, departments d
where   e.job_id = j.job_id
and     e.department_id = d.department_id
--and     e.department_id is not null and e.job_id is not null
group   by rollup(department_name, job_title);

--27
select  department_name, job_title, round(avg(salary)),
        decode(grouping(department_name), 0, 'Dept', 'No Dept') by_dept, 
        decode(grouping(job_title), 0, 'Job', 'No job') by_job
from    employees e, jobs j, departments d
where   e.job_id = j.job_id
and     e.department_id = d.department_id
group   by cube(department_name, job_title);

--28
--Grouping
select  department_id, manager_id, count(employee_id),
        decode(grouping(department_id), 1, 'ind de dept', 0) dept,
        decode(grouping(manager_id), 1, 'ind de mgr', 0) mgr
from employees
--where manager_id is not null and department_id is not null
group by cube (department_id, manager_id)
order by 1, 2;

-- Tema: ce face group_id

--29
select  department_name, job_title, e.manager_id, 
        max(salary), sum(salary)
from    employees e, departments d, jobs j
where   e.department_id = d.department_id
and     e.job_id = j.job_id
group   by grouping sets(
        (department_name, job_title),
        (job_title, e.manager_id),
        ()
);








