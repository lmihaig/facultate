
-- L8 362


CREATE OR REPLACE FUNCTION func7(nume_dep IN departments.department_name%type)
RETURN sys_refcursor
IS
	c sys_refcursor;
BEGIN
	OPEN c FOR
		SELECT first_name, salary, round(MONTHS_BETWEEN(sysdate, hire_date)) AS nr
		FROM EMPLOYEES e JOIN DEPARTMENTS d ON e.DEPARTMENT_ID = d.DEPARTMENT_ID
		WHERE d.DEPARTMENT_NAME = nume_dep;

	RETURN c;
END func7;


SELECT func7('Sales')
FROM dual;


DECLARE
	c sys_refcursor;
	TYPE rec_ang IS RECORD (
		fn employees.first_name%TYPE,
		sal employees.salary%TYPE,
		nr number
	);
	rec rec_ang;
BEGIN
	c := func7('IT');

	LOOP
		FETCH c
		INTO rec;
		EXIT WHEN c%notfound;
		dbms_output.put_line(rec.fn || ' ' || rec.sal || ' ' || rec.nr);
	END LOOP;

	CLOSE c;
END;



SELECT hire_date, sysdate, round(MONTHS_BETWEEN(hire_date, sysdate)) AS nr
FROM employees
ORDER BY nr desc;


SELECT LINE, POSITION, TEXT
FROM USER_ERRORS
WHERE NAME = UPPER('trig8');




SELECT *
FROM EMP_DETAILS_VIEW edv ;


UPDATE EMP_DETAILS_VIEW 
SET LOCATION_ID = 1400
WHERE EMPLOYEE_ID = 100;




CREATE OR REPLACE TRIGGER trig6
BEFORE
INSERT OR UPDATE OF department_id
ON emp2_mcm
FOR EACH ROW
DECLARE
	nr NUMBER;
BEGIN
	SELECT count(*)
	INTO nr
	--FROM EMP2_MCM
	FROM employees
	WHERE DEPARTMENT_ID = :NEW.department_id;

	IF nr > 20 THEN
		raise_application_error(-20001, 'nu se poate, prea multa lume');
	END IF;
END trig6;

SELECT employee_id, department_id
FROM EMP2_MCM em ;


UPDATE EMP2_MCM
SET DEPARTMENT_ID = 60
WHERE EMPLOYEE_ID = 103;

ROLLBACK;



SELECT USER 
FROM dual;


CREATE TABLE dep_mcm AS SELECT * FROM DEPARTMENTS;


ALTER TABLE dep_mcm ADD nr_ang NUMBER;


UPDATE dep_mcm d
SET nr_ang = (
	SELECT count(*)
	FROM employees e
	WHERE e.department_id = d.department_id);


SELECT *
FROM dep_mcm;

DELETE
FROM EMP2_MCM em
WHERE EMPLOYEE_ID = 119;

ROLLBACK;

CREATE OR REPLACE TRIGGER trig7
AFTER
INSERT OR DELETE OR UPDATE OF department_id
ON emp2_mcm
FOR EACH row
BEGIN
	IF inserting THEN
		UPDATE dep_mcm d
		SET nr_ang = nr_ang + 1
		WHERE d.DEPARTMENT_ID = :NEW.department_id;
	ELSIF updating THEN
		UPDATE dep_mcm d
		SET nr_ang = nr_ang + 1
		WHERE d.DEPARTMENT_ID = :NEW.department_id;
		UPDATE dep_mcm d
		SET nr_ang = nr_ang - 1
		WHERE d.DEPARTMENT_ID = :OLD.department_id;
	ELSIF deleting THEN
		UPDATE dep_mcm d
		SET nr_ang = nr_ang - 1
		WHERE d.DEPARTMENT_ID = :OLD.department_id;
	END IF;
END trig7;



CREATE TABLE loguri (
	timp timestamp,
	usr varchar2(50),
	actiune varchar2(20)
);

SELECT *
FROM loguri;


CREATE OR REPLACE TRIGGER trig8
AFTER
INSERT OR DELETE OR UPDATE OF department_id
ON emp2_mcm
BEGIN
	IF inserting THEN
		INSERT INTO loguri VALUES (sysdate, USER, 'insert pe emp2');
	ELSIF updating THEN
		INSERT INTO loguri VALUES (sysdate, USER, 'update pe emp2');
	ELSIF deleting THEN
		INSERT INTO loguri VALUES (sysdate, USER, 'delete pe emp2');
	END IF;
END trig8;




maximum NUMBER OF locks acquired
maybe try increasing the NUMBER OF locks?

-- ulimit



--------------------------------

-- db local ca admin

SELECT *
FROM v$open_cursor;



SELECT USER 
FROM dual;


SELECT LINE, POSITION, TEXT
FROM USER_ERRORS
WHERE NAME =UPPER('func7');


CREATE OR REPLACE FUNCTION func7(nume_dep IN seria36.departments.department_name%type)
RETURN sys_refcursor
IS
	c sys_refcursor;
BEGIN
	OPEN c FOR
		SELECT first_name, salary, round(MONTHS_BETWEEN(sysdate, hire_date)) AS nr
		FROM seria36.EMPLOYEES e JOIN seria36.DEPARTMENTS d ON e.DEPARTMENT_ID = d.DEPARTMENT_ID
		WHERE d.DEPARTMENT_NAME = nume_dep;

	RETURN c;
END func7;


SELECT func7('Sales')
FROM dual;


DECLARE
	c sys_refcursor;
	TYPE rec_ang IS RECORD (
		fn seria36.employees.first_name%TYPE,
		sal seria36.employees.salary%TYPE,
		nr number
	);
	rec rec_ang;
BEGIN
	c := func7('Marketing');

	LOOP
		FETCH c
		INTO rec;
		EXIT WHEN c%notfound;
		dbms_output.put_line(rec.fn || ' ' || rec.sal || ' ' || rec.nr);
	END LOOP;
	

	CLOSE c;
END;


