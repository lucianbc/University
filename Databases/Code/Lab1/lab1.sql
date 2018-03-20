--8
--lipsesc ghilimelele din alias
select employee_id, last_name, salary * 12 "salariu anual"
from employees;

--10
describe employees;

--11
select * from employees;

--14
describe employees;
select employee_id, first_name || ' ' || last_name as name, job_id, hire_date
from employees;

--17
select job_id from employees;
select distinct job_id from employees;

--18
select first_name || ' ' || last_name nume
from employees;

--19
select first_name, last_name, salary
from employees 
where salary > 10000;

--20
select first_name, last_name, salary
from employees
where salary between 5000 and 10000;

--21
select first_name, salary
from employees
where department_id in (10, 30)
order by first_name asc;

--22
select first_name || ' ' || last_name as Angajat, salary as "Salariu lunar"
from employees
where department_id in (10, 30)
and salary >= 10000;

--23
select sysdate, current_date, systimestamp, current_timestamp, localtimestamp from dual;

--24
select to_char(sysdate, 'YYYY-MM-DD - HH24:MI:SS Q') from dual;

--25
select first_name, last_name, hire_date
from employees
where hire_date like ('%87');

select first_name, last_name, hire_date
from employees
where to_char(hire_date, 'YYYY') = 1987;
--Apostrofurile din dreapta conditiei " = 1987" nu sunt necesare
--SGBD-ul face conversia la string automat cand incearca sa compare un numar cu un string

--26
select last_name, job_id, hire_date
from employees
where hire_date between '10-FEB-1987' and '10-FEB-1990'
order by hire_date;

--27
select last_name, job_id
from employees
where manager_id is NULL;

--28
select last_name, salary, commission_pct
from employees
where commission_pct is not null
order by salary desc, commission_pct asc;

--29
select last_name, salary, commission_pct
from employees
order by commission_pct asc;
--valorile null sunt considerate mai mari decat orice alta valoare si sunt puse la final
--aceasta ordine este definita de utilizator

--30
select distinct last_name
from employees
where last_name like '__a%';

--31
select 'Suntem in ' || to_char(sysdate, '"Anul" YYYY "Luna" fmMONTH "Ziua" DD') data from dual;

--33
describe departments;
select department_name
from departments
where location_id = 1700
and manager_id is not null;

--34
select department_id from employees;

--35
select first_name, last_name from employees
where to_char(hire_date, 'MON-YYYY') = 'JUN-1987';

--36
select employee_id 
from job_history
order by employee_id desc;

--37
select * from employees
where department_id = 70
and to_char(hire_date, 'MON-YYYY') = 'MAR-1997';

--38
select job_title from jobs
where min_salary > 8000;

--39
select * from job_grades
where lowest_sal > 8000;

--40
select first_name || ' ' || last_name as nume from employees
where regexp_like(first_name || ' ' || last_name,  '^(.)*(L|l)(.)*(L|l)(.)*$');

--41
select * from employees
where manager_id = 123;

--42
select first_name, last_name, salary, commission_pct, salary + salary * commission_pct as venit from employees
where commission_pct is not null
and commission_pct <= 0.25;



