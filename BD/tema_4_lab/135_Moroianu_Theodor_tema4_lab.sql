-- MOROIANU THEODOR - grupa 135

--1
SELECT s_last
FROM student s
WHERE '(null)' NOT IN (SELECT grade
                       FROM enrollment
                       WHERE s_id = s.s_id);
                       
-- 2
SELECT DISTINCT bldg_code
FROM location
WHERE bldg_code NOT IN (SELECT bldg_code
                        FROM location
                        WHERE loc_id NOT IN (SELECT loc_id
                                             FROM course_section));
                                             
--3
SELECT DISTINCT f.f_last
FROM faculty f join student s ON (s.f_id = f.f_id)
     JOIN enrollment e ON (e.s_id = s.s_id)
WHERE e.grade = 'A'
INTERSECT
SELECT f.f_last
FROM faculty f JOIN course_section c ON (f.f_id = c.f_id)
WHERE c.course_no LIKE 'MIS%';

--4
SELECT f_last
FROM (SELECT f_last
      FROM faculty f
      ORDER BY (SELECT MAX((SELECT COUNT(s_id)
                           FROM enrollment
                           WHERE c_sec_id = c.c_sec_id))
                FROM course_section c
                WHERE f_id = f.f_id))
WHERE rownum = 1
UNION
SELECT f_last
FROM (SELECT f_last
      FROM faculty f
      ORDER BY (SELECT MAX(capacity)
                FROM location l JOIN course_section c ON (l.loc_id = c.loc_id)
                WHERE f_id = f.f_id))
WHERE rownum = 1;

--5
SELECT f_last
FROM faculty f
WHERE loc_id IN (SELECT loc_id
                 FROM location
                 WHERE capacity = (SELECT MIN(capacity) FROM location))
      AND f_id IN (SELECT f_id
                  FROM course_section
                  WHERE max_enrl = (SELECT MIN(max_enrl)
                                    FROM course_section
                                    WHERE loc_id = (SELECT loc_id
                                                    FROM course_section
                                                    WHERE max_enrl = (SELECT MAX(max_enrl) FROM course_section))));


--6
SELECT avg(capacity)
FROM location l
WHERE EXISTS (SELECT *
              FROM course_section
              WHERE f_id = (SELECT f_id FROM faculty WHERE f_first = 'Teresa')
              AND loc_id = l.loc_id);
SELECT avg(max_enrl)
FROM course_section c JOIN enrollment e ON (c.c_sec_id = e.c_sec_id)
    JOIN student s ON (s.s_id = e.s_id)
WHERE s_first = 'Tammy';

--7
SELECT bldg_code, AVG(capacity)
FROM location l
WHERE EXISTS (SELECT *
              FROM course_section c
              WHERE loc_id = l.loc_id
              AND (SELECT course_name
                   FROM course
                   WHERE course_no = c.course_no) like '%Systems%')
GROUP BY bldg_code;

--8
SELECT bldg_code, AVG(capacity)
FROM location l
GROUP BY bldg_code
HAVING EXISTS (SELECT *
               FROM course_section cs JOIN course c ON (c.course_no = cs.course_no)
               WHERE c.course_name like '%Systems%' AND EXISTS (SELECT *
                                                            FROM location
                                                            WHERE bldg_code = l.bldg_code
                                                                 AND cs.loc_id = loc_id));

--9
SELECT course_name
FROM course
WHERE NOT EXISTS (SELECT course_name
                  FROM course
                  WHERE course_name like '%Java%')
      OR course_name like '%Java%';

--10
SELECT course_name
FROM course t
WHERE DECODE((SELECT COUNT(1)
              FROM course_section c JOIN faculty f ON (c.f_id = f.f_id)
              WHERE c.course_no = t.course_no
              AND f.f_last = 'Brown'), 1, 1, 0) +
     DECODE((SELECT COUNT(1)
             FROM enrollment e JOIN student s ON (e.s_id = s.s_id) JOIN course_section c ON (e.c_sec_id = c.c_sec_id)
             WHERE s.s_last = 'Jones' AND c.course_no = t.course_no), 1, 1, 0) + 
     CASE WHEN course_name LIKE '%Database%' THEN 1 ELSE 0 END +
     DECODE((SELECT COUNT(1)
             FROM term trm JOIN course_section c ON (trm.term_id = c.term_id)
             WHERE c.course_no = t.course_no
             AND EXTRACT(year FROM start_date) > 2007), 1, 1, 0) >= 3;

--11
SELECT term_desc, (SELECT COUNT(*)
                   FROM course_section
                   WHERE term_id = t.term_id)
FROM term t
WHERE (SELECT COUNT(*)
       FROM course_section
       WHERE term_id = t.term_id) = (SELECT MAX(COUNT(*))
                                     FROM course_section
                                     GROUP BY term_id);
                                     
--12
SELECT grade, nr_studenti
FROM (SELECT grade, count(s_id) as nr_studenti
      FROM (SELECT grade, s_id
            FROM enrollment
            WHERE grade IS NOT NULL)
      GROUP BY grade
      ORDER BY count(s_id) desc)
WHERE rownum = 1;

--13
SELECT term_desc, nr
FROM (SELECT term_desc, COUNT(*) nr
      FROM term t JOIN course_section c ON (t.term_id = c.term_id) JOIN
            course cs ON (c.course_no = cs.course_no)
      GROUP BY term_desc
      ORDER BY COUNT(*) desc)
WHERE rownum = 1;

--14
SELECT loc_id
FROM location l
WHERE EXISTS (SELECT *
              FROM course_section
              WHERE loc_id = l.loc_id
                     AND course_no like '%MIS%')
     AND EXISTS (SELECT *
                 FROM course_section
                 WHERE loc_id = l.loc_id
                 AND course_no like '%CS%');

--15
SELECT bldg_code
FROM location
GROUP BY bldg_code
HAVING COUNT(*) = 1;


desc course_section;
select * from course_section;
select * from faculty;
SELECT * FROM location;
SELECT * FROM enrollment;
SELECT * FROM student;
SELECT * FROM course;
SELECT * FROM term;
