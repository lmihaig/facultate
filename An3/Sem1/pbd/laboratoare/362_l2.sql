-- Laborator 2 362

-------------------------------------------------------------------------------

-- begin conexiune 1 db facultate



SELECT *
FROM (
    SELECT first_name,
        last_name,
        salary,
        department_name,
        ROW_NUMBER() OVER (PARTITION BY e.DEPARTMENT_ID ORDER BY SALARY DESC) AS nr
    FROM employees e JOIN DEPARTMENTS d ON e.DEPARTMENT_ID = d.DEPARTMENT_ID 
) emp
WHERE nr <= 5;


SET serveroutput ON;
/

BEGIN
    dbms_output.put_line('hello, world!');
END;
/

DECLARE
    x int := 5;
    y int;
BEGIN
    dbms_output.put_line('x este ' || x || '.');
END;
/


DECLARE
    --prenume varchar(20);
    prenume employees.first_name%TYPE;
BEGIN
    SELECT first_name
    INTO prenume
    FROM employees;
    dbms_output.put_line('prenumele este ' || prenume || '.');
END;
/


DECLARE
    prenume employees.first_name%TYPE;
BEGIN
    SELECT first_name
    INTO prenume
    FROM employees
    WHERE EMPLOYEE_ID = 123;
    dbms_output.put_line('prenumele este ' || prenume || '.');
END;
/

DECLARE
    prenume employees.first_name%TYPE;
BEGIN
    SELECT first_name
    INTO prenume
    FROM employees
    WHERE EMPLOYEE_ID = 0;
    dbms_output.put_line('prenumele este ' || prenume || '.');
END;
/

DECLARE
    ang employees%ROWTYPE;
BEGIN
    SELECT *
    INTO ang
    FROM employees
    WHERE EMPLOYEE_ID = 123;
    dbms_output.put_line(
        'prenumele este ' || 
        ang.first_name || ', salariul este ' ||
        ang.salary
    );
END;
/

DECLARE
    ang employees%ROWTYPE;
BEGIN
    SELECT first_name, last_name
    INTO ang.last_name, ang.first_name
    FROM employees
    WHERE EMPLOYEE_ID = 123;
    dbms_output.put_line(
        'prenumele este ' || 
        ang.first_name || ', numele este ' ||
        ang.last_name
    );
END;
/

SELECT iff(TRUE, 1, 0) FROM dual;

SELECT CASE
    WHEN 1 > 2 THEN 'asd'
    WHEN 'xy' LIKE 'x%' THEN 'abc'
    ELSE 'qwerty'
    END AS rezultat
    FROM dual;

SELECT CASE 5
    WHEN 2 THEN 'asd'
    WHEN 1 THEN 'abc'
    ELSE 'qwerty'
    END AS rezultat
    FROM dual;
/

DECLARE
    ang employees%ROWTYPE;
BEGIN
    SELECT first_name, last_name
    INTO ang.last_name, ang.first_name
    FROM employees
    WHERE EMPLOYEE_ID = 123;

    CASE ang.department_id
    WHEN 2 THEN
        dbms_output.put_line('2');
    WHEN 1 THEN
        dbms_output.put_line('1');
    ELSE
        dbms_output.put_line('qwerty');
    END CASE;

    CASE
    WHEN ang.first_name LIKE '2%' THEN
        dbms_output.put_line('2');
    WHEN ang.salary < 6000 THEN
        dbms_output.put_line('sal');
    ELSE
        dbms_output.put_line('qwerty');
    END CASE;

    IF ang.department_id > 10 THEN
        dbms_output.put_line('10');
    ELSIF ang.department_id < 30 THEN
        dbms_output.put_line('30');
    ELSE
        dbms_output.put_line('altceva');
    END IF;
END;
/

BEGIN
    FOR i IN 1..10 LOOP
        CONTINUE WHEN i < 3;
        dbms_output.put_line('i este ' || i);
        -- EXIT;
        EXIT WHEN i > 6;
    END LOOP;
END;
/

BEGIN
    FOR i IN REVERSE 1..10 LOOP
        CONTINUE WHEN i > 6;
        dbms_output.put_line('i este ' || i);
        -- EXIT;
        EXIT WHEN i < 3;
    END LOOP;
END;
/
DECLARE
    i int := 0;
BEGIN
    LOOP
        i := i + 1;
        dbms_output.put_line('i este ' || i);
        EXIT WHEN i > 2;
    END LOOP;
END;
/

DECLARE
    i int := 5;
BEGIN
    WHILE i > 0 LOOP
        dbms_output.put_line('i este ' || i);
        i := i - 1;
    END LOOP;
    
END;

/
    SELECT 1
    FROM departments
    WHERE DEPARTMENT_NAME = 'asd';


-- end conexiune 1 db facultate

-------------------------------------------------------------------------------

-- begin conexiune 2 db facultate

-- end conexiune 2 db facultate

-------------------------------------------------------------------------------

-- begin conexiune db oracle local user normal

SELECT
    first_name,
    last_name,
    salary,
    department_id,
    ROW_NUMBER() OVER (
        PARTITION BY DEPARTMENT_ID
        ORDER BY salary DESC
    ) AS nr
FROM employees
FETCH first 10 ROWS only;

-- end conexiune db oracle local user normal


-------------------------------------------------------------------------------

-- begin conexiune db local mariadb user normal

-- end conexiune db local mariadb user normal

-------------------------------------------------------------------------------

-- begin conexiune db local postgres user normal

do $$
BEGIN
    CREATE TABLE tbl(id int);
end $$;
/

drop table tbl;

do $$
DECLARE
    ang employees%rowtype;
BEGIN
    SELECT first_name, salary
    INTO ang
    FROM EMPLOYEES e
    WHERE EMPLOYEE_ID = 123;
--    dbms_output.put_line(
 --       'numele este ' || ang.first_name ||
   --     ', salariul este ' || ang.salary);
end $$;
/

do $$
DECLARE
    nume employees.first_name%type = 'asd';
BEGIN
    SELECT first_name
    INTO nume
    FROM employees
    -- WHERE rownum = 1;
    WHERE EMPLOYEE_ID = 0;
    raise notice 'numele este %', nume;
end $$;

-- end conexiune db local postgres user normal

-------------------------------------------------------------------------------

