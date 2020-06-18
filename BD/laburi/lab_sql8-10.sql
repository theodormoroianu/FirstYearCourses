-- LAB 8 ===========================================================================

--1
DROP TABLE emp_tmo;
DROP TABLE dept_tmo;
CREATE TABLE emp_tmo AS (SELECT *
                         FROM employees);
CREATE TABLE dept_tmo AS (SELECT *
                          FROM departments);

--2
DESC emp_tmo;
DESC employees;

--3
SELECT *
FROM emp_tmo;

--4
ALTER TABLE emp_tmo
ADD CONSTRAINT prim_key_emp PRIMARY KEY(employee_id);

ALTER TABLE dept_tmo
ADD CONSTRAINT prim_key_dept PRIMARY KEY(department_id);

ALTER TABLE emp_tmo
ADD CONSTRAINT fk_emp
FOREIGN KEY (department_id) REFERENCES dept_tmo(department_id);

--5
INSERT INTO dept_tmo
VALUES (300, 'Programare');
--- Nu sunt date suficiente valori

INSERT INTO dept_tmo (department_id, department_name)
VALUES (300, 'Programare');
--- corect
ROLLBACK;

--6
DESC emp_tmo;
INSERT INTO emp_tmo (employee_id, last_name, email, hire_date, job_id)
VALUES (1000, 'Popescu', 'pop@gmail.com', '10-JAN-2000', 'SA');

--7
INSERT INTO emp_tmo (employee_id, last_name, email, hire_date, job_id)
VALUES (1001, 'Popescu', 'pop@gmail.com', sysdate, 'SA');

--8
INSERT INTO emp_tmo (employee_id, last_name, email, hire_date, job_id)
VALUES ((SELECT MAX(employee_id) + 1 FROM emp_tmo),
        'Marcel', 'm@m', sysdate, 'SA');
        
--9

WITH val AS (SELECT employee_id, last_name, email, hire_date, job_id
             FROM emp_tmo)
INSERT INTO val
VALUES ((SELECT MAX(employee_id) + 1 FROM emp_tmo),
        'Marcel', 'm@m', sysdate, 'SA');

--10
DROP TABLE emp1_tmo;
CREATE TABLE emp1_tmo AS SELECT * FROM employees
WHERE 1 = 0;

SELECT * FROM emp1_tmo;

INSERT INTO emp1_tmo (SELECT *
                      FROM employees
                      WHERE commission_pct IS NULL);

SAVEPOINT s;
ROLLBACK;

--11
DESC emp_tmo;
INSERT INTO emp_tmo (employee_id, last_name, email, hire_date, job_id, salary, commission_pct)
VALUES ((SELECT MAX(employee_id) + 1 FROM emp_tmo),
        'TOTAL',
        'total@total.com',
        sysdate,
        '0',
        (SELECT SUM(salary) FROM employees),
        (SELECT AVG(NVL(commission_pct, 0)) FROM employees));
        
--12

DESC emp_tmo;
ACCEPT emp_code PROMPT 'Cod user:';
ACCEPT emp_nume PROMPT 'Nume:';
ACCEPT emp_prenume PROMPT 'Prenume:';
ACCEPT emp_salary PROMPT 'Salariu:';
INSERT INTO emp_tmo (employee_id, first_name, last_name, email, salary, hire_date, job_id)
VALUES (&&emp_code,
        '&&emp_prenume',
        '&&emp_nume',
        SUBSTR('&&emp_nume', 1) || SUBSTR('&&emp_prenume', 7) || '@c.com',
        &&emp_salary,
        sysdate,
        '123');
UNDEFINE emp_code, emp_nume, emp_prenume, emp_salary;

--13

CREATE TABLE emp2_tmo AS SELECT * FROM employees WHERE 1 = 0;
CREATE TABLE emp3_tmo AS SELECT * FROM employees WHERE 1 = 0;

INSERT ALL
    WHEN salary < 5000 THEN
        INTO emp1_tmo
    WHEN salary BETWEEN 5000 AND 10000 THEN
        INTO emp2_tmo
    WHEN salary > 10000 THEN
        INTO emp3_tmo
SELECT * FROM employees;

ROLLBACK;

--14

CREATE TABLE emp0_tmo AS SELECT * FROM employees WHERE 1 = 0;

INSERT ALL
    WHEN department_id = 80 THEN INTO emp0_tmo
    WHEN salary < 5000 THEN INTO emp1_tmo
    WHEN salary BETWEEN 5000 AND 10000 THEN INTO emp2_tmo
    WHEN salary > 10000 THEN INTO emp3_tmo
SELECT * FROM employees;
ROLLBACK;

--15

UPDATE emp_tmo
SET salary = salary * 1.05;

ROLLBACK;

--16

UPDATE emp_tmo
SET job_id = 'SA_REP'
WHERE department_id = 80 AND commission_pct IS NOT NULL;

ROLLBACK;

--17

SELECT employee_id
FROM emp_tmo
WHERE last_name = 'Grant' AND first_name = 'Douglas';
UPDATE dept_tmo
SET manager_id = (SELECT employee_id
                  FROM emp_tmo
                  WHERE last_name = 'Grant' AND first_name = 'Douglas')
WHERE department_id = 20;

UPDATE emp_tmo
SET salary = salary + 1000
WHERE last_name = 'Grant' AND first_name = 'Douglas';

ROLLBACK;

--18

UPDATE emp_tmo e
SET salary = (SELECT salary
              FROM emp_tmo
              WHERE employee_id = e.manager_id)
WHERE salary = (SELECT MIN(salary) FROM emp_tmo);

ROLLBACK;

--19

UPDATE emp_tmo e
SET email = NVL(SUBSTR(last_name, 1), '.') || first_name
WHERE salary = (SELECT MAX(salary)
                FROM emp_tmo
                WHERE department_id = e.department_id);
                
--20

UPDATE emp_tmo e
SET salary = GREATEST(salary, (SELECT AVG(salary)
                               FROM emp_tmo))
WHERE hire_date = (SELECT MAX(hire_date)
                   FROM emp_tmo
                   WHERE department_id = e.department_id);
                   
--21

UPDATE emp_tmo e
SET (job_id, department_id) = (SELECT job_id, department_id
                              FROM emp_tmo
                              WHERE employee_id = 205)
WHERE employee_id = 114;

--22

ACCEPT dept_code PROMPT 'ID-ul departamentului';
SELECT * FROM dept_tmo WHERE department_id = &&dept_code;
ACCEPT dept_col PROMPT 'Care coloana vreti sa modificati?';
ACCEPT dept_val PROMPT 'Care e valoare cu care vreti sa inlocuiti?';
UPDATE dept_tmo
SET &&dept_col = &&dept_val
WHERE department_id = '&&dept_code';
UNDEFINE dept_code, dept_col, dept_val;

--23

DELETE FROM dept_tmo;
ROLLBACK;

--24

DELETE FROM emp_tmo
WHERE commission_pct IS NULL;
ROLLBACK;

--25

DELETE FROM dept_tmo d
WHERE NOT EXISTS (SELECT 1
                  FROM emp_tmo
                  WHERE department_id = d.department_id);
ROLLBACK;

--26

ACCEPT emp_cod PROMPT 'COD angajat:';
SELECT *
FROM emp_tmo
WHERE employee_id = &&emp_cod;
DELETE FROM emp_tmo
WHERE employee_id = &&emp_cod;
UNDEFINE emp_cod;

--27

COMMIT;

--28

--29

SAVEPOINT p;

--30

DELETE FROM emp_tmo;
SELECT * FROM emp_tmo;

--31

ROLLBACK TO p;

--32

COMMIT;




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

