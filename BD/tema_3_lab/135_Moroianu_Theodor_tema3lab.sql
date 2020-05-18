-- Tema 3 laborator
-- Moroianu Theodor 135

-- 1

SELECT s_id "Cod", s_last || ' ' || s_first "Student sau Curs", 'Student' "Tip"
FROM student
WHERE f_id IN (SELECT f_id
               FROM faculty
               WHERE lower(f_last) = 'brown')
UNION
SELECT course_no, course_name, 'Curs'
FROM course
WHERE course_no IN (SELECT course_no
                    FROM course_section
                    WHERE f_id IN (SELECT f_id
                                   FROM faculty
                                   WHERE lower(f_last) = 'brown'));
                                   
-- 2

WITH cs AS
     (SELECT c_sec_id
      FROM course_section
      WHERE lower(course_no) LIKE 'cs%'),
     bd AS
     (SELECT c_sec_id
      FROM course_section
      WHERE lower(course_no) LIKE 'mis%')
SELECT s_id, s_last
FROM student s
WHERE EXISTS (SELECT *
              FROM enrollment
              WHERE s_id = s.s_id AND c_sec_id IN (SELECT * FROM bd))
      AND NOT EXISTS (SELECT *
                      FROM enrollment
                      WHERE s_id = s.s_id AND c_sec_id IN (SELECT * FROM cs));


-- 3

SELECT s_id, s_last
FROM student s
WHERE EXISTS (SELECT * 
              FROM enrollment
              WHERE s_id = s.s_id AND NVL(grade, 'C') = 'C');

-- 4

SELECT loc_id, bldg_code, capacity
FROM location
WHERE capacity >= (SELECT MAX(capacity)
                   FROM location);

-- 5

CREATE TABLE t (id NUMBER PRIMARY KEY);
INSERT INTO t VALUES(1);
INSERT INTO t VALUES(2);
INSERT INTO t VALUES(4);
INSERT INTO t VALUES(6);
INSERT INTO t VALUES(8);
INSERT INTO t VALUES(9);

SELECT MIN(id) + 1
FROM t
WHERE id + 1 not in (SELECT * FROM t)
UNION
SELECT MAX(id) - 1
FROM t
WHERE id - 1 not in (SELECT * FROM t); 

-- 6

SELECT f_id, f_last,
    DECODE((SELECT COUNT(*) FROM student WHERE f_id = f.f_id),
           0, 'NU',
           'DA (' || (SELECT COUNT(*) FROM student WHERE f_id = f.f_id) || ')') "Student",
    DECODE((SELECT COUNT(*) FROM course_section WHERE f_id = f.f_id),
           0, 'NU',
           'DA (' || (SELECT COUNT(*) FROM course_section WHERE f_id = f.f_id) || ')') "Curs"
FROM faculty f;
           
-- 7

SELECT a.term_desc, b.term_desc
FROM term a, term b
WHERE SUBSTR(a.term_desc, 0, LENGTH(a.term_desc) - 1) = SUBSTR(b.term_desc, 0, LENGTH(b.term_desc) - 1);

-- 8

SELECT DISTINCT s_id, s_last
FROM student s JOIN course_section c1 ON (c1.c_sec_id IN (SELECT c_sec_id
                                                          FROM enrollment
                                                          WHERE s_id = s.s_id))
               JOIN course_section c2 ON (c2.c_sec_id IN (SELECT c_sec_id
                                                          FROM enrollment
                                                          WHERE s_id = s.s_id))
WHERE LENGTH(c1.course_no) >= 5 AND LENGTH(c2.course_no) >= 5 AND
      SUBSTR(c1.course_no, 5, 1) != SUBSTR(c2.course_no, 5, 1); 

-- 9

SELECT a.c_sec_id, b.c_sec_id
FROM course_section a JOIN course_section b ON (a.term_id = b.term_id)
WHERE a.c_sec_id > b.c_sec_id;

-- 10

SELECT c_sec_id, course_no, term_desc, max_enrl
FROM course_section c JOIN term t ON (c.term_id = t.term_id)
WHERE max_enrl < (SELECT capacity
                  FROM location
                  WHere loc_id = 1);
                  
-- 11

SELECT c_sec_id, course_no, max_enrl
FROM course_section
WHERE max_enrl = (SELECT MIN(max_enrl)
                  FROM course_section);

-- 12

SELECT f.f_id, f_last, AVG(max_enrl)
FROM faculty f JOIN course_section c ON (f.f_id = c.f_id)
GROUP BY f.f_id, f_last;

-- 13

SELECT f.f_id, f_last, COUNT(*)
FROM faculty f JOIN student s ON (f.f_id = s.f_id)
GROUP BY f.f_id, f_last
HAVING COUNT(*) >= 3;

-- 14

SELECT c_sec_id, course_no, c.loc_id, l.capacity
FROM course_section c JOIN location l ON (c.loc_id = l.loc_id);

-- 15

SELECT term_desc, AVG(max_enrl)
FROM term t JOIN course_section c ON (t.term_id = c.term_id)
GROUP BY term_desc
HAVING term_desc LIKE '%2007%';


-- description of tables

desc Student;
desc Faculty;
select * from faculty;
select * from student;
select * from course_section;
select * from enrollment;
select * from term;
select * from location;

