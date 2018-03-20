--2
select initcap(first_name) "Nume", rpad(to_char(hire_date), 20, ' ') as "Data angajarii"
from employees;

--3
select 'Functia angajatului ' || first_name || ' ' || last_name || ' este ' || job_id 
from employees;

--4
select first_name, last_name, department_id from employees
where upper(trim(last_name)) = 'HIGGINS';

--5
select employee_id, last_name, length(last_name) lungme_nume, instr(upper(last_name), 'A') poz_a from employees
where substr(last_name, -1) = 'n';

--7
select * from employees
where mod(round(sysdate - hire_date), 7) = 0;

--9
select to_char(sysdate + 10, 'MON-DD "T" HH:MI:SS') data from dual;

--10
select floor(add_months(trunc(sysdate, 'y'), 12) - 1 - sysdate) zile_ramase from dual;

--11
select to_char(sysdate +12/24, 'DD-MON-YYYY HH24:MI:SS') peste_12_ore from dual;
select to_char(sysdate +1/288, 'DD-MON-YYYY HH24:MI:SS') peste_5_min from dual;

--13
select last_name, first_name, hire_date, next_day(add_months(hire_date, 6), 'Monday') negociere
from employees;

--14
select last_name, round(Months_between(sysdate, hire_date)) "Luni lucrate"
from employees
order by "Luni lucrate";

--16
select first_name, last_name
from employees
where to_char(hire_date, 'MON') = 'MAY';

--17
select to_char(next_day(add_months(sysdate, 3), 'Friday'), 'DY, MONTH, DD, YYYY') urm_vineri from dual;

--19
select first_name, last_name, nvl(to_char(commission_pct), 'fara comision') "Comision"
from employees;

--20
select first_name, last_name, salary, commission_pct
from employees
where salary + nvl(commission_pct, 0) * salary > 10000;

--22
select last_name, job_id, salary, DECODE
    (job_id,    'IT_PROG', salary*1.1,
                'ST_CLERK', salary*1.15,
                'SA_REP', salary*1.2,
                salary ) "salariu revizuit"
from employees;

select last_name, job_id, salary, 
    case job_id when 'IT_PROG' then salary * 1.1
                when 'ST_CLERK' then salary * 1.15
                when 'SA_REP' then salary * 1.2
                else salary
    end "salariu revizuit"
from employees;

select last_name, job_id, salary, 
    case when job_id = 'IT_PROG' then salary * 1.1
         when job_id = 'ST_CLERK' then salary * 1.15
         when job_id = 'SA_REP' then salary * 1.2
         else salary
    end "salariu revizuit"
from employees;

--23
select first_name, last_name, nvl(department_id, 0) id_departament from employees;
select first_name, last_name, nvl(to_char(department_id), 'fara departament') id_departament from employees;

--24
select avg(commission_pct) comision_mediu
from employees
where commission_pct is not null;

select avg(nvl(commission_pct, 0)) comision_mediu_all
from employees;

--25
select first_name, last_name
from employees
where manager_id is null;

select first_name, last_name, nvl(to_char(manager_id), 'nu are sef')
from employees;

--26
select first_name, last_name, salary + nvl2(commission_pct, commission_pct * salary, 0) venit
from employees;

--27
select nullif(length(first_name), length(last_name)) lg_nume from employees;

--28
select nvl(to_char(nullif(length(first_name), length(last_name))), 'valori egale') lg_nume from employees;

--29
select first_name, last_name, salary, salary + salary *
    case when round(Months_between(sysdate, hire_date)) > 200 then 0.2
         when round(Months_between(sysdate, hire_date)) > 150 then 0.15
         when round(Months_between(sysdate, hire_date)) > 100 then 0.1
         else 0.05
    end "salariu revizuit"
from employees;






