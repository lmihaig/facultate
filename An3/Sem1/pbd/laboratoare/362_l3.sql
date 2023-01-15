-- Laborator 3 362

-------------------------------------------------------------------------------

-- begin conexiune 1 db facultate

-- L3 362 cu 363

DECLARE
     nume employees.last_name%TYPE;
BEGIN
    --DBMS_OUTPUT.PUT_LINE('mesaj');
    SELECT last_name
    INTO nume
    FROM employees e1
    WHERE e1.employee_id = (
        SELECT min(e2.employee_id)
        FROM employees e2
    );
    DBMS_OUTPUT.PUT_LINE('nume: ' || nume);
END;
/

DECLARE
     nume employees.last_name%TYPE;
BEGIN
    --DBMS_OUTPUT.PUT_LINE('mesaj');
    SELECT last_name
    INTO nume
    FROM employees e1
    WHERE e1.last_name = (
        SELECT min(e2.last_name)
        FROM employees e2
    );
    DBMS_OUTPUT.PUT_LINE('nume: ' || nume);
END;
/

DECLARE
     emp employees%ROWTYPE;
BEGIN
    --DBMS_OUTPUT.PUT_LINE('mesaj');
    SELECT *
    INTO emp
    FROM employees e1
    WHERE e1.last_name = (
        SELECT min(e2.last_name)
        FROM employees e2
    );
    DBMS_OUTPUT.PUT_LINE(
        'nume: ' || emp.last_name || ', ' ||
        'salariu: ' || emp.salary);
END;
/

SELECT * -- sau dummy
FROM dual;

/

CREATE GLOBAL TEMPORARY TABLE tbl(id int);
ROLLBACK;
DROP TABLE tbl;


/*CREATE OR REPLACE TYPE emp_tip AS OBJECT (
    nume employees.last_name%TYPE,
    sal employees.SALARY%type
);*/

CREATE TYPE tip;
DROP TYPE tip;
CREATE TYPE tip;

CREATE OR REPLACE TYPE emp_tip AS OBJECT (
    nume varchar2(25),
    sal number(8,2)
);

SELECT emp_tip('asd', 123)
FROM dual;

DECLARE
    var emp_tip;
BEGIN
    SELECT emp_tip('asd', 123)
    INTO var
    FROM dual;
END;
/

DECLARE
    emp emp_tip;
BEGIN
    SELECT last_name, salary
    INTO emp
    FROM employees e1
    WHERE e1.last_name = (
        SELECT min(e2.last_name)
        FROM employees e2
    );
    DBMS_OUTPUT.PUT_LINE(
        'nume: ' || emp.nume || ', ' ||
        'salariu: ' || emp.sal);
END;
/

DECLARE
    emp emp_tip;
BEGIN
    SELECT last_name, salary
    INTO emp.nume, emp.sal
    FROM employees e1
    WHERE e1.last_name = (
        SELECT min(e2.last_name)
        FROM employees e2
    );
    DBMS_OUTPUT.PUT_LINE(
        'nume: ' || emp.nume || ', ' ||
        'salariu: ' || emp.sal);
END;
/


DECLARE
    emp emp_tip := emp_tip('', 0);
BEGIN
    SELECT last_name, salary
    INTO emp.nume, emp.sal
    FROM employees e1
    WHERE e1.last_name = (
        SELECT min(e2.last_name)
        FROM employees e2
    );
    DBMS_OUTPUT.PUT_LINE(
        'nume: ' || emp.nume || ', ' ||
        'salariu: ' || emp.sal);
END;
/

DECLARE
    emp emp_tip;
BEGIN
    SELECT emp_tip(last_name, salary)
    INTO emp
    FROM employees e1
    WHERE e1.last_name = (
        SELECT min(e2.last_name)
        FROM employees e2
    );
    DBMS_OUTPUT.PUT_LINE(
        'nume: ' || emp.nume || ', ' ||
        'salariu: ' || emp.sal);
END;
/

SELECT 1
FROM dual
WHERE 1 = NULL;


SELECT 1
FROM dual
WHERE NULL = NULL;


SELECT 1
FROM dual
WHERE NULL != NULL;

SELECT 1
FROM dual
WHERE NULL IS NULL;


SELECT 1
FROM dual
WHERE 1 IS NULL;

SELECT 1
FROM dual
WHERE 1 != NULL;


SELECT 1
FROM dual
WHERE 1 IS NOT NULL;


DECLARE
    TYPE ang_tip IS RECORD (
        nume employees.last_name%TYPE,
        sal employees.salary%type
    );

    emp ang_tip;
BEGIN
    SELECT last_name, salary
    INTO emp
    FROM employees e1
    WHERE e1.last_name = (
        SELECT min(e2.last_name)
        FROM employees e2
    );
    DBMS_OUTPUT.PUT_LINE(
        'nume: ' || emp.nume || ', ' ||
        'salariu: ' || emp.sal);
END;
/


DECLARE
    TYPE ang_tip IS RECORD (
        ang employees%ROWTYPE,
        nume_dep departments.department_name%type
    );

    emp ang_tip;
BEGIN
    SELECT e.*, department_name
    INTO emp.ang, emp.nume_dep
    FROM employees e JOIN DEPARTMENTS d
        ON e.DEPARTMENT_ID = d.DEPARTMENT_ID
    WHERE EMPLOYEE_ID = 162;
    DBMS_OUTPUT.PUT_LINE(
        'nume: ' || emp.ang.last_name || ', ' ||
        'salariu: ' || emp.nume_dep);
END;
/



CREATE TABLE marius_temp(
    id NUMBER,
    txt varchar2(5),
    dt DATE DEFAULT sysdate
);

DROP TABLE marius_temp;

SELECT *
FROM marius_temp;

INSERT INTO marius_temp VALUES (1, 'asd', sysdate);

INSERT INTO marius_temp(id, txt) VALUES (2, 'zxc');

/

DECLARE
    TYPE tmp_tip IS RECORD (
        id marius_temp.id%TYPE,
        tx marius_temp.txt%type
    );

    tmp tmp_tip;
BEGIN
    tmp.id := 5;
    tmp.tx := 'yes';
    INSERT INTO marius_temp
    VALUES tmp;
END;
/

DECLARE
    TYPE tmp_tip IS RECORD (
        id marius_temp.id%TYPE,
        tx marius_temp.txt%type
    );

    tmp tmp_tip;
BEGIN
    tmp.id := 5;
    tmp.tx := 'yes';
    INSERT INTO marius_temp (id, txt)
    VALUES tmp;
END;
/

DECLARE
    TYPE tmp_tip IS RECORD (
        id marius_temp.id%TYPE,
        tx marius_temp.txt%type
    );

    tmp tmp_tip;
BEGIN
    tmp.id := 5;
    tmp.tx := 'yes';
    INSERT INTO marius_temp (id, txt)
    VALUES tmp.id, tmp.tx;
END;
/

DECLARE
    TYPE tmp_tip IS RECORD (
        id marius_temp.id%TYPE,
        tx marius_temp.txt%type
    );

    tmp tmp_tip;
BEGIN
    tmp.id := 5;
    tmp.tx := 'yes';
    INSERT INTO marius_temp (id, txt)
    VALUES (tmp.id, tmp.tx);
END;
/


DECLARE
    tmp marius_temp%rowtype;
BEGIN
    tmp.id := 7;
    tmp.txt := 'no';
    INSERT INTO marius_temp
    VALUES tmp;
END;
/

SELECT *
FROM marius_temp;

UPDATE marius_temp
SET dt = sysdate - 1;

UPDATE marius_temp
SET dt = sysdate - 1
WHERE id = 5;

DECLARE
    tmp marius_temp%rowtype;
BEGIN
    tmp.id := 10;
    tmp.txt := 'x';
    INSERT into marius_temp
    VALUES tmp;
END;
/


DECLARE
    tmp marius_temp%rowtype;
BEGIN
    tmp.id  := 7;
    tmp.dt  := sysdate + 5;
    tmp.txt := 'oops';
    UPDATE marius_temp
    SET ROW = tmp
    WHERE id = 7;
END;

DECLARE
    TYPE tmp_tip IS RECORD (
        id marius_temp.id%TYPE,
        tx marius_temp.txt%type
    );

    tmp tmp_tip;
BEGIN
    tmp.id := 7;
    tmp.tx := 'Yes';
    UPDATE marius_temp
    SET ROW = tmp
    WHERE id = 7;
END;
/

SELECT *
FROM marius_temp;

DECLARE
    TYPE tmp_tip IS RECORD (
        id marius_temp.id%TYPE,
        tx marius_temp.txt%type
    );

    tmp tmp_tip;
BEGIN
    UPDATE marius_temp
    SET txt = txt || '1'
    WHERE id = 10
    RETURNING id, txt
    INTO tmp;
    dbms_output.put_line(
        'id: ' || tmp.id || ', ' ||
        'txt: ' || tmp.tx
    );
END;
/

COMMIT;
ROLLBACK;

DELETE
FROM marius_temp;

DELETE
FROM marius_temp
WHERE id = 5;

SELECT *
FROM marius_temp;
/

DECLARE
    TYPE tmp_tip IS RECORD (
        id marius_temp.id%TYPE,
        tx marius_temp.txt%type
    );

    tmp tmp_tip;
BEGIN
    DELETE
    FROM marius_temp
    WHERE id = 7
    RETURNING id, txt
    INTO tmp;
    dbms_output.put_line(
        'id: ' || tmp.id || ', ' ||
        'txt: ' || tmp.tx
    );
END;

DECLARE
    TYPE tbl_tip IS TABLE OF NUMBER
        INDEX BY pls_integer; -- binary_integer
    
    tbl tbl_tip;
BEGIN
    NULL;
    tbl(201) := 3620363;
    tbl(300) := 344;
    tbl(-6) := 2;

    FOR i IN  1..tbl.count LOOP
        dbms_output.put_line('i: ' || tbl(i));
    END LOOP;
END;
/

DECLARE
    TYPE tbl_tip IS TABLE OF NUMBER
        INDEX BY pls_integer; -- binary_integer
    
    tbl tbl_tip;
    i int;
BEGIN
    NULL;
    tbl(201) := 3620363;
    tbl(300) := 344;
    tbl(-6) := 2;


    i := tbl.FIRST;
    WHILE i <= tbl.last LOOP
        dbms_output.put_line('i: ' || tbl(i));
        i := tbl.next(i);
    END LOOP;

    WHILE i IS NOT NULL LOOP
        dbms_output.put_line('i: ' || tbl(i));
        i := tbl.next(i);
    END LOOP;

    i := tbl.LAST;
    WHILE i IS NOT NULL LOOP
        dbms_output.put_line('i: ' || tbl(i));
        i := tbl.prior(i);
    END LOOP;
END;


-- end conexiune 1 db facultate

-------------------------------------------------------------------------------

-- begin conexiune 2 db facultate

-- end conexiune 2 db facultate

-------------------------------------------------------------------------------

-- begin conexiune db oracle local user normal

DECLARE
    nume employees.last_name%TYPE;
    pct employees.commission_pct%TYPE;
BEGIN
    SELECT last_name, COALESCE(COMMISSION_PCT, 0)
    INTO nume, pct
    FROM employees
    FETCH FIRST 1 ROW ONLY;

    DBMS_OUTPUT.PUT_LINE(
        'nume: ' || nume || ', ' ||
        'pct: ' || pct
    );
END;
/

---


DECLARE
    TYPE ang_tip IS RECORD (
        ang employees%ROWTYPE,
        nume_dep departments.department_name%type
    );

    emp ang_tip;
BEGIN
    SELECT e.*, department_name
    INTO emp.ang, emp.nume_dep
    FROM employees e JOIN DEPARTMENTS d
        ON e.DEPARTMENT_ID = d.DEPARTMENT_ID
    WHERE EMPLOYEE_ID = 162;
    DBMS_OUTPUT.PUT_LINE(
        'nume: ' || emp.ang.last_name || ', ' ||
        'salariu: ' || emp.nume_dep);
END;

---------------------


CREATE TABLE marius_temp(
    id NUMBER GENERATED ALWAYS AS IDENTITY(
        START WITH 1 INCREMENT BY 1
    ), txt varchar2(5), txt2 date
);

INSERT INTO MARIUS_TEMP(txt, txt2) VALUES ('asd', sysdate);

SELECT * FROM marius_temp;

DECLARE
    TYPE test_rec IS RECORD (
        txt marius_temp.txt%TYPE,
        txt2 marius_temp.txt2%type
    );
    v_test test_rec := test_rec('qwert', sysdate + 1);
BEGIN
    INSERT INTO marius_temp(txt, txt2) VALUES(v_test.txt, v_test.txt2);
END;


-- end conexiune db oracle local user normal


-------------------------------------------------------------------------------

-- begin conexiune db local mariadb user normal

-- end conexiune db local mariadb user normal

-------------------------------------------------------------------------------

-- begin conexiune db local postgres user normal

DO $$
DECLARE
    nume employees.first_name%TYPE;
BEGIN
    --DBMS_OUTPUT.PUT_LINE('comanda aia urâtă');
    SELECT first_name
    INTO nume
    FROM employees;
END $$;


----------------

CREATE TYPE tip_test AS (
    id int,
    nume varchar
);
--COMMIT;
--
DROP TYPE tip_test;
--
SELECT (1, 't')::tip_test;
--
DO $$
DECLARE
    emp1 tip_test;
    emp2 tip_test; -- := (0, 'n/a')::tip_test;
BEGIN
    SELECT employee_id, first_name
    INTO emp1
    FROM EMPLOYEES e
    WHERE EMPLOYEE_ID = 123;
    --
    SELECT employee_id, first_name
    INTO emp2.id, emp2.nume
    FROM EMPLOYEES
    WHERE EMPLOYEE_ID = 123;
    --
    RAISE NOTICE '% %', emp1.id, emp1.nume;
    RAISE NOTICE '% %', emp2.id, emp2.nume;
END $$;

-- eroare
CREATE TYPE emp_test AS (
    id employees.employee_id%TYPE,
    nume employees.first_name%TYPE
);

-- end conexiune db local postgres user normal

-------------------------------------------------------------------------------

