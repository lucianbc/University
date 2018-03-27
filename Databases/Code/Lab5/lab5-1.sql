select department_name, sum(salary), round(avg(salary), 2)
from departments d, employees e
where d.department_id = e.department_id
group by department_name
having sum(salary) > (
    select avg(salary)
    from departments
);

SELECT *
FROM (
    SELECT last_name, job_id, salary
    FROM employees
    ORDER BY salary DESC
    )
WHERE ROWNUM <= 5;

select rownum, last_name, salary
from employees
where rownum <= 5
order by salary desc;

select *
from (
    select last_name, job_id, salary
    from employees
    order by salary desc
)
where rownum <= 5;


select rownum, last_name, salary
from employees
where rownum = 1;

select rownum, last_name, salary
from employees
where rownum between 3 and 5;

select last_name, job_id, salary
from employees e
where 5 > (
    select count(*)
    from employees
    where salary > e.salary
) order by salary desc;


--8
SELECT last_name, salary, job_id, department_id
FROM
employees
WHERE (department_id, salary) IN (SELECT department_id, MIN(salary)
FROM
employees
GROUP BY department_id);


SELECT last_name, salary, job_id, department_id
FROM
employees e
WHERE salary = (SELECT MIN(salary)
                FROM employees
                WHERE department_id=e.department_id);

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


--18
select count(*) from employees
union
select count(*) from employees where to_char(hire_date, 'YYYY') = '1997';

select count(*) nr_total, sum(decode(to_char(hire_date, 'YYYY'), 1997, 1, 0)) "nr 1997"
from employees;









