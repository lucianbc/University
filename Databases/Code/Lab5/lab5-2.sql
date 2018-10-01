--Lucian Boaca
--Grupa 241
--1
--v1
select  a.employee_id, a.last_name
from    employees a, employees b
where   a.salary > b.salary
and     b.employee_id = 200;

--v2
select  employee_id, last_name
from    employees e
where   exists (
    select  1
    from    employees
    where   employee_id = 200
    and     e.salary > salary
);

--2
with
sal_200 as (
    select  salary
    from    employees
    where   employee_id = 200
)
select  employee_id, last_name
from    employees
where   salary > (select * from sal_200);

--3
select  department_id, department_name
from    departments d
where   exists (
    select  'x'
    from    employees
    where   department_id = d.department_id
);

--4
with
depts_with_people as (
    select  distinct department_id
    from    employees
    where   department_id is not null
)
select  department_id, department_name
from    departments
where   department_id in (select * from depts_with_people);

--5
select  department_id, department_name
from    departments d
where   not exists (
    select  1
    from    employees
    where   department_id = d.department_id
);

--6
--a
select  location_id, city
from    locations
where   location_id not in (
    select  distinct location_id
    from    departments d
);
--b
select  location_id, city
from    locations
minus
select  l.location_id, city
from    locations l, departments d
where     d.location_id = l.location_id;
--c
select  location_id, city
from    locations l
where   not exists (
    select  1
    from    departments d
    where   d.location_id = l.location_id
);
--d
select  l.location_id, city
from    locations l full outer join departments d
on      l.location_id = d.location_id
where   d.department_id is null;

select  l.location_id, city
from    locations l, departments d
where   l.location_id = d.location_id(+)
and     d.location_id is null;

--7
select  employee_id, first_name, last_name
from    employees e
where   not exists (
    select  project_id
    from    work
    where   employee_id = 202
    minus
    select  project_id
    from    work
    where   employee_id = e.employee_id
);

--8
select  employee_id, first_name, last_name
from    employees e
where   not exists (
    select  project_id
    from    work
    where   employee_id = e.employee_id
    minus
    select  project_id
    from    work
    where   employee_id = 202
);

--9
select  employee_id, first_name, last_name
from    employees e
where   not exists (
    select  project_id
    from    work
    where   employee_id = e.employee_id
    minus
    select  project_id
    from    work
    where   employee_id = 202
)
and     not exists (
    select  project_id
    from    work
    where   employee_id = 202
    minus
    select  project_id
    from    work
    where   employee_id = e.employee_id
);

--10
--v1
select  p.project_id, project_name
from    projects p, work w
where   p.project_id = w.project_id
and     employee_id in (
    select  employee_id
    from    employees
    where   department_id = 20
)
group   by p.project_id, project_name
having  count(*) = (
    select  count(*)
    from    employees
    where   department_id = 20
);

--v2
select  distinct p.project_id, project_name
from    projects p, work w
where   p.project_id = w.project_id
and     not exists (
    select  'x'
    from    employees e
    where   department_id = 20
    and     not exists (
        select  'x'
        from    work w1
        where   e.employee_id = w1.employee_id
        and     w.project_id = w1.project_id
    )
);

--11
with
proiecte_an as (
    select  project_id
    from    projects 
    where   to_char(start_date, 'yyyy') = 1999
)
select  e.employee_id, e.first_name, e.last_name
from    employees e
where   not exists (
    select * from proiecte_an
    minus
    select  project_id
    from    work
    where   employee_id = e.employee_id
);

--12
select  level, employee_id, last_name, manager_id
from    employees
connect by prior manager_id = employee_id;

--13
select  level, employee_id, last_name, manager_id
from    employees
start   with employee_id = 103
connect by prior manager_id = employee_id;

--14
select  level, employee_id, last_name, manager_id
from    employees
start   with employee_id = 103
connect by manager_id = prior employee_id;

--15
with 
id_min_sal as (
    select  *
    from (
        select  employee_id
        from    employees
        order   by salary
    )
    where   rownum = 1
)
select  level, employee_id, last_name, manager_id
from    employees
start   with employee_id = (select * from id_min_sal)
connect by prior manager_id = employee_id;

--16
select  level, employee_id, last_name, salary, manager_id
from    employees
start   with employee_id = 206
connect by prior manager_id = employee_id;

select  level, employee_id, last_name, salary, manager_id
from    employees
where   salary > 15000
start   with employee_id = 206
connect by prior manager_id = employee_id;

select  level, employee_id, last_name, salary, manager_id
from    employees
start   with employee_id = 206
connect by prior manager_id = employee_id 
and     salary > 15000;

--17
--a
--v1
with 
ref_id as (
    select  employee_id
    from    employees
    where   upper(last_name) = upper('de haan')
)
select  employee_id, last_name, hire_date, salary, manager_id
from    employees
where   manager_id = (select * from ref_id);

--v2
select  employee_id, last_name, hire_date, salary, manager_id
from    employees
where   level = 2
start   with upper(last_name) = upper('de haan')
connect by manager_id = prior employee_id;

--b
select  level, employee_id, last_name, hire_date, salary, manager_id
from    employees
where   level = 2
start   with upper(last_name) = upper('de haan')
connect by manager_id = prior employee_id;

--c
select  level, employee_id, last_name, hire_date, salary, manager_id
from    employees
start   with upper(last_name) = upper('de haan')
connect by manager_id = prior employee_id;

--d
--v1
with 
subalterni as (
    select  employee_id
    from    employees
    where   level <> 1
    start   with upper(last_name) = upper('de haan')
    connect by manager_id = prior employee_id
)
select  employee_id, last_name, hire_date, salary, manager_id
from    employees
where   manager_id in (select * from subalterni);

--v2
select  level, employee_id, last_name, hire_date, salary, manager_id
from    employees
where   level > 2
start   with upper(last_name) = upper('de haan')
connect by manager_id = prior employee_id;

--e
select  level, employee_id, last_name, hire_date, salary, manager_id
from    employees
start   with upper(last_name) = upper('hunold')
connect by prior manager_id = employee_id;

--f
select  level, employee_id, last_name, hire_date, salary, manager_id
from    employees
where   level = 2
start   with upper(last_name) = upper('hunold')
connect by prior manager_id = employee_id;

--18
select  count(*)
from    employees
where   level <> 1
start   with employee_id = 107
connect by prior manager_id = employee_id;

--19
with
dept_mgrs as (
    select  manager_id
    from    departments
    where   manager_id is not null
)
select  level, employee_id, last_name, hire_date, salary, manager_id
from    employees
start   with employee_id in (select * from dept_mgrs)
connect by prior manager_id = employee_id;

--20
select  level, employee_id, last_name, manager_id 
from    employees
start   with manager_id is null
connect by manager_id = prior employee_id;

--21
with
dept_mgrs as (
    select  manager_id
    from    departments
    where   manager_id is not null
)
select  level, employee_id, last_name, department_id
from    employees
where   employee_id in (select * from dept_mgrs)
start   with manager_id is null
connect by manager_id = prior employee_id;

--22
select  employee_id, manager_id, level, last_name, 
        lpad(last_name, length(last_name) + level * 2 - 2, '_') nume
from    employees
start   with employee_id = 206
connect by employee_id = prior manager_id;

--23
select  lpad(' ', 3 * level - 3) || last_name nume, level,
        employee_id, manager_id, department_id
from    employees
start   with manager_id is null
connect by prior employee_id = manager_id;

--24
select  lpad(' ', 3 * level - 3) || last_name nume, level,
        employee_id, manager_id, department_id
from    employees
start   with manager_id is null
connect by prior employee_id = manager_id;
--a
select  lpad(' ', 3 * level - 3) || last_name nume, level,
        employee_id, manager_id, department_id
from    employees
where   upper(last_name) <> upper('de haan')
start   with manager_id is null
connect by prior employee_id = manager_id;

--b
select  lpad(' ', 3 * level - 3) || last_name nume, level,
        employee_id, manager_id, department_id
from    employees
start   with manager_id is null
connect by prior employee_id = manager_id
and     upper(last_name) <> upper('de haan');


--25
with
emp_sk as (
    select  employee_id, hire_date
    from    employees
    where   manager_id = (
        select  employee_id
        from    employees
        where   initcap(last_name) = 'King'
        and     initcap(first_name) = 'Steven'
    )
)
select  employee_id, initcap(first_name) || ' ' || upper(last_name)
        job_id, hire_date, manager_id
from    employees
where   to_char(hire_date, 'yyyy') != 1970
start   with employee_id in (
            select  employee_id
            from    emp_sk
            where   hire_date = (
                    select  min(hire_date)
                    from    emp_sk
            )
)
connect by prior employee_id = manager_id;

--26
select  'true'
from    job_grades
having  min(highest_sal) < 10000;






