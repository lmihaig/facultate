-- Laborator 1 362

-------------------------------------------------------------------------------

-- begin conexiune 1 db facultate



SELECT sysdate FROM dual;

SELECT 1 FROM dual;

DROP TABLE dual;

SELECT * FROM dual;

SELECT lower(dummy) AS x_mic
FROM dual;


SELECT first_name || ' ' || last_name AS FULL_name
FROM employees;


SELECT first_name || ' ' || last_name AS "full name"
FROM employees;


CREATE TABLE "test" (id number);

DROP TABLE "test";


CREATE TABLE "tesT" (id2 number);
CREATE TABLE test2 (id5 number);

INSERT INTO "test" values(1);


INSERT INTO "tesT" values(2);


-- table or view does not exist
SELECT * FROM test;
SELECT * FROM test2;

SELECT * FROM "tesT";

UPDATE "tesT"
SET id2 = 5
WHERE id2 = 4;


DELETE FROM "tesT";


--COMMIT;
ROLLBACK;



SELECT *
FROM EMPLOYEES e ;


SELECT *
FROM EMPLOYEES e 
WHERE lower(e.first_name) LIKE 'd%';
-- WHERE lower(e.first_name) LIKE 'D%';



-- not a group by expression
SELECT first_name, last_name, salary
FROM EMPLOYEES e 
GROUP BY employee_id;



SELECT salary
FROM employees;


SELECT avg(salary)
FROM employees;


SELECT round(avg(salary))
FROM employees;


SELECT round(avg(salary), 2)
FROM employees;


-- eroare
SELECT avg(salary), department_id
FROM employees;



SELECT avg(salary), department_id
FROM employees
GROUP BY DEPARTMENT_ID ;



-- eroare
SELECT avg(salary), department_id
FROM employees
GROUP BY DEPARTMENT_ID
HAVING salary > 5000;


-- eroare pe oracle
SELECT avg(salary), department_id
FROM employees
GROUP BY DEPARTMENT_ID
where salary > 5000;



SELECT avg(salary), department_id
FROM employees
where salary > 5000
GROUP BY DEPARTMENT_ID;


SELECT avg(salary), department_id
FROM employees
GROUP BY DEPARTMENT_ID
HAVING avg(salary) > 5000;



SELECT avg(salary), department_id
FROM employees
GROUP BY DEPARTMENT_ID
HAVING min(salary) > 5000;



SELECT avg(salary), nvl(department_id, '0')
FROM employees
GROUP BY DEPARTMENT_ID
HAVING min(salary) > 5000;


-- nu face ce vrem
SELECT avg(salary), nullif(department_id, 1)
FROM employees
GROUP BY DEPARTMENT_ID
HAVING min(salary) > 5000;


SELECT avg(salary), coalesce(department_id, 0)
FROM employees
GROUP BY DEPARTMENT_ID
HAVING min(salary) > 5000;


SELECT avg(salary), department_id
FROM employees
GROUP BY DEPARTMENT_ID
HAVING DEPARTMENT_ID > 50;


SELECT avg(salary), department_id
FROM employees
GROUP BY DEPARTMENT_ID
HAVING DEPARTMENT_ID > 50;


-- eroare
SELECT avg(salary), department_name
FROM employees e JOIN DEPARTMENTS d using(department_id)
GROUP BY DEPARTMENT_ID
HAVING DEPARTMENT_ID > 50;


SELECT avg(salary), department_name
FROM employees e JOIN DEPARTMENTS d using(department_id)
GROUP BY e.DEPARTMENT_ID
HAVING DEPARTMENT_ID > 50;


SELECT avg(salary), department_name
FROM employees e JOIN DEPARTMENTS d using(department_id)
GROUP BY department_name, DEPARTMENT_ID 
HAVING DEPARTMENT_ID > 50;



SELECT round(avg(salary)), department_name
FROM employees e JOIN DEPARTMENTS d using(department_id)
GROUP BY department_name, DEPARTMENT_ID 
HAVING DEPARTMENT_ID > 50;


SELECT round(avg(salary)), department_name
FROM employees e JOIN DEPARTMENTS d ON e.DEPARTMENT_ID = d.DEPARTMENT_ID 
GROUP BY department_name, e.DEPARTMENT_ID 
HAVING e.DEPARTMENT_ID > 50;


SELECT round(avg(salary)), COALESCE(department_name, 'Not available')
FROM employees e LEFT JOIN DEPARTMENTS d ON e.DEPARTMENT_ID = d.DEPARTMENT_ID 
GROUP BY department_name, e.DEPARTMENT_ID ;
--HAVING e.DEPARTMENT_ID > 50;



SELECT round(avg(salary)), COALESCE(department_name, 'Not available')
FROM employees e RIGHT JOIN DEPARTMENTS d ON e.DEPARTMENT_ID = d.DEPARTMENT_ID 
GROUP BY department_name, e.DEPARTMENT_ID ;



SELECT round(avg(salary)), COALESCE(department_name, 'Not available')
FROM employees e RIGHT JOIN DEPARTMENTS d ON d.DEPARTMENT_ID = e.DEPARTMENT_ID 
GROUP BY department_name, e.DEPARTMENT_ID ;


-- echivalent cu join
SELECT round(avg(salary)), COALESCE(department_name, 'Not available')
FROM employees e INNER JOIN DEPARTMENTS d ON d.DEPARTMENT_ID = e.DEPARTMENT_ID 
GROUP BY department_name, e.DEPARTMENT_ID ;



SELECT COALESCE(round(avg(salary)), 0), COALESCE(department_name, 'Not available')
FROM employees e FULL JOIN DEPARTMENTS d ON d.DEPARTMENT_ID = e.DEPARTMENT_ID 
GROUP BY department_name, e.DEPARTMENT_ID ;



SELECT *
FROM employees;


SELECT e.first_name AS ang, m.first_name AS manager
FROM EMPLOYEES e
JOIN employees m ON e.manager_id = m.EMPLOYEE_ID ;



SELECT DISTINCT manager_id
FROM employees;


SELECT COALESCE(round(avg(salary)), 0), COALESCE(department_name, 'Not available')
FROM employees e JOIN DEPARTMENTS d ON d.DEPARTMENT_ID = e.DEPARTMENT_ID 
GROUP BY department_name, e.DEPARTMENT_ID;



SELECT COALESCE(round(avg(salary)), 0) AS sal, COALESCE(department_name, 'Not available')
FROM employees e JOIN DEPARTMENTS d ON d.DEPARTMENT_ID = e.DEPARTMENT_ID 
GROUP BY department_name, e.DEPARTMENT_ID
ORDER BY sal desc;



WITH deps AS (
	SELECT COALESCE(round(avg(salary)), 0) AS sal, COALESCE(department_name, 'Not available')
	FROM employees e JOIN DEPARTMENTS d ON d.DEPARTMENT_ID = e.DEPARTMENT_ID 
	GROUP BY department_name, e.DEPARTMENT_ID
	ORDER BY sal DESC
)
SELECT *
FROM deps;



EXPLAIN PLAN
    SET STATEMENT_ID='plan1'
    FOR
    SELECT employee_id
FROM employees;

    SELECT * FROM table(DBMS_XPLAN.DISPLAY('plan_table', 'plan1', 'all'));  


EXPLAIN PLAN
    SET STATEMENT_ID='plan1'
    FOR
    SELECT *
FROM employees;

    SELECT * FROM table(DBMS_XPLAN.DISPLAY('plan_table', 'plan1', 'all'));  


CREATE TABLE emp2_mcm AS SELECT * FROM employees;


-- SELECT * INTO emp22_mcm FROM EMPLOYEES e ;

EXPLAIN PLAN
    SET STATEMENT_ID='plan1'
    FOR
    SELECT first_name
FROM emp2_mcm
WHERE first_name = 'Steven';

    SELECT * FROM table(DBMS_XPLAN.DISPLAY('plan_table', 'plan1', 'all'));  



CREATE INDEX emp_nume_idx ON emp2_mcm(first_name);



SELECT first_name, EMPLOYEE_ID , department_name
FROM EMPLOYEES e JOIN DEPARTMENTS d using(DEPARTMENT_id)
WHERE rownum <= 10
ORDER BY employee_id;






-- end conexiune 1 db facultate

-------------------------------------------------------------------------------

-- begin conexiune 2 db facultate

SELECT * FROM "tesT";

SELECT * FROM test2;

-- end conexiune 2 db facultate

-------------------------------------------------------------------------------

-- begin conexiune db oracle local user normal


SELECT *
FROM EMPLOYEES e 
ORDER BY employee_id
FETCH FIRST 10 ROWS ONLY;

-- end conexiune db oracle local user normal

-------------------------------------------------------------------------------


-- begin conexiune db sqlite


SELECT *
FROM EMPLOYEES e 
ORDER BY employee_id
limit 10;


-- end conexiune db sqlite

-------------------------------------------------------------------------------

-- begin conexiune db local mariadb user normal

use hr;


SELECT *
FROM employees e 
ORDER BY employee_id
FETCH FIRST 10 ROWS ONLY;


-- end conexiune db local mariadb user normal

-------------------------------------------------------------------------------

-- begin conexiune db local postgres user normal

SELECT *
FROM employees e 
ORDER BY employee_id
FETCH FIRST 10 ROWS ONLY;

-- end conexiune db local postgres user normal

-------------------------------------------------------------------------------

