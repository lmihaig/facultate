
-- L6 362???????

----------------------------- conexiune 1

SELECT *
FROM employees;




DECLARE -- {
BEGIN
	DECLARE -- {
	BEGIN
		NULL;
	END; --    }
END; --    }


DECLARE
	fn employees.first_name%TYPE;
BEGIN
	SELECT first_name
	INTO fn
	FROM employees
	WHERE EMPLOYEE_ID = 163;
	
	dbms_output.put_line(SQL%ROWCOUNT);
END;

DECLARE
	TYPE tab IS TABLE OF employees.first_name%TYPE;
		--INDEX BY pls_integer;

	t tab;
BEGIN
	SELECT first_name
	BULK COLLECT INTO t
	FROM employees
	WHERE manager_id = 123;
	
	dbms_output.put_line(SQL%ROWCOUNT);
END;



DECLARE
	CURSOR c IS
		SELECT first_name AS fn, hire_date AS zi
		FROM employees
		WHERE manager_id = 123;

	--TYPE rec_ang IS RECORD (
	--	fn employees.first_name%TYPE,
	--	ziua employees.hire_date%TYPE
	--);
	TYPE tab IS TABLE OF c%rowtype;

	t tab;
BEGIN
	OPEN c;

	FETCH c
	BULK COLLECT INTO t;

	CLOSE c;

	FOR ang IN c LOOP
		dbms_output.put_line( ang.fn || ' ' || ang.zi);
	end LOOP;

	dbms_output.put_line('---------------------------');

	FOR i in t.FIRST .. t.LAST LOOP
		dbms_output.put_line( t(i).fn || ' ' || t(i).zi);
	END LOOP;
	
END;



DECLARE
	CURSOR c(id employees.manager_id%TYPE) IS
		SELECT first_name AS fn, hire_date AS zi
		FROM employees
		WHERE manager_id = id;

BEGIN
	dbms_output.put_line('---------------------------');
	FOR ang IN c(123) LOOP
		dbms_output.put_line( ang.fn || ' ' || ang.zi);
	END LOOP;
	dbms_output.put_line('---------------------------');
	FOR ang IN c(101) LOOP
		dbms_output.put_line( ang.fn || ' ' || ang.zi);
	END LOOP;
END;



-- pentru fiecare departament
-- top 5 angajați după hire_date 


DECLARE
	CURSOR c_dep IS
		SELECT department_name AS nume_dep,
				CURSOR(
					SELECT first_name AS fn, hire_date AS zi
					FROM employees e
					WHERE e.department_id = d.department_id
					ORDER BY hire_date
				) ang
		FROM DEPARTMENTS d;

	--TYPE tab IS TABLE OF c_dep%rowtype;
 -- Cursor Variable in record, object, or collection is NOT
 -- supported by this release
	-- TYPE refcursor IS REF CURSOR;
	
	TYPE rec_ang IS RECORD (
		fn employees.first_name%TYPE,
		ziua employees.hire_date%TYPE
	);

	-- c_ang refcursor;
	dep departments.department_name%TYPE;
	c_ang SYS_REFCURSOR;
	ang rec_ang;
BEGIN
	OPEN c_dep;
	LOOP
		FETCH c_dep
		INTO dep, c_ang;
		EXIT WHEN c_dep%notfound;
		dbms_output.put_line('departamentul ' || dep);
		LOOP
			FETCH c_ang
			INTO ang;
			EXIT WHEN c_ang%notfound OR c_ang%rowcount > 5;
			dbms_output.put_line(
				'    >>' || ang.fn || ' ' || ang.ziua
			);
		END LOOP;
	END LOOP;
	CLOSE c_dep;
END;



DECLARE
	CURSOR c_dep IS
		SELECT department_name AS nume_dep,
				CURSOR(
					SELECT first_name AS fn, hire_date AS zi
					FROM employees e
					WHERE e.department_id = d.department_id
					ORDER BY hire_date
				) AS ang_info
		FROM DEPARTMENTS d;

	TYPE rec_ang IS RECORD (
		fn employees.first_name%TYPE,
		ziua employees.hire_date%TYPE
	);
	ang rec_ang;
BEGIN
	FOR dep_info IN c_dep LOOP
		dbms_output.put_line('departamentul ' || dep_info.nume_dep);
		IF dep_info.ang_info%isopen THEN
			dbms_output.put_line('cursorul este deschis');
		ELSE
			dbms_output.put_line('cursorul este inchis');
		END IF;
		LOOP
			FETCH dep_info.ang_info
			INTO ang;
			EXIT WHEN dep_info.ang_info%notfound OR dep_info.ang_info%rowcount > 5;
			dbms_output.put_line(
				'    >>' || ang.fn || ' ' || ang.ziua
			);
		END LOOP;
	END LOOP;
END;



DECLARE
	c_ref SYS_REFCURSOR;
	fn employees.first_name%TYPE;
	zi employees.hire_date%TYPE;
	query varchar2(30) := 'Qbc';
BEGIN
	OPEN c_ref FOR
		'select hire_date, first_name ' ||
		'from employees ' ||
		'where first_name > :query'
		USING query;
	-- prepared statements
	LOOP
		FETCH c_ref
		INTO zi, fn;
		EXIT WHEN c_ref%notfound;
		dbms_output.put_line(zi || ' ' || fn);
	END LOOP;
	
	CLOSE c_ref;
END;





DECLARE
	c_ref SYS_REFCURSOR;
	fn employees.first_name%TYPE;
	zi employees.hire_date%TYPE;
	query varchar2(30) := '''Qbc'' OR 1=1';
BEGIN
	OPEN c_ref FOR
		'select hire_date, first_name ' ||
		'from employees ' ||
		'where first_name > ' || query;
	LOOP
		FETCH c_ref
		INTO zi, fn;
		EXIT WHEN c_ref%notfound;
		dbms_output.put_line(zi || ' ' || fn);
	END LOOP;
	
	CLOSE c_ref;
END;


SELECT *
FROM EMPLOYEES
WHERE DEPARTMENT_ID = 30
FOR UPDATE NOWAIT;

ROLLBACK;


LOCK TABLE employees IN share MODE NOWAIT;

LOCK TABLE employees IN exclusive MODE NOWAIT;







DECLARE
	PROCEDURE p1
	IS
	BEGIN
		dbms_output.put_line('p1');
	END;
BEGIN
	p1;
END;


DECLARE
	PROCEDURE p1
	IS
	BEGIN
		dbms_output.put_line('p1');
	END p1;

	x NUMBER;
BEGIN
	p1();
END;


CREATE OR REPLACE PROCEDURE proc1
IS
BEGIN
	dbms_output.put_line('proc1 stocata');
END proc1;


BEGIN
	proc1;
END;



CREATE OR REPLACE PROCEDURE proc2(id employees.MANAGER_ID%TYPE)
IS
    TYPE tab IS TABLE OF employees.first_name%TYPE INDEX BY pls_integer;
	t tab;
BEGIN
	SELECT first_name
	BULK COLLECT INTO t
	FROM employees
	WHERE manager_id = id;
	dbms_output.put_line(SQL%ROWCOUNT);
END proc2;


BEGIN
	proc2(123);
	proc2(101);
END;



CREATE OR REPLACE FUNCTION func2(id employees.MANAGER_ID%TYPE)
RETURN NUMBER
IS
    TYPE tab IS TABLE OF employees.first_name%TYPE INDEX BY pls_integer;
	t tab;
BEGIN
	SELECT first_name
	BULK COLLECT INTO t
	FROM employees
	WHERE manager_id = id;

	RETURN SQL%ROWCOUNT;
END func2;


BEGIN
	dbms_output.put_line(func2(123));
	dbms_output.put_line(func2(101));
END;


SELECT func2(123)
FROM dual;


----------------------------- conexiune 2



SELECT *
FROM EMPLOYEES
WHERE DEPARTMENT_ID = 30
FOR UPDATE nowait;

ROLLBACK;


LOCK TABLE employees IN share MODE NOWAIT;

LOCK TABLE employees IN exclusive MODE NOWAIT;



SELECT *
FROM EMPLOYEES
WHERE DEPARTMENT_ID = 30;
