-- LAB 1 ========================================================

-- 3
DESC employees;
DESC departments;
DESC jobs;
DESC job_history;
DESC locations;
DESC countries;
DESC regions;

--4
SELECT *
FROM employees;

--5
SELECT employee_id, first_name, job_id
FROM employees;

--6
SELECT employee_id COD, first_name Nume, job_id job
FROM employees;

--7
SELECT DISTINCT job_id
FROM employees;

--8
SELECT first_name || ' ' || last_name "Nume angajat"
FROM employees;

--9
SELECT employee_id || ' ' || first_name || ' ' || last_name || ' ' || email Informatii
FROM employees;

--10
SELECT first_name, salary
FROM employees
WHERE salary >= 2850;

--11
SELECT first_name, department_id
FROM employees
WHERE employee_id = 104;

--12
SELECT first_name, salary
FROM employees
WHERE salary NOT BETWEEN 1500 AND 2850;

--13
SELECT last_name, job_id, hire_date
FROM employees
WHERE hire_date BETWEEN '20-feb-1987' AND '1-may-1989';

--14
SELECT last_name, department_id
FROM employees
WHERE department_id IN (10, 30, 50)
ORDER BY last_name;

--15
SELECT last_name, salary
FROM employees
WHERE department_id IN (10, 30, 50)
      AND salary > 1500;

--16
SELECT TO_CHAR(sysdate, 'DY-MM-YYYY')
FROM DUAL;

--17
SELECT last_name, hire_date
FROM employees
--WHERE TO_CHAR(hire_date, 'YYYY') = 1987;
--WHERE EXTRACT(YEAR FROM hire_date) = 1987;
WHERE hire_date LIKE '%87';

--18
SELECT last_name, first_name, hire_date
FROM employees
WHERE TO_CHAR(hire_date, 'DD') = TO_CHAR(sysdate, 'DD');

--19
SELECT first_name, last_name
FROM employees
WHERE manager_id IS NULL;

--20
SELECT first_name, salary, commission_pct
FROM employees
WHERE commission_pct IS NOT NULL
ORDER BY salary DESC, commission_pct DESC;

--21
SELECT first_name, salary, commission_pct
FROM employees
ORDER BY commission_pct;

--22
SELECT last_name
FROM employees
--WHERE SUBSTR(UPPER(last_name), 3, 1) = 'A';
WHERE UPPER(last_name) LIKE '__A%';

--23
SELECT last_name, manager_id, department_id
FROM employees
WHERE (manager_id = 102 OR department_id = 30)
      AND UPPER(last_name) LIKE '%L%L%';

--24
SELECT last_name, job_id, salary
FROM employees
WHERE (job_id LIKE '%CLERK%' OR job_id LIKE '%REP%')
      AND salary NOT IN (1000, 2000, 3000);
      
--25
SELECT *
FROM departments
WHERE manager_id IS NULL;





-- LAB 2 =====================================================================

--1
SELECT first_name || ' ' || last_name || ' castiga ' || salary || ' dar doreste ' || 3 * salary "Salariu ideal"
FROM employees;

--2
SELECT INITCAP(last_name), UPPER(first_name), LENGTH(last_name)
FROM employees
WHERE last_name LIKE 'J%' OR last_name LIKE 'M%' OR last_name LIKE '__A%'
ORDER BY LENGTH(last_name) DESC;

--3
SELECT employee_id, first_name, department_id
FROM employees
WHERE TRIM(first_name) = 'Steven';

--4
SELECT employee_id, first_name, INSTR(LOWER(first_name), 'a') "Pozitie"
FROM employees
WHERE first_name LIKE '%e';

--5
SELECT *
FROM employees
WHERE MOD(ROUND(sysdate - hire_date), 7) = 0;

--6
SELECT employee_id, last_name, salary, ROUND(salary * 1.15, 2) "Marit", ROUND(salary * 1.15 / 100, 2) "Sute"
FROM employees
WHERE MOD(salary, 1000) != 0;

--7
SELECT last_name, RPAD(hire_date, 20) "Data angajare"
FROM employees
WHERE commission_pct IS NOT NULL;

--8
SELECT TO_CHAR(sysdate + 30, 'MON-DY-YYYY HH-MM-SS')
FROM dual;

--9
SELECT ROUND(TO_DATE(EXTRACT(YEAR FROM sysdate) + 1 || '-01-01', 'YYYY-MM-DD') - sysdate)
FROM dual;

--10
SELECT TO_CHAR(sysdate + 1/2, 'HH-MI-SS')
FROM dual;
SELECT TO_CHAR(sysdate + 1/24/12, 'HH-MI-SS')
FROM dual;

--11
SELECT last_name || ' ' || first_name "Nume", NEXT_DAY(ADD_MONTHS(hire_date, 6), 'Monday')
FROM employees;

--12
SELECT last_name, ROUND((sysdate - hire_date) / 30) "Luni"
FROM employees;

--13
SELECT last_name, hire_date, TO_CHAR(hire_date, 'DAY')
FROM employees;

--14
SELECT last_name, NVL(TO_CHAR(commission_pct), 'Fara comision')
FROM employees;

--15
SELECT last_name, salary, commission_pct
FROM employees
WHERE (1 + NVL(commission_pct, 0)) * salary > 10000;

--16
SELECT last_name, job_id, DECODE(job_id, 'IT_PROG', 1.2,
                                        'SA_REP', 1.25,
                                        'SA_MAN', 1.35, 1) * salary Modificat
FROM employees;

--17
SELECT last_name, department_name
FROM employees e JOIN departments d ON (e.department_id = d.department_id);

--18
SELECT job_title, e.job_id
FROM employees e JOIN jobs j ON (e.job_id = j.job_id)
WHERE e.department_id = 30;

--19
SELECT last_name, department_name, city
FROM employees e JOIN departments d ON (e.department_id = d.department_id)
    JOIN locations l ON (d.location_id = l.location_id);

--20
SELECT last_name, department_name
FROM employees e JOIN departments d ON (e.department_id = d.department_id)
WHERE UPPER(last_name) LIKE '%A%';

--21
SELECT last_name, job_title, department_name
FROM employees e JOIN jobs j ON (e.job_id = j.job_id)
    JOIN departments d ON (e.department_id = d.department_id)
    JOIN locations l ON (d.location_id = l.location_id)
WHERE city = 'Oxford';

--22
SELECT e.last_name, e.employee_id, b.last_name "Boss name", b.employee_id "Boss id"
FROM employees e JOIN employees b ON (e.manager_id = b.employee_id);

--23

SELECT e.last_name, e.employee_id, b.last_name "Boss name", b.employee_id "Boss id"
FROM employees e LEFT JOIN employees b ON (e.manager_id = b.employee_id);
SELECT e.last_name, e.employee_id, b.last_name "Boss name", b.employee_id "Boss id"
FROM employees e JOIN employees b ON (e.manager_id = b.employee_id(+));
SELECT e.last_name, e.employee_id, b.last_name "Boss name", b.employee_id "Boss id"
FROM employees e, employees b
WHERE e.manager_id = b.employee_id(+);

--24
SELECT e.last_name, e.department_id, c.last_name "Coleg"
FROM employees e LEFT JOIN employees c ON (e.department_id = c.department_id)
WHERE e.employee_id != c.employee_id
ORDER BY e.employee_id;

--25
SELECT employee_id, e.job_id, job_title, department_name, salary
FROM employees e JOIN jobs j ON (e.job_id = j.job_id)
    LEFT JOIN departments d ON (e.department_id = d.department_id); 

--26
SELECT DISTINCT e.last_name, e.hire_date
FROM employees e, employees b 
WHERE e.hire_date > b.hire_date AND b.last_name = 'Gates';

--27
SELECT e.last_name "Angajat", e.hire_date "Data_ang", m.last_name "Manager", m.hire_date "Data_mgr"
FROM employees e JOIN employees m ON (e.manager_id = m.employee_id)
WHERE e.hire_date < m.hire_date;




-- LAB 3 ============================================================================

--1
SELECT e.first_name, TO_CHAR(e.hire_date, 'MONTH YYYY')
FROM employees e JOIN employees b ON (e.department_id = b.department_id)
WHERE e.employee_id != b.employee_id
        AND b.last_name = 'Gates'
        AND UPPER(e.last_name) LIKE '%A%';

--2
SELECT DISTINCT e1.employee_id, e1.last_name, e1.department_id, d.department_name
FROM employees e1 JOIN employees e2 ON (e1.department_id = e2.department_id)
        JOIN departments d ON (e1.department_id = d.department_id)
WHERE UPPER(e2.last_name) LIKE '%T%'
ORDER BY e1.last_name;

--3
SELECT e.last_name, e.salary, j.job_title, l.city, c.country_name
FROM employees e JOIN employees boss ON (e.manager_id = boss.employee_id)
    JOIN jobs j ON (e.job_id = j.job_id)
    LEFT JOIN departments d ON (d.department_id = e.department_id)
    LEFT JOIN locations l ON (l.location_id = d.location_id)
    LEFT JOIN countries c ON (l.country_id = c.country_id)
WHERE boss.last_name = 'King';

--4
SELECT d.department_name, e.last_name, j.job_title, TO_CHAR(e.salary, '$99,999.99')
FROM employees e JOIN departments d ON (e.department_id = d.department_id)
    JOIN jobs j ON (e.job_id = j.job_id)
WHERE UPPER(d.department_name) LIKE '%TI%' 
ORDER BY d.department_name, e.last_name;

--5
SELECT e.last_name, d.department_id, d.department_name, l.city, j.job_title
FROM employees e JOIN departments d ON (e.department_id = d.department_id)
    JOIN jobs j ON (e.job_id = j.job_id)
    JOIN locations l ON (d.location_id = l.location_id)
WHERE LOWER(l.city) = 'oxford';

--6
SELECT DISTINCT e.employee_id, e.last_name, e.salary
FROM employees e JOIN employees oth ON (e.department_id = oth.department_id AND e.employee_id != oth.employee_id)
    JOIN jobs j ON (e.job_id = j.job_id)
WHERE e.salary > (j.min_salary + j.max_salary) / 2;

--7
SELECT e.last_name, d.department_name
FROM employees e LEFT JOIN departments d ON (e.department_id = d.department_id);

--8
SELECT e.last_name, d.department_name
FROM employees e RIGHT JOIN departments d ON (e.department_id = d.department_id);

--9
SELECT e.last_name, d.department_name
FROM employees e RIGHT JOIN departments d ON (e.department_id = d.department_id)
UNION
SELECT e.last_name, d.department_name
FROM employees e LEFT JOIN departments d ON (e.department_id = d.department_id);

--10
SELECT DISTINCT d.department_name
FROM employees e JOIN departments d ON (e.department_id = d.department_id)
WHERE e.job_id = 'SA_REP' OR LOWER(d.department_name) LIKE '%re%';

--11
SELECT department_name
FROM departments
MINUS
SELECT department_name
FROM employees e JOIN departments d ON (e.department_id = d.department_id);

SELECT department_name --- RETURNS 16 rows
FROM departments
WHERE department_id NOT IN (SELECT e.department_id
                            FROM employees e JOIN departments q ON (e.department_id = q.department_id));
                            
SELECT department_name --- RETURNS 0 rows
FROM departments
WHERE department_id NOT IN (SELECT department_id
                            FROM employees);
                            
--12
SELECT department_name
FROM departments
WHERE LOWER(department_name) LIKE '%re%'
INTERSECT
SELECT department_name
FROM employees e JOIN departments d ON (e.department_id = d.department_id)
WHERE e.job_id = 'HR_REP';

--13
SELECT employee_id, e.job_id, e.last_name
FROM employees e JOIN jobs j ON (e.job_id = j.job_id)
WHERE e.salary > 3000 OR e.salary = (j.max_salary + j.min_salary) / 2;

--14
SELECT 'Departamentul ' || department_name || ' este condus de ' || NVL(e.last_name, 'nimeni') || ' si ' ||
    CASE WHEN EXISTS (SELECT * FROM employees WHERE department_id = d.department_id) THEN 'are angajati'
        ELSE 'nu are angajati' END Info
FROM departments d LEFT JOIN employees e ON (d.manager_id = e.employee_id);

--15
SELECT first_name, last_name, NULLIF(LENGTH(first_name), LENGTH(last_name))
FROM employees;

--16
SELECT employee_id, last_name, hire_date, salary, DECODE(EXTRACT(YEAR FROM hire_date), 1989, 1.2,
                                                                               1990, 1.15,
                                                                               1991, 1.1, 1) * salary "Salariu Nou"
FROM employees;


-- LAB 4 ====================================================================================
--1
SELECT last_name, hire_date
FROM employees
WHERE hire_date > (SELECT hire_date
                   FROM employees
                   WHERE last_name = 'Gates');
                   
--2
SELECT last_name, salary
FROM employees
WHERE department_id = (SELECT department_id
                       FROM employees
                       WHERE last_name = 'Gates')
     AND last_name <> 'Gates';

--3
SELECT last_name, salary
FROM employees
WHERE manager_id = (SELECT employee_id
                    FROM employees
                    WHERE manager_id IS NULL);
                    
--4
SELECT last_name, department_id, salary
FROM employees
WHERE (department_id, salary) IN (select department_id, salary
                                  FROM employees
                                  WHERE commission_pct IS NOT NULL);

--5
--??

--6
SELECT last_name, salary
FROM employees
WHERE salary > (SELECT MAX(salary)
                FROM employees
                WHERE job_id LIKE '%CLERK%')
ORDER BY salary DESC;

--7
SELECT last_name, department_name, salary
FROM employees e LEFT JOIN departments d ON (e.department_id = d.department_id)
WHERE e.manager_id IN (SELECT employee_id
                       FROM employees
                       WHERE commission_pct IS NOT NULL)
    AND commission_pct IS NULL;
    
--8
SELECT last_name, department_id, salary, job_id
FROM employees
WHERE salary IN (SELECT salary
                 FROM employees e JOIN departments d
                        ON (e.department_id = d.department_id)
                     JOIN locations l
                        ON (l.location_id = d.location_id)
                 WHERE LOWER(l.city) = 'oxford');

--9
SELECT last_name, department_id, job_id
FROM employees
WHERE department_id IN (SELECT d.department_id
                        FROM departments d JOIN locations l
                            ON (d.location_id = l.location_id)
                        WHERE lower(l.city) = 'toronto');
                        
--11
SELECT MIN(salary), MAX(salary), ROUND(AVG(salary), 2)
FROM employees;

--12
SELECT job_id, MIN(salary), MAX(salary), ROUND(AVG(salary), 2)
FROM employees
GROUP BY job_id;

--13
SELECT job_id, COUNT(*)
FROM employees
GROUP BY job_id;

--14
SELECT COUNT(DISTINCT e.employee_id)
FROM employees e JOIN employees b ON (e.employee_id = b.manager_id);
--or
SELECT COUNT(*)
FROM employees
WHERE employee_id IN (SELECT manager_id FROM employees);

--15
SELECT MAX(salary) - MIN(salary) Diferenta, job_id
FROM employees
GROUP BY job_id;

--16
SELECT department_name, street_address, COUNT(*), AVG(salary)
FROM employees e LEFT JOIN departments d ON (e.department_id = d.department_id)
    LEFT JOIN locations l ON (d.location_id = l.location_id)
GROUP BY department_name, street_address;

--17
SELECT employee_id, last_name, salary
FROM employees
WHERE salary > (SELECT AVG(salary) FROM employees)
ORDER BY salary desc;

--18
SELECT manager_id, MIN(salary)
FROM employees
GROUP BY manager_id
HAVING manager_id IS NOT NULL
      AND MIN(salary) > 1000
ORDER BY MIN(salary) DESC;

--19
SELECT d.department_id, d.department_name, MAX(salary)
FROM employees e JOIN departments d ON (e.department_id (+) = d.department_id)
GROUP BY d.department_id, d.department_name
HAVING MAX(salary) > 3000;

--20
SELECT job_id, MIN(salary), AVG(salary)
FROM employees
GROUP BY job_id;

--21
SELECT d.department_id, d.department_name, SUM(salary)
FROM employees e JOIN departments d ON (e.department_id (+) = d.department_id)
GROUP BY d.department_id, d.department_name;

--22
SELECT MAX(AVG(salary))
FROM employees e
GROUP BY job_id;


--23
SELECT j.job_id, j.job_title, AVG(salary)
FROM jobs j JOIN employees e ON (j.job_id = e.job_id)
GROUP BY j.job_id, j.job_title
HAVING AVG(salary) = (SELECT MAX(AVG(salary))
                      FROM employees
                      GROUP BY job_id);

--24
SELECT AVG(salary)
FROM employees
HAVING AVG(salary) > 2500;


-- LAB 5 ==========================================================
--1
SELECT department_id, job_id, SUM(salary)
FROM employees
GROUP BY department_id, job_id;

--2
SELECT e.department_id, d.department_name, j.job_id, j.job_title, SUM(salary)
FROM employees e LEFT JOIN departments d ON (e.department_id = d.department_id)
    LEFT JOIN jobs j ON (e.job_id = j.job_id)
GROUP BY e.department_id, department_name, j.job_id, j.job_title;

--3
SELECT d.department_name, MIN(salary), AVG(salary)
FROM employees e LEFT JOIN departments d ON (e.department_id = d.department_id)
GROUP BY d.department_name
HAVING AVG(salary) = (SELECT MAX(AVG(salary))
                      FROM employees
                      GROUP BY department_id);

--4
SELECT d.department_id, d.department_name, COUNT(*)
FROM employees e JOIN departments d ON (e.department_id = d.department_id)
GROUP BY d.department_id, d.department_name
HAVING COUNT(*) <= 4;
SELECT d.department_id, d.department_name, COUNT(*)
FROM employees e JOIN departments d ON (e.department_id = d.department_id)
GROUP BY d.department_id, d.department_name
HAVING COUNT(*) = (SELECT MAX(COUNT(*))
                   FROM employees
                   GROUP BY department_id);
    
--5
SELECT last_name, hire_date
FROM employees
WHERE EXTRACT(DAY FROM hire_date) =
    (SELECT EXTRACT(DAY FROM hire_date)
    FROM employees
    GROUP BY EXTRACT(DAY FROM hire_date)
    HAVING COUNT(*) = (SELECT MAX(COUNT(*))
                      FROM employees
                      GROUP BY EXTRACT(DAY FROM hire_date)));

--6
SELECT COUNT(*)
FROM (SELECT 1
      FROM employees
      GROUP BY department_id
      HAVING COUNT(*) >= 15);
--7
SELECT department_id, SUM(salary)
FROM employees
GROUP BY department_id
HAVING COUNT (*) >= 10 AND department_id <> 30
ORDER BY SUM(SALARY);

--8
SELECT d.department_id, d.department_name, d.average, d.nr, e.last_name, e.salary
FROM (SELECT d.department_id department_id, d.department_name department_name,
            AVG(e.salary) average, COUNT(*) nr
      FROM departments d JOIN employees e ON (d.department_id (+) = e.department_id)
      GROUP BY d.department_id, d.department_name) d
   LEFT JOIN employees e ON (d.department_id = e.department_id);

--9
SELECT j.job_title Titlu, l.city Oras, d.department_name Departament, SUM(salary) "Suma Salarii"
FROM employees e LEFT JOIN departments d ON (e.department_id = d.department_id)
        LEFT JOIN locations l ON (d.location_id = l.location_id)
        LEFT JOIN jobs j ON (e.job_id = j.job_id)
WHERE d.department_id > 80
GROUP BY j.job_title, l.city, d.department_name;

--10
SELECT last_name, employee_id
FROM employees e
WHERE (SELECT COUNT(*)
       FROM job_history
       WHERE employee_id = e.employee_id) >= 2;
SELECT last_name, employee_id
FROM employees e JOIN job_history j USING (employee_id)
GROUP BY last_name, employee_id
HAVING COUNT(*) >= 2;

--11
SELECT AVG(commission_pct)
FROM employees; --- BUSIT
SELECT AVG(NVL(commission_pct, 0))
FROM employees;

--12
SELECT job_title,
    SUM(CASE department_id WHEN 30 THEN salary ELSE 0 END) Dep30,
    SUM(CASE department_id WHEN 50 THEN salary ELSE 0 END) Dep50,
    SUM(CASE department_id WHEN 80 THEN salary ELSE 0 END) Dep80,
    SUM(salary) Total
FROM employees e JOIN jobs j USING (job_id)
GROUP BY job_title;

--13
SELECT COUNT(*),
    COUNT(DECODE(EXTRACT(YEAR FROM hire_date), 1997, 1)) Y1997,
    COUNT(DECODE(EXTRACT(YEAR FROM hire_date), 1998, 1)) Y1998,
    COUNT(DECODE(EXTRACT(YEAR FROM hire_date), 1999, 1)) Y1999,
    COUNT(DECODE(EXTRACT(YEAR FROM hire_date), 2000, 1)) Y2000
FROM employees;

--14
SELECT department_id, department_name, salary
FROM departments JOIN (SELECT department_id, SUM(salary) salary
                       FROM employees
                       GROUP BY department_id) USING (department_id);
                       
--15
SELECT job_title, (max_salary - min_salary) / 2 expected, average
FROM jobs JOIN (SELECT job_id, AVG(salary) average
                FROM employees
                GROUP BY job_id) USING (job_id);
                
--16
SELECT job_title, (max_salary - min_salary) / 2 expected, average, nr
FROM jobs JOIN (SELECT job_id, AVG(salary) average, COUNT(*) nr
                FROM employees
                GROUP BY job_id) USING (job_id);

--17
SELECT job_title, last_name, salary
FROM jobs j JOIN employees e ON (j.job_id = e.job_id) ---- DC NU MERGE CU USING
WHERE salary = (SELECT MIN(salary)
                FROM employees
                WHERE e.job_id = job_id);


-- LAB 6 ================================================================

--1
SELECT employee_id, salary
FROM employees e
WHERE salary > (SELECT AVG(salary)
                FROM employees
                WHERE department_id = e.department_id);
SELECT employee_id, salary
FROM employees e JOIN (SELECT department_id, AVG(salary) avg
                       FROM employees
                       GROUP BY department_id) d ON (e.department_id = d.department_id)
WHERE e.salary > d.avg;

--2
SELECT last_name, salary
FROM employees
WHERE salary > all (SELECT AVG(salary)
                    FROM employees
                    GROUP BY department_id);
SELECT last_name, salary
FROM employees
WHERE salary >  (SELECT MAX(AVG(salary))
                 FROM employees
                 GROUP BY department_id);
  
--3
--a
SELECT first_name, salary
FROM employees e
WHERE salary = (SELECT MIN(salary)
                FROM employees
                WHERE department_id = e.department_id);
--b
SELECT first_name, salary
FROM employees
WHERE (department_id, salary) IN (SELECT department_id, MIN(salary)
                 FROM employees
                 GROUP BY department_id);

--4
SELECT d.department_name, e.last_name, e.hire_date
FROM employees e JOIN departments d ON (e.department_id = d.department_id)
WHERE e.hire_date = (SELECT MIN(hire_date)
                     FROM employees
                     WHERE department_id = d.department_id)
ORDER BY d.department_id;

--5
SELECT last_name, salary
FROM employees e
WHERE EXISTS (SELECT *
              FROM employees
              WHERE department_id = e.department_id
                AND salary = (SELECT MAX(salary)
                              FROM employees
                              WHERE department_id = 30));
                              
--6
SELECT last_name, salary
FROM (SELECT last_name, salary
    FROM employees
    ORDER BY salary DESC)
WHERE rownum <= 3;

--7
SELECT last_name, employee_id, salary
FROM employees e
WHERE (SELECT COUNT(*)
       FROM employees
       WHERE manager_id = e.employee_id) >= 2;
       
--8
SELECT l.location_id
FROM locations l
WHERE EXISTS (SELECT *
              FROM departments
              WHERE location_id = l.location_id);
              
--9
SELECT department_name
FROM departments d
WHERE NOT EXISTS (SELECT *
                  FROM employees
                  WHERE department_id = d.department_id);
                  
--10
WITH val_dep AS (SELECT department_name, SUM(salary) total
                 FROM employees e JOIN departments d ON (e.department_id = d.department_id)
                 GROUP BY department_name),
    val_medie AS (SELECT AVG(SUM(salary)) medie
                  FROM employees
                  GROUP BY department_id)
SELECT *
FROM val_dep
WHERE total > (SELECT medie
               FROM val_medie);
                    
--11
WITH vechime AS (SELECT MAX(hire_date) hire_date
                 FROM employees e
                 WHERE (SELECT last_name
                        FROM employees
                        WHERE employee_id = e.manager_id) = 'King')
SELECT employee_id, first_name || ' ' || last_name, job_id, hire_date
FROM employees e
WHERE hire_date = (SELECT hire_date FROM vechime);

--12
SELECT employee_id, first_name, salary
FROM (SELECT employee_id, first_name, salary
      FROM employees
      ORDER BY salary DESC)
WHERE rownum <= 10;

--13
SELECT job_title, avg_sal
FROM (SELECT job_title, (SELECT AVG(salary)
                         FROM employees
                         WHERE job_id = j.job_id) avg_sal
      FROM jobs j
      ORDER BY (SELECT AVG(salary)
                 FROM employees
                 WHERE job_id = j.job_id) DESC)
WHERE rownum <= 3;

--14
SELECT job_id, SUM(salary)
FROM employees e
GROUP BY job_id
HAVING LOWER(job_id) LIKE 's%';

SELECT AVG(salary)
FROM employees e
WHERE EXISTS (SELECT *
              FROM employees b
              WHERE e.job_id = b.job_id
                AND salary = (SELECT MAX(salary) FROM employees));
                
SELECT job_title, (SELECT MIN(salary) FROM employees WHERE job_id = j.job_id)
FROM jobs j
WHERE NOT EXISTS (SELECT *
              FROM employees b
              WHERE j.job_id = b.job_id
                AND salary = (SELECT MAX(salary) FROM employees));
                
-- LAB 7 ====================================================================

--1
SELECT employee_id, last_name
FROM employees e
WHERE NOT EXISTS (SELECT *
                  FROM project p
                  WHERE EXTRACT(MONTH FROM start_date) <= 6
                    AND NOT EXISTS (SELECT *
                                    FROM works_on
                                    WHERE project_id = p.project_id
                                        AND employee_id = e.employee_id));
                                        
--2
SELECT project_id
FROM project p
WHERE NOT EXISTS
    (SELECT *
     FROM employees e
     WHERE (SELECT COUNT(*)
            FROM job_history
            WHERE employee_id = e.employee_id) = 2
        AND NOT EXISTS (SELECT *
                        FROM works_on
                        WHERE employee_id = e.employee_id
                            AND project_id = p.project_id));

--3
SELECT employee_id, COUNT(job_id)
FROM (SELECT employee_id, job_id
      FROM employees
      UNION
      SELECT employee_id, job_id
      FROM job_history)
GROUP BY employee_id
HAVING COUNT(job_id) >= 3;

--4
SELECT country_name, COUNT(employee_id)
FROM employees e LEFT JOIN departments d ON (e.department_id = d.department_id)
    LEFT JOIN locations l ON (d.location_id = l.location_id)
    LEFT JOIN countries c ON (l.country_id = c.country_id)
GROUP BY country_name;

--5
SELECT employee_id, last_name
FROM employees e
WHERE (SELECT COUNT(*)
       FROM project p
       WHERE EXISTS (SELECT *
                     FROM works_on
                     WHERE employee_id = e.employee_id
                        AND project_id = p.project_id)
            AND delivery_date > deadline) >= 2;
            
--6
SELECT e.employee_id, project_id
FROM employees e LEFT JOIN works_on w ON (e.employee_id = w.employee_id);

--7
SELECT employee_id, last_name
FROM employees e
WHERE EXISTS (SELECT *
              FROM employees m
              WHERE m.department_id = e.department_id
                AND EXISTS (SELECT *
                            FROM project
                            WHERE project_manager = m.employee_id));

--8
SELECT employee_id, last_name
FROM employees e
WHERE NOT EXISTS (SELECT *
              FROM employees m
              WHERE m.department_id = e.department_id
                AND EXISTS (SELECT *
                            FROM project
                            WHERE project_manager = m.employee_id));

--9
SELECT department_id
FROM employees
GROUP BY department_id
HAVING AVG(salary) > &average;

--10
SELECT employee_id, last_name, first_name, salary, (SELECT COUNT(*)
                                                    FROM project
                                                    WHERE project_manager = e.employee_id) Nr
FROM employees e
WHERE (SELECT COUNT(*)
        FROM project
        WHERE project_manager = e.employee_id) > 1;
        
--11
SELECT employee_id, last_name
FROM employees e
WHERE NOT EXISTS (SELECT *
                  FROM works_on w
                  WHERE employee_id = e.employee_id
                    AND EXISTS (SELECT *
                                FROM project
                                WHERE project_id = w.project_id
                                    AND project_manager = 102));
                                    
--12
SELECT employee_id
FROM employees e
WHERE NOT EXISTS (SELECT *
                  FROM project p
                  WHERE EXISTS (SELECT *
                                FROM works_on
                                WHERE project_id = p.project_id
                                    AND employee_id = 200)
                    AND NOT EXISTS (SELECT *
                                    FROM works_on
                                    WHERE project_id = p.project_id
                                    AND employee_id = e.employee_id));
                                    
SELECT employee_id
FROM employees e
WHERE NOT EXISTS (SELECT *
                  FROM project p
                  WHERE NOT EXISTS (SELECT *
                                    FROM works_on
                                    WHERE project_id = p.project_id
                                        AND employee_id = 200)
                    AND EXISTS (SELECT *
                                FROM works_on
                                WHERE project_id = p.project_id
                                    AND employee_id = e.employee_id));
                                        

--13
SELECT employee_id
FROM employees e
WHERE NOT EXISTS (SELECT *
                  FROM project p
                  WHERE EXISTS (SELECT *
                                FROM works_on
                                WHERE project_id = p.project_id
                                    AND employee_id = 200)
                    AND NOT EXISTS (SELECT *
                                    FROM works_on
                                    WHERE project_id = p.project_id
                                    AND employee_id = e.employee_id))
    AND NOT EXISTS (SELECT *
                  FROM project p
                  WHERE NOT EXISTS (SELECT *
                                    FROM works_on
                                    WHERE project_id = p.project_id
                                        AND employee_id = 200)
                    AND EXISTS (SELECT *
                                FROM works_on
                                WHERE project_id = p.project_id
                                    AND employee_id = e.employee_id));
     
--14
DESC job_grades;
--SELECT * FROM job_grades; WTF??? AAh ok :)) still shady tho

SELECT employee_id, salary, (SELECT grade_level
                             FROM job_grades
                             WHERE e.salary BETWEEN lowest_sal AND highest_sal) "Grade level"
FROM employees e;

--15

--16
SHOW LINESIZE;
SHOW PAGESIZE;
SET LINESIZE 100;
SET PAGESIZE 24;

--17
SELECT employee_id, last_name, salary, department_id
FROM employees
WHERE employee_id = &p_cod;

ACCEPT p_cod PROMPT 'Hei';
SELECT employee_id, last_name, salary, department_id
FROM employees
WHERE employee_id = &&p_cod;
UNDEFINE p_cod;

--18
SELECT last_name department_id, salary * 12 Salariu
FROM employees
WHERE job_id = '&job';

--19
SELECT last_name, department_id, 12 * salary "Salavriu anual"
FROM employees
WHERE hire_date > '&date';

--20
SELECT &coloana
FROM &tabel
WHERE &conditie;

--21
UNDEFINE inceput;
ACCEPT inceput PROMPT 'Inceput:';
UNDEFINE sfarsit;
ACCEPT sfarsit PROMPT 'Sfarsit:';
SELECT last_name, job_id
FROM employees
WHERE hire_date between '&&inceput' AND '&&sfarsit';

--22
SELECT last_name, job_id, salary
FROM employees e JOIN departments d ON (e.department_id = d.department_id)
    JOIN locations l ON (d.location_id = l.location_id)
WHERE UPPER(city) = UPPER('&location');

;
DESC project;
DESC works_on;
SELECT * FROM countries;
SELECT * FROM locations;
SELECT * FROM jobs;
SELECT * FROM departments;
SELECT * FROM EMPLOYEES;
SELECT * FROM job_history;
-- EMPLOYEES, DEPARTMENTS,
-- JOBS, JOB_HISTORY, LOCATIONS, COUNTRIES, REGIONS





















