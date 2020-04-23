-- TEMA 2 LAB
-- MOROIANU THEODOR

-- 1

SELECT *
FROM employees
where UPPER(last_name) LIKE 'K%';

-- 2

select last_name, first_name, employee_id, salary
from employees
where salary = (SELECT MIN(salary)
                  FROM employees);

-- 3

SELECT DISTINCT employee_id, last_name, first_name
FROM employees
WHERE employee_id IN (SELECT manager_id
                      FROM employees
                      WHERE department_id = 30);
                      
-- 4

SELECT employee_id, last_name, first_name, (SELECT COUNT(1)
                                            FROM employees
                                            WHERE manager_id = e.employee_id) as "nr_subalterns"
from employees e;

-- 5

SELECT employee_id, last_name, first_name
FROM employees e
WHERE (SELECT COUNT(1)
       FROM employees
       WHERE last_name = e.last_name) = 2;
       
-- 6

SELECT department_id, department_name
FROM departments d
WHERE (SELECT COUNT(DISTINCT job_id)
       FROM employees
       WHERE department_id = d.department_id) >= 2;

-- 7

SELECT qty, o.prod_id, prod_desc
FROM orders_tbl o, products_tbl p
WHERE o.prod_id = p.prod_id
      AND LOWER(p.prod_desc) like '%plastic%';

-- 8

SELECT cust_name, 'client'
FROM customer_tbl
UNION
SELECT last_name || ' ' || first_name, 'angajat'
FROM employee_tbl;

-- 9

SELECT DISTINCT prod_desc
FROM products_tbl p, orders_tbl o
WHERE p.prod_id = o.prod_id
    AND EXISTS (SELECT *
                FROM orders_tbl oo
                WHERE sales_rep = o.sales_rep
                    AND (SELECT LOWER(prod_desc)
                         FROM products_tbl
                         WHERE prod_id = oo.prod_id) like '% p%');
                         
-- 10

SELECT cust_name
FROM customer_tbl c
WHERE EXISTS (SELECT 1
              FROM orders_tbl
              WHERE cust_id = c.cust_id
                AND TO_CHAR(ord_date, 'dd') = 17);

-- 11

SELECT last_name, first_name, bonus
FROM employee_pay_tbl p, employee_tbl e
WHERE e.emp_id = p.emp_id
    AND salary < 32000 AND bonus * 17 < 32000;
 
-- 12

SELECT last_name, first_name, NVL(SUM(o.qty), 0)
FROM employee_tbl e LEFT JOIN orders_tbl o
ON o.sales_rep = e.emp_id
GROUP BY e.emp_id, e.last_name, e.first_name
HAVING SUM(o.qty) > 50 OR nvl(SUM(o.qty), 0) = 0;

-- 13

SELECT last_name, first_name, salary, MAX(ord_date)
FROM (employee_tbl e JOIN employee_pay_tbl p ON e.emp_id = p.emp_id) JOIN orders_tbl o
ON e.emp_id = o.sales_rep
GROUP BY last_name, first_name, salary, o.sales_rep;

-- 14

SELECT prod_desc
FROM products_tbl
WHERE cost > (SELECT AVG(cost)
              FROM products_tbl);
              
-- 15

SELECT last_name, first_name, salary, bonus, (SELECT SUM(salary) FROM employee_pay_tbl),
        (SELECT SUM(bonus) FROM employee_pay_tbl)
FROM employee_tbl e, employee_pay_tbl p
WHERE e.emp_id = p.emp_id;

-- 16

SELECT DISTINCT city
FROM employee_Tbl e
WHERE (SELECT COUNT(1)
       FROM orders_tbl
       WHERE sales_rep = e.emp_id) >=
      (SELECT MAX(COUNT(1))
       FROM orders_tbl
       GROUP BY sales_rep);
       
-- 17

SELECT emp_id, last_name, COUNT(DECODE(TO_CHAR(ord_date, 'mm'), 9, 1)) "sept",
    COUNT(DECODE(TO_CHAR(ord_date, 'mm'), 10, 1)) "oct"
FROM employee_tbl e LEFT JOIN orders_tbl o
ON emp_id = sales_rep
GROUP BY emp_id, last_name;

-- 18

SELECT cust_name, cust_city
FROM customer_tbl c
WHERE cust_id NOT IN (SELECT cust_id FROM orders_tbl)
AND REGEXP_LIKE(cust_address, '^[0-9]');

-- 19

SELECT DISTINCT e.emp_id, last_name, city, c.cust_id, cust_name, cust_city
FROM employee_tbl e, customer_tbl c
WHERE EXISTS (SELECT 1
              FROM orders_tbl
              WHERE sales_rep = e.emp_id AND cust_id = c.cust_id)
AND city != cust_city;

-- 20

SELECT AVG(NVL(salary, 0))
FROM employee_pay_tbl;

-- 21

SELECT CUST_ID, CUST_NAME  ---- DA
FROM CUSTOMER_TBL
WHERE CUST_ID =
(SELECT CUST_ID
FROM ORDERS_TBL
WHERE ORD_NUM = '16C17');

SELECT EMP_ID, SALARY  ---- NU
FROM EMPLOYEE_PAY_TBL
WHERE SALARY BETWEEN '20000'
AND (SELECT SALARY
FROM EMPLOYEE_ID
WHERE SALARY = '40000');


-- 22

SELECT last_name, pay_rate
FROM employee_tbl e, employee_pay_tbl p
WHERE e.emp_id = p.emp_id
AND pay_rate > (SELECT MAX(pay_rate)
                FROM employee_tbl e2, employee_pay_tbl p2
                WHERE e2.emp_id = p2.emp_id
                AND UPPER(last_name) like '%LL%');












