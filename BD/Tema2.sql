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


select * from customer_tbl;
select * from orders_tbl;
select * from products_tbl;
select * from employee_tbl;












