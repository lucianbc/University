--1
select last_name, e.department_id, department_name
from employees e, departments d
where e.department_id = d.department_id;

--2
select e.last_name, d.department_name
from employees e, departments d
where e.department_id = d.department_id
and e.commission_pct is not null;

--3
select distinct j.JOB_TITLE 
from jobs j, employees e
where e.job_id = j.job_id
and e.DEPARTMENT_ID = 30;

--4
select last_name, job_id, department_name
from employees e, departments d, locations s
where e.department_id = d.department_id
and d.location_id = s.location_id
and city = 'Seattle';

--5
select e.last_name, e.salary, e.hire_date, d.department_name
from employees e, departments d, locations l, countries c, regions r
where e.department_id = d.DEPARTMENT_ID
and d.location_id = l.location_id
and l.COUNTRY_ID = c.COUNTRY_ID
and c.REGION_ID = r.REGION_ID
and r.region_name = 'Americas';

--6
select last_name, department_name
from employees e, departments d
where e.department_id = d.department_id(+);

--7
select d.department_name, e.last_name
from departments d, employees e
where d.department_id = e.department_id(+);

--8
select e.last_name, d.department_name
from employees e, departments d
where e.department_id = d.department_id(+)
union all
select e.last_name, d.department_name
from departments d, employees e
where e.department_id(+) = d.department_id
and e.department_id is null;

--9
select last_name, job_id, department_name, grade_level
from employees e, departments d, job_grades j
where e.department_id = d.department_id (+)
and salary between j.lowest_sal and j.HIGHEST_SAL;

--10
select  a.employee_id "CodAng", a.last_name "NumeAng",
        b.employee_id "CodMgr", b.last_name "NumeMgr"
from    employees a, employees b
where   a.manager_id = b.employee_id;

--11
SELECT  a.employee_id "CodAng", a.last_name "NumeAng",
        b.employee_id "CodMgr", b.last_name "NumeMgr"
FROM    employees a, employees b
WHERE   a.manager_id = b.employee_id (+);

SELECT  a.employee_id "CodAng", a.last_name "NumeAng",
        b.employee_id "CodMgr1", b.last_name "NumeMgr1",
        c.employee_id "CodMgr2", c.last_name "NumeMgr2"
FROM    employees a, employees b, employees c
WHERE   a.manager_id = b.employee_id (+)
and     b.manager_id = c.employee_id (+);

--12
select  a.last_name, a.hire_date,
        b.last_name, b.hire_date
from    employees a, employees b
where   a.hire_date < b.hire_date;

--13
select  t.employee_id, t.last_name nume_tinta, t.department_id,
        c.last_name nume_coleg
from    employees t, employees c
where   c.department_id = t.department_id
and     c.employee_id <> t.employee_id
order by
        t.employee_id;

--14
SELECT last_name, hire_date
FROM employees
WHERE hire_date > ( SELECT hire_date
                    FROM employees
                    WHERE last_name = 'Fay');

--15
select  a.last_name, a.hire_date
from    employees a, employees b
where   upper(b.last_name) = 'FAY'
and     a.hire_date > b.hire_date;

--16
select  last_name, salary
from    employees
where   last_name <> 'Fay'
and     department_id = (
            select  department_id
            from    employees
            where   last_name = 'Fay');

--17
select  last_name, salary
from    employees
where   manager_id = (
            select  employee_id
            from    employees
            where   upper(last_name) = 'KING'
            and     upper(first_name) = 'STEVEN');
            
--18
select  last_name, job_id
from    employees
where   department_id = (
            select  department_id
            from    departments
            where   department_name = 'Sales'
            );

--19
select  e.last_name, e.job_id
from    employees e, departments d
where   e.department_id = d.department_id
and     d.department_name = 'Sales';

--20
SELECT last_name, job_id, department_id
FROM employees
WHERE department_id IN
            (
            SELECT department_id
            FROM departments
            WHERE location_id = (SELECT location_id
            FROM locations
            WHERE city = 'Seattle')
            );

--21
select  e.last_name, e.job_id, e.department_id
from    employees e, departments d, locations l
where   e.department_id = d.department_id
and     d.location_id = l.location_id
and     l.city = 'Seattle';

--22
select  last_name, salary, commission_pct, department_id
from    employees
where   (salary, commission_pct) in (
            select  salary, commission_pct
            from    employees e, departments d
            where   e.department_id = d.department_id
            and     department_name = 'Sales'
)
and     department_id <> (
            select  department_id
            from    departments
            where   department_name = 'Sales'
);

--23
select last_name, salary, job_id
from employees
where salary > (select max(salary)
                from employees
                where job_id like '%CLERK'
                )
order by salary desc;

select  last_name, salary, job_id
from    employees
where   salary >  all(  select  salary
                        from    employees
                        where job_id like '%CLERK'
                    )
order by salary desc;

--24
select  *
from    employees e
where   e.manager_id = (
            select  manager_id
            from    employees
            where   employee_id = 140
);

--25
select  d.department_name
from    departments d, locations l, countries c
where   d.location_id = l.location_id
and     l.country_id = c.country_id
and     c.country_name = 'United States of America';

--26
select  e.last_name nume_angajat, 
        s.last_name nume_sef, 
        ss.last_name nume_sefu_la_sef
from    employees e, employees s, employees ss
where   e.MANAGER_ID = s.employee_id(+)
and     s.manager_id = ss.employee_id(+);

--27
select  e.employee_id, e.salary, e.last_name
from    employees e
where   e.salary > (
            select  avg(salary)
            from    employees
);

--28
select  e.last_name, e.hire_date, j.JOB_TITLE
from    employees e, jobs j
where   e.job_id = j.job_id
and     to_char(e.hire_date, 'MON') = 'JUN';

--29
select  salary + NVL(commission_pct,0) * salary castig_total,
        department_name
from    employees e, departments d
where   e.DEPARTMENT_ID = d.DEPARTMENT_ID
and     salary + NVL(commission_pct,0) * salary > 1200;

--30
select  e.employee_id, j.JOB_TITLE, jh.start_date, jh.end_date
from    job_history jh, employees e, jobs j
where   jh.EMPLOYEE_ID = e.employee_id
and     jh.JOB_ID = j.job_id;

--31
select  e.last_name, j.job_id, jh.start_date, jh.end_date
from    job_history jh, employees e, jobs j
where   jh.EMPLOYEE_ID = e.employee_id
and     jh.JOB_ID = j.job_id;

--32
select  e.last_name, cj.job_title current_job, j.job_id prev_job, jh.start_date, jh.end_date
from    job_history jh, employees e, jobs j, jobs cj
where   jh.EMPLOYEE_ID = e.employee_id
and     cj.job_id = e.JOB_ID
and     jh.JOB_ID = j.job_id;

--33
select  e.last_name, cj.job_title current_job, j.job_id prev_job, jh.start_date, jh.end_date
from    job_history jh, employees e, jobs j, jobs cj
where   jh.EMPLOYEE_ID = e.employee_id
and     cj.job_id = e.JOB_ID
and     jh.JOB_ID = j.job_id
and     e.job_id in (
            select  job_id
            from    job_history
            where   employee_id = e.employee_id
);

--34
select  e.last_name, 
        cj.job_title current_job, cd.department_name current_dep, 
        j.job_id prev_job, d.department_name prev_dep,
        jh.start_date, jh.end_date
from    job_history jh, employees e, jobs j, jobs cj, departments cd, departments d
where   jh.EMPLOYEE_ID = e.employee_id
and     cj.job_id = e.JOB_ID
and     cd.department_id = e.department_id
and     jh.DEPARTMENT_ID = d.department_id
and     jh.JOB_ID = j.job_id
and     e.job_id in (
            select  job_id
            from    job_history
            where   employee_id = e.employee_id
);

--35
select  e.last_name, 
        cj.job_title current_job, cd.department_name current_dep, 
        j.job_id prev_job, d.department_name prev_dep,
        jh.start_date, jh.end_date
from    job_history jh, employees e, jobs j, jobs cj, departments cd, departments d
where   jh.EMPLOYEE_ID = e.employee_id
and     cj.job_id = e.JOB_ID
and     cd.department_id = e.department_id
and     jh.DEPARTMENT_ID = d.department_id
and     jh.JOB_ID = j.job_id
and     e.job_id in (
            select  job_id
            from    job_history
            where   employee_id = e.employee_id
            and     department_id <> e.department_id
);










