-- L7 362

DECLARE
	emp employees%rowtype;
BEGIN
	SELECT *
	INTO emp
	FROM employees
	WHERE employee_id = 162;

	dbms_output.put_line('nr: ' || SQL%ROWCOUNT);
END;


DECLARE
	TYPE tab_ang IS TABLE OF employees%rowtype;
	emp tab_ang;
BEGIN
	SELECT *
	BULK COLLECT INTO emp
	FROM employees
    WHERE MOD(employee_id, 62) = 1;

	dbms_output.put_line('nr: ' || SQL%ROWCOUNT);
END;


DECLARE
	CURSOR c(nr number) IS
		SELECT *
		FROM employees
	    WHERE MOD(employee_id, nr) = 1;
BEGIN
	FOR ang IN c(62) LOOP
		dbms_output.put_line(ang.employee_id || ' ' || ang.salary);
	END LOOP;
	dbms_output.put_line('----------------------');
	FOR ang IN c(26) LOOP
		dbms_output.put_line(ang.employee_id || ' ' || ang.salary);
	END LOOP;
END;



CREATE OR REPLACE PROCEDURE proc3
IS
BEGIN
	dbms_output.put_line('proc 3 stocata');
END proc3;

BEGIN
	proc3;
END;


CREATE OR REPLACE FUNCTION func3
RETURN NUMBER
IS
BEGIN
	dbms_output.put_line('func 3 stocata');
	RETURN 5;
END func3;

DECLARE
	nr NUMBER;
BEGIN
	nr := func3;
	dbms_output.put_line('functia a intors ' || nr);
END;



CREATE OR REPLACE FUNCTION func4(x number)
RETURN NUMBER
IS
BEGIN
	dbms_output.put_line('func 4 stocata');
	IF x MOD 3 = 0 THEN
		RETURN 5;
	END IF;
END func4;


SELECT func4(3)
FROM dual;

SELECT func4(4)
FROM dual;



CREATE OR REPLACE FUNCTION func5(x number)
RETURN NUMBER
IS
BEGIN
	dbms_output.put_line('func 5 stocata');
	IF x MOD 3 = 1 THEN
		RETURN 5;
	END IF;
	RETURN 3;
END func5;


SELECT LINE, POSITION, TEXT
FROM USER_ERRORS
WHERE NAME =UPPER('func6');


CREATE OR REPLACE FUNCTION func6(x number)
RETURN NUMBER
IS
BEGIN
	RETURN func5(x) + 100;
END func6;

SELECT func6(20)
FROM dual;


ALTER FUNCTION func6 compile;


CREATE OR REPLACE PROCEDURE proc4( 
	x IN NUMBER, y OUT NUMBER, z IN OUT number)
IS
BEGIN
	dbms_output.put_line('x este ' || x);
	dbms_output.put_line('y este ' || y);
	dbms_output.put_line('z este ' || z);
	y := x + 1 + z;
	z := z - 2;
END;

DECLARE
    n1 NUMBER := 1;
    n2 NUMBER := 2;
BEGIN
	proc4(3, n1, n2);

	dbms_output.put_line('n1 este ' || n1);
	dbms_output.put_line('n2 este ' || n2);
END;


SELECT *
FROM JOB_HISTORY jh
ORDER BY employee_id;

UPDATE JOB_HISTORY
SET job_id = 'SA_REP'
WHERE EMPLOYEE_ID = 176 AND JOB_ID = 'SA_MAN';


UPDATE JOB_HISTORY
SET job_id = 'SA_MAN'
WHERE EMPLOYEE_ID = 176 AND to_char(START_DATE, 'yyyy-mm-dd') = '1999-01-01';

ROLLBACK;
COMMIT;


CREATE OR REPLACE FUNCTION func6(oras locations.city%type)
RETURN number
IS
	nr NUMBER;
BEGIN
	SELECT count(*)
	INTO nr
	FROM (
		SELECT employee_id, count(DISTINCT job_id)
		FROM job_history jh
			JOIN departments d ON jh.DEPARTMENT_ID = d.DEPARTMENT_ID
			JOIN locations   l ON d.LOCATION_ID    = l.LOCATION_ID
		WHERE l.CITY = oras
		GROUP BY EMPLOYEE_ID
		HAVING count(DISTINCT job_id) >= 2
	);
	RETURN nr;
END func6;

SELECT func6('Oxford')
FROM dual;

SELECT func6('London')
FROM dual;

DECLARE
	oras locations.city%TYPE := 'Oxford';
BEGIN
	dbms_output.put_line(func6(oras));
END;




SELECT count(*)
	FROM (
		SELECT employee_id, count(DISTINCT job_id) AS nr
		FROM job_history jh
			JOIN departments d ON jh.DEPARTMENT_ID = d.DEPARTMENT_ID
			JOIN locations   l ON d.LOCATION_ID    = l.LOCATION_ID
		WHERE l.CITY = 'Oxford'
		GROUP BY EMPLOYEE_ID
		HAVING count(DISTINCT job_id) >= 2
	);



SELECT *
FROM MARIUS_TEMP mt ;

UPDATE MARIUS_TEMP
SET dt = dt - 1
WHERE id > 5;

ROLLBACK;

CREATE OR REPLACE TRIGGER trig1
BEFORE
	INSERT OR UPDATE OF dt
ON marius_temp
BEGIN
	dbms_output.put_line('trig1 before statement');
END trig1;

CREATE OR REPLACE TRIGGER trig2
AFTER
	INSERT OR UPDATE OF dt
ON marius_temp
BEGIN
	dbms_output.put_line('trig2 after statement');
END trig2;


CREATE OR REPLACE TRIGGER trig3
BEFORE
	INSERT OR UPDATE OF dt
ON marius_temp
FOR EACH ROW
WHEN (OLD.dt < NEW.dt)
BEGIN
	dbms_output.put_line(
		'trig3 before row: ' || :OLD.dt || ' ' || :NEW.dt);
END trig3;

CREATE OR REPLACE TRIGGER trig4
AFTER
	INSERT OR UPDATE OF dt
ON marius_temp
FOR EACH ROW
BEGIN
	IF :OLD.dt < :NEW.dt THEN
		dbms_output.put_line(
			'trig4 after row: ' || :OLD.dt || ' ' || :NEW.dt
		);
	END if;
END trig4;

ALTER TRIGGER trig5 disable;
ALTER TRIGGER trig1 enable;



CREATE OR REPLACE TRIGGER trig5
BEFORE
	INSERT OR UPDATE OF dt
ON marius_temp
BEGIN
	dbms_output.put_line('trig5 before statement');
    raise_application_error(-20001, '5 lei');
END trig5;
