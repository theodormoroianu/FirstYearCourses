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


-- LAB 9 =============================================================================

--1

CREATE TABLE angajati_tmo (
    cod_ang number(4),
    nume varchar2(20),
    prenume varchar2(20),
    email char(15),
    data_ang date,
    job varchar2(20),
    cod_sef number(4),
    salariu number(8, 2),
    cod_dep number(2));
DROP TABLE angajati_tmo;

CREATE TABLE angajati_tmo (
    cod_ang number(4) PRIMARY KEY,
    nume varchar2(20) NOT NULL,
    prenume varchar2(20) NOT NULL,
    email char(15),
    data_ang date,
    job varchar2(20),
    cod_sef number(4),
    salariu number(8, 2),
    cod_dep number(2));

DROP TABLE angajati_tmo;

CREATE TABLE angajati_tmo (
    cod_ang number(4),
    nume varchar2(20) NOT NULL,
    prenume varchar2(20),
    email char(15),
    data_ang date DEFAULT sysdate,
    job varchar2(20),
    cod_sef number(4),
    salariu number(8, 2) NOT NULL,
    cod_dep number(2),
    PRIMARY KEY(cod_ang),
    FOREIGN KEY (cod_ang) REFERENCES employees(employee_id));

DESC angajati_tmo;

SELECT * FROM user_constraints
WHERE LOWER(table_name) = 'angajati_tmo';

--2

TRUNCATE TABLE angajati_tmo;

INSERT INTO angajati_tmo (cod_ang, nume, prenume, email, data_ang, job, cod_sef, salariu, cod_dep)
SELECT 100, 'Nume1', 'Prenume1', NULL, NULL, 'Director', NULL, 20000, 10 FROM DUAL
UNION
SELECT 103, 'Nume4', 'Prenume4', NULL, NULL, 'Inginer', 100, 9000, 20 FROM DUAL;

INSERT INTO angajati_tmo
SELECT 101, 'Nume2', 'Prenume2', 'Nume2', '02-FEB-2014', 'Inginer', 100, 10000, 10 FROM dual;

--3

CREATE TABLE angajati10_tmo AS (SELECT *
                                FROM angajati_tmo
                                WHERE cod_dep = 10);
                                
DESC angajati10_tmo;

--4

ALTER TABLE angajati_tmo
ADD comision number(4, 2);

DESC angajati_tmo;

--5

ALTER TABLE angajati_tmo
MODIFY salariu NUMBER(1, 10); -- NU

--6

ALTER TABLE angajati_tmo
MODIFY salariu DEFAULT 10;

--7

ALTER TABLE angajati_tmo
MODIFY (comision NUMBER(2, 2), salariu NUMBER(10, 2));

--8

UPDATE angajati_tmo
SET comision = 0.1
WHERE LOWER(job) LIKE 'i%';

--9

ALTER TABLE angajati_tmo
MODIFY email VARCHAR2(100);

--10

ALTER TABLE angajati_tmo
ADD nr_telefon VARCHAR2(10) DEFAULT '123';

--11

SELECT *
FROM angajati_tmo;

ALTER TABLE angajati_tmo
DROP (nr_telefon);

--12

RENAME angajati_tmo TO angajati3_tmo;

--13

SELECT * FROM TAB
WHERE tname = 'ANGAJATI3_TMO';
RENAME angajati3_tmo TO angajati_tmo;

--14

TRUNCATE TABLE angajati_tmo;

--15

DROP TABLE departamente_tmo;
CREATE TABLE departamente_tmo (
    cod_dep number(2),
    nume varchar2(15) NOT NULL,
    cod_director number(4)
);
DESC departamente_tmo;

--16

INSERT INTO departamente_tmo
(SELECT 10, 'Administrativ', 100 FROM DUAL
    UNION
 SELECT 20, 'PRoiectare', 101 FROM DUAL
    UNION
 SELECT 30, 'Programara', null FROM DUAL);

--17

ALTER TABLE departamente_tmo
ADD CONSTRAINT dep_tmo_pk PRIMARY KEY(cod_dep);

--18

DESC angajati_tmo;
DESC departamente_tmo;
ALTER TABLE angajati_tmo
ADD CONSTRAINT ang_fk FOREIGN KEY (cod_dep) REFERENCES departamente_tmo(cod_dep);

DROP TABLE angajati_tmo;
CREATE TABLE angajati_tmo (
    cod_ang NUMBER(4) PRIMARY KEY,
    nume VARCHAR2(20) NOT NULL,
    prenume VARCHAR2(20) NOT NULL,
    email VARCHAR2(100),
    data_ang DATE,
    job VARCHAR2(20),
    cod_sef NUMBER(4),
    salariu NUMBER(10, 2) NOT NULL,
    cod_dep NUMBER(2),
    comision NUMBER(2, 2),
    CONSTRAINT fk_ang_tmo FOREIGN KEY (cod_dep) REFERENCES departamente_tmo(cod_dep),
    CONSTRAINT un_num_pren UNIQUE(nume, prenume),
    CONSTRAINT un_email UNIQUE(email),
    CONSTRAINT chk_ang_tmo CHECK(cod_dep > 0),
    CONSTRAINT chk2_Ang_tmo CHECK(salariu > 100 * comision)
);

--19
DROP TABLE angajati_tmo;
CREATE TABLE angajati_tmo (
    cod_ang NUMBER(4),
    nume VARCHAR2(20) NOT NULL,
    prenume VARCHAR2(20) NOT NULL,
    email VARCHAR2(100),
    data_ang DATE,
    job VARCHAR2(20),
    cod_sef NUMBER(4),
    salariu NUMBER(10, 2) NOT NULL,
    cod_dep NUMBER(2),
    comision NUMBER(2, 2),
    PRIMARY KEY(cod_ang),
    CONSTRAINT fk_ang_tmo FOREIGN KEY (cod_dep) REFERENCES departamente_tmo(cod_dep),
    CONSTRAINT un_num_pren UNIQUE(nume, prenume),
    CONSTRAINT un_email UNIQUE(email),
    CONSTRAINT chk_ang_tmo CHECK(cod_dep > 0),
    CONSTRAINT chk2_Ang_tmo CHECK(salariu > 100 * comision)
);

--20

TRUNCATE TABLE angajati_tmo;
ALTER TABLE angajati_tmo
ADD CONSTRAINT chk2_Ang_tmo CHECK(salariu > 0);

SELECT *
FROM departamente_tmo;

INSERT INTO angajati_tmo (cod_ang, nume, prenume, salariu, cod_dep)
VALUES(1, 'popescu', 'marian', 123, 10);

--21

DELETE FROM departamente_tmo;

--22

DROP TABLE departame
SELECT *
FROM user_tables
WHERE LOWER(table_name) = 'angajati_tmo';


--23

SELECT *
FROM user_constraints
WHERE LOWER(table_name) IN ('departamente_tmo', 'angajati_tmo');

SELECT *
FROM user_cons_columns
WHERE LOWER(table_name) IN ('departamente_tmo', 'angajati_tmo');

--24

SELECT *
FROM angajati_tmo;

UPDATE angajati_tmo
SET email = nume
WHERE email IS NULL;

ALTER TABLE angajati_tmo
MODIFY (email NOT NULL);


--25

DESC angajati_tmo;
INSERT INTO angajati_tmo (cod_ang, nume, prenume, email, salariu, cod_dep)
VALUES (643, '123', '123', '123', 123, 50);

--26

DESC departamente_tmo;
INSERT INTO departamente_tmo
VALUES (60, 'Testare', NULL);

COMMIT;

--27

DELETE FROM departamente_tmo
WHERE cod_dep = 20;

--28

DELETE FROM departamente_tmo
WHERE cod_dep = 60;

ROLLBACK;

--29

DESC angajati_tmo;

ALTER TABLE angajati_tmo
ADD CONSTRAINT fk_sef FOREIGN KEY (cod_sef) REFERENCES angajati_tmo(cod_ang);

INSERT INTO angajati_tmo(cod_ang, nume, prenume, email, cod_sef, salariu)
VALUES (151, '1123', '1123', '1213', 114, 123);

--30

INSERT INTO angajati_tmo(cod_ang, nume, prenume, email, salariu)
VALUES (114, '123', '123', '123', 23);

--31

SELECT *
FROM user_constraints
WHERE LOWER(table_name) = 'angajati_tmo';

DESC departamente_tmo;

ALTER TABLE angajati_tmo
DROP CONSTRAINT fk_ang_tmo;
ALTER TABLE angajati_tmo
ADD CONSTRAINT fk_dep FOREIGN KEY(cod_dep) REFERENCES departamente_tmo(cod_dep) ON DELETE CASCADE;

--32

DELETE FROM departamente_tmo
WHERE cod_dep = 20;
ROLLBACK;
--33

UPDATE departamente_tmo
SET cod_Director = NULL;

ALTER TABLE departamente_tmo
ADD CONSTRAINT fk_director FOREIGN KEY (cod_director)
            REFERENCES angajati_tmo(cod_ang) ON DELETE SET NULL;

--34

INSERT INTO angajati_tmo(cod_ang, nume, prenume, email, cod_dep, salariu)
VALUES (102, '102', '102', '102', 30, 12);

UPDATE departamente_tmo
SET cod_director = 102
WHERE cod_dep = 30;

--35

ALTER TABLE angajati_tmo
ADD CONSTRAINT chk_sal CHECK(salariu <= 30000);

--36

INSERT INTO angajati_tmo(cod_ang, nume, prenume, email, salariu)
VALUES(1234, '1233', '1232', '42', 35000);

--37

ALTER TABLE angajati_tmo
DISABLE CONSTRAINT chk_sal;

ALTER TABLE angajati_tmo
ENABLE CONSTRAINT chk_sal;


-- LAB 10 ===================================================================

--1
CREATE OR REPLACE VIEW VIZ_EMP30_TMO AS
SELECT employee_id, last_name, email, hire_date, job_id
FROM emp_tmo
WHERE department_id = 30;

SELECT * FROM viz_emp30_tmo;
DESC emp_tmo;
--2

INSERT INTO viz_emp30_tmo
VALUES(12, '123', 't', sysdate, '12');

--3

DESC emp_tmo;

;
SELECT * FROM departamente_tmo;
SELECT * FROM angajati_tmo;
DESC departamente_tmo;
DESC angajati_tmo;




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

