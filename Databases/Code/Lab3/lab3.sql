--1
--4
select last_name, job_id, department_name
from employees e, departments d, locations s
where e.department_id = d.department_id
and d.location_id = s.location_id
and city = 'Seattle';

--9
select last_name, job_id, department_name, grade_level
from employees e, departments d, job_grades j
where e.department_id = d.department_id (+)
and salary between j.lowest_sal and j.HIGHEST_SAL;

--11
SELECT  a.employee_id "CodAng", a.last_name "NumeAng",
        b.employee_id "CodMgr", b.last_name "NumeMgr"
FROM employees a, employees b
WHERE a.manager_id = b.employee_id (+);

SELECT  a.employee_id "CodAng", a.last_name "NumeAng",
        b.employee_id "CodMgr1", b.last_name "NumeMgr1",
        c.employee_id "CodMgr2", c.last_name "NumeMgr2"
FROM employees a, employees b, employees c
WHERE a.manager_id = b.employee_id (+)
and b.manager_id = c.employee_id (+);

--14
SELECT last_name, hire_date
FROM employees
WHERE hire_date > ( SELECT hire_date
                    FROM employees
                    WHERE last_name = 'Fay');

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