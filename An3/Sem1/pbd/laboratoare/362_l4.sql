-- Laborator 4 362

-------------------------------------------------------------------------------

-- begin conexiune 1 db facultate

-- L4 362 cu 363

--struct ang {
--    int sal;
--    string nume;
--};



DECLARE
    TYPE date_ang IS RECORD (
        nume employees.first_name%TYPE,
        sal employees.salary%type
    );
    ang date_ang;
BEGIN
    SELECT first_name, salary
    INTO ang
    FROM employees
    WHERE employee_id = 162;

    dbms_output.put_line(
        'nume: ' || ang.nume || ', ' ||
        'salariu: ' || ang.sal
        
    );
END;
/

DECLARE
    TYPE date_ang IS RECORD (
        nume employees.first_name%TYPE,
        sal employees.salary%type
    );
    
    TYPE tab_ang_idx IS TABLE OF date_ang
        INDEX BY binary_integer; -- sau pls_integer
    
    tab tab_ang_idx;
BEGIN
    SELECT first_name, salary
    INTO tab
    FROM employees
    WHERE employee_id = 162;

    dbms_output.put_line(
        'nume: ' || ang.nume || ', ' ||
        'salariu: ' || ang.sal
        
    );
END;
/


DECLARE
    TYPE date_ang IS RECORD (
        nume employees.first_name%TYPE,
        sal employees.salary%type
    );
    
    TYPE tab_ang_idx IS TABLE OF date_ang
        INDEX BY binary_integer; -- sau pls_integer
    
    tab tab_ang_idx;
BEGIN
    SELECT first_name, salary
    INTO tab.first_name
    FROM employees
    WHERE employee_id = 162;

    dbms_output.put_line(
        'nume: ' || ang.nume || ', ' ||
        'salariu: ' || ang.sal
        
    );
END;
/

DECLARE
    TYPE date_ang IS RECORD (
        nume employees.first_name%TYPE,
        sal employees.salary%type
    );
    
    TYPE tab_ang_idx IS TABLE OF date_ang
        INDEX BY binary_integer; -- sau pls_integer
    
    tab tab_ang_idx;
BEGIN
    SELECT first_name, salary
    INTO tab(362).nume, tab(362).sal
    FROM employees
    WHERE employee_id = 162;

    dbms_output.put_line(
        'nume: ' || tab(362).nume || ', ' ||
        'salariu: ' || tab(362).sal
        
    );
END;
/

DECLARE
    TYPE date_ang IS RECORD (
        nume employees.first_name%TYPE,
        sal employees.salary%type
    );
    
    TYPE tab_ang_idx IS TABLE OF date_ang
        INDEX BY binary_integer; -- sau pls_integer
    
    tab tab_ang_idx;
BEGIN
    SELECT first_name, salary
    INTO tab(363)
    FROM employees
    WHERE employee_id = 163;

    dbms_output.put_line(
        'nume: ' || tab(363).nume || ', ' ||
        'salariu: ' || tab(363).sal
        
    );
END;
/

DECLARE
    TYPE date_ang IS RECORD (
        nume employees.first_name%TYPE,
        sal employees.salary%type
    );
    
    TYPE tab_ang_idx IS TABLE OF date_ang
        INDEX BY binary_integer; -- sau pls_integer
    
    tab tab_ang_idx;
BEGIN
    SELECT first_name, salary
    INTO tab
    FROM employees;

    dbms_output.put_line(
        'nume: ' || tab(362).nume || ', ' ||
        'salariu: ' || tab(362).sal
        
    );
END;
/


DECLARE
    TYPE date_ang IS RECORD (
        nume employees.first_name%TYPE,
        sal employees.salary%type
    );
    
    TYPE tab_ang_idx IS TABLE OF date_ang
        INDEX BY binary_integer; -- sau pls_integer
    
    tab tab_ang_idx;
BEGIN
    SELECT first_name, salary
    BULK COLLECT INTO tab
    FROM employees;
    
    FOR i IN tab.FIRST..tab.LAST LOOP
        dbms_output.put_line(
            'i: ' || i || ', ' ||
            'nume: ' || tab(i).nume || ', ' ||
            'salariu: ' || tab(i).sal
            
        );
        --i := tab.next(i);
    END LOOP;


    FOR i IN REVERSE tab.FIRST..tab.LAST LOOP
        dbms_output.put_line(
            'i: ' || i || ', ' ||
            'nume: ' || tab(i).nume || ', ' ||
            'salariu: ' || tab(i).sal
            
        );
        --i := tab.next(i);
    END LOOP;

    dbms_output.put_line(
        'count: ' || tab.count || ' ' ||
        'limit:' || tab.limit
    );
END;
/


DECLARE
    TYPE tab_nr IS TABLE OF NUMBER
        INDEX BY pls_integer;

    v tab_nr;
    i NUMBER;
BEGIN
    dbms_output.put_line(
        'count: ' || v.count
    );
    v(3) := 2;
    v(6) := 0;
    v(2) := 1;
    v(-55) := 11;
    v(-50) := 12;
    v(-155) := 10;

    i := v.FIRST;
    WHILE i IS NOT NULL LOOP
        --i := v.next(i);
        DBMS_OUTPUT.PUT_LINE(
            'i: ' || i || ', ' ||
            'v(i): ' || v(i)
        );
        i := v.next(i);
    END LOOP;
    dbms_output.put_line(
        'count: ' || v.count
    );
    dbms_output.put_line('------------------');

    i := v.LAST;
    WHILE i IS NOT NULL LOOP
        --i := v.next(i);
        DBMS_OUTPUT.PUT_LINE(
            'i: ' || i || ', ' ||
            'v(i): ' || v(i)
        );
        i := v.prior(i);
    END LOOP;
    dbms_output.put_line('------------------');
    v.delete(-55);
    i := v.FIRST;
    WHILE i IS NOT NULL LOOP
        --i := v.next(i);
        DBMS_OUTPUT.PUT_LINE(
            'i: ' || i || ', ' ||
            'v(i): ' || v(i)
        );
        i := v.next(i);
    END LOOP;
    dbms_output.put_line(
        'count: ' || v.count
    );
    dbms_output.put_line('------------------');
    v.delete(-5, 4);
    i := v.FIRST;
    WHILE i IS NOT NULL LOOP
        --i := v.next(i);
        DBMS_OUTPUT.PUT_LINE(
            'i: ' || i || ', ' ||
            'v(i): ' || v(i)
        );
        i := v.next(i);
    END LOOP;
    dbms_output.put_line(
        'count: ' || v.count
    );
    dbms_output.put_line('------------------');
    IF NOT v.exists(-55) THEN
        --dbms_output.put_line('nu s-a sters');
        dbms_output.put_line('s-a sters');
    ELSE
        dbms_output.put_line('ok');
    END IF;
END;


-- tablourile indexate pot fi folosite numai în PL/SQL

-- tablouri imbricate merg și în SQL

CREATE OR REPLACE TYPE tab_numere IS TABLE OF NUMBER;

SELECT tab_numere(1, 2, 3)
FROM dual;

CREATE TABLE tbl_imb (
    id NUMBER,
    tbl tab_numere
)
NESTED TABLE tbl STORE AS tbl_store;


-- tablouri imbricate
DECLARE
    TYPE tab_nr IS TABLE OF NUMBER;

    v tab_nr;
    i NUMBER;
BEGIN
    dbms_output.put_line(
        'count: ' || v.count
    );
END;

DECLARE
    TYPE tab_nr IS TABLE OF NUMBER;

    v tab_nr := tab_nr();
    i NUMBER;
BEGIN
    dbms_output.put_line(
        'count: ' || v.count
    );
END;


DECLARE
    TYPE tab_nr IS TABLE OF NUMBER;

    v tab_nr := tab_nr(3, 6, 2, 3, 6, 3);
BEGIN
    dbms_output.put_line(
        'count: ' || v.count || ' ' ||
        'limit: ' || v.limit
    );
    FOR i IN reverse v.FIRST..v.LAST LOOP
        DBMS_OUTPUT.PUT_LINE(
            'i: ' || i || ', ' ||
            'v(i): ' || v(i)
        );
    END LOOP;
    dbms_output.put_line('------------------');
    v(10) := 60;
END;
/


DECLARE
    TYPE tab_nr IS TABLE OF NUMBER;

    v tab_nr := tab_nr(3, 6, 2, 3, 6, 3);

    j NUMBER;
BEGIN
    dbms_output.put_line(
        'count: ' || v.count || ' ' ||
        'limit: ' || v.limit
    );
    FOR i IN reverse v.FIRST..v.LAST LOOP
        DBMS_OUTPUT.PUT_LINE(
            'i: ' || i || ', ' ||
            'v(i): ' || v(i)
        );
    END LOOP;
    dbms_output.put_line('------------------');
    v.extend; -- extinde cu un ELEMENT cu valoare NULL
    
    dbms_output.put_line(
        'count: ' || v.count || ' ' ||
        'limit: ' || v.limit
    );
    FOR i IN v.FIRST..v.LAST LOOP
        DBMS_OUTPUT.PUT_LINE(
            'i: ' || i || ', ' ||
            'v(i): ' || v(i)
        );
    END LOOP;
    dbms_output.put_line('------------------');
    v.extend(3); -- extinde cu 3 elemente NULL
    
    dbms_output.put_line(
        'count: ' || v.count || ' ' ||
        'limit: ' || v.limit
    );
    FOR i IN v.FIRST..v.LAST LOOP
        DBMS_OUTPUT.PUT_LINE(
            'i: ' || i || ', ' ||
            'v(i): ' || v(i)
        );
    END LOOP;
    dbms_output.put_line('------------------');
    v(10) := 60;

    dbms_output.put_line(
        'count: ' || v.count || ' ' ||
        'limit: ' || v.limit
    );
    FOR i IN v.FIRST..v.LAST LOOP
        DBMS_OUTPUT.PUT_LINE(
            'i: ' || i || ', ' ||
            'v(i): ' || v(i)
        );
    END LOOP;
    dbms_output.put_line('------------------');

    v.extend(4, 10); -- extinde cu 4 elemente
    -- cu valoarea elementului de pe poziția 10
    dbms_output.put_line(
        'count: ' || v.count || ' ' ||
        'limit: ' || v.limit
    );
    FOR i IN v.FIRST..v.LAST LOOP
        DBMS_OUTPUT.PUT_LINE(
            'i: ' || i || ', ' ||
            'v(i): ' || v(i)
        );
    END LOOP;
    dbms_output.put_line('------------------');
    v.trim;

    dbms_output.put_line(
        'count: ' || v.count || ' ' ||
        'limit: ' || v.limit
    );
    FOR i IN v.FIRST..v.LAST LOOP
        DBMS_OUTPUT.PUT_LINE(
            'i: ' || i || ', ' ||
            'v(i): ' || v(i)
        );
    END LOOP;
    dbms_output.put_line('------------------');
    v.trim(3);

    dbms_output.put_line(
        'count: ' || v.count || ' ' ||
        'limit: ' || v.limit
    );
    FOR i IN v.FIRST..v.LAST LOOP
        DBMS_OUTPUT.PUT_LINE(
            'i: ' || i || ', ' ||
            'v(i): ' || v(i)
        );
    END LOOP;
    dbms_output.put_line('------------------');
    --v.delete(7, 9);
    v.delete(4, 5);

    dbms_output.put_line(
        'count: ' || v.count || ' ' ||
        'limit: ' || v.limit
    );
    --FOR i IN v.FIRST..v.LAST LOOP
    --    DBMS_OUTPUT.PUT_LINE(
    --        'i: ' || i || ', ' ||
    --        'v(i): ' || v(i)
    --    );
    --END LOOP;

    FOR i IN v.FIRST..v.LAST LOOP
        --IF v(i) IS NOT NULL THEN
        --IF v.exists(i) IS NOT NULL THEN
        IF v.exists(i) THEN
            DBMS_OUTPUT.PUT_LINE(
                'i: ' || i || ', ' ||
                'v(i): ' || v(i)
            );
        END IF;
    END LOOP;
    dbms_output.put_line('------------------');

    j := v.FIRST;
    WHILE j IS NOT NULL LOOP
        DBMS_OUTPUT.PUT_LINE(
            'j: ' || j || ', ' ||
            'v(j): ' || v(j)
        );
        j := v.next(j);
    END LOOP;
    v.delete(8);
    v(5) := 88;
    dbms_output.put_line('------------------');

    j := v.FIRST;
    WHILE j IS NOT NULL LOOP
        DBMS_OUTPUT.PUT_LINE(
            'j: ' || j || ', ' ||
            'v(j): ' || v(j)
        );
        j := v.next(j);
    END LOOP;
END;
/

-- varray

-- varrays pot fi folosiți în SQL

CREATE OR REPLACE TYPE vec_numere
    IS varray(5) OF NUMBER;

SELECT vec_numere(4, 5, 6)
FROM dual;

DECLARE
    TYPE vec_nr IS varray(10) OF NUMBER;

    v vec_nr;
BEGIN
    dbms_output.put_line(
        'count: ' || v.count || ' ' ||
        'limit: ' || v.limit
    );
END;


DECLARE
    TYPE vec_nr IS varray(10) OF NUMBER;

    v vec_nr := vec_nr();
BEGIN
    dbms_output.put_line(
        'count: ' || v.count || ' ' ||
        'limit: ' || v.limit
    );
END;


DECLARE
    TYPE vec_nr IS varray(10) OF NUMBER;

    v vec_nr := vec_nr(1, 5, 1, 8);
BEGIN
    dbms_output.put_line(
        'count: ' || v.count || ' ' ||
        'limit: ' || v.limit
    );
END;


DECLARE
    TYPE vec_nr IS varray(10) OF NUMBER;

    v vec_nr := vec_nr(1, 5, 1, 8);
BEGIN
    dbms_output.put_line(
        'count: ' || v.count || ' ' ||
        'limit: ' || v.limit
    );
    v(8) := 7;
END;
/



DECLARE
    TYPE vec_nr IS varray(10) OF NUMBER;

    v vec_nr := vec_nr(1, 5, 1, 8);
BEGIN
    dbms_output.put_line(
        'count: ' || v.count || ' ' ||
        'limit: ' || v.limit
    );
    v.extend(4);
    v(8) := 7;

    FOR i IN v.FIRST..v.LAST LOOP
        DBMS_OUTPUT.PUT_LINE(
            'i: ' || i || ', ' ||
            'v(i): ' || v(i)
        );
    END LOOP;
    --v.extend(3);
    v.trim(2);
    dbms_output.put_line('------------------');
    FOR i IN v.FIRST..v.LAST LOOP
        DBMS_OUTPUT.PUT_LINE(
            'i: ' || i || ', ' ||
            'v(i): ' || v(i)
        );
    END LOOP;
END;
/

-- end conexiune 1 db facultate

-------------------------------------------------------------------------------

-- begin conexiune 2 db facultate

-- end conexiune 2 db facultate

-------------------------------------------------------------------------------

-- begin conexiune db oracle local user normal

-- L4 362 + 363

DECLARE
    TYPE tab_idx IS TABLE OF test_date%rowtype;

    tab tab_idx;
BEGIN
    SELECT *
    BULK COLLECT INTO tab
    FROM test_date;
    dbms_output.put_line(
        'count :' || tab.count
    );
END;


DECLARE
    TYPE tab_idx IS TABLE OF test_date%rowtype;

    tab tab_idx;
BEGIN
    SELECT *
    BULK COLLECT INTO tab
    FROM test_date
    FETCH FIRST 1e6 ROWS ONLY;
    --FETCH FIRST 50 ROWS ONLY;
    dbms_output.put_line(
        'count :' || tab.count
    );
END;

SELECT *
FROM test_date;


SELECT *
FROM test_date
FETCH FIRST 5 ROWS ONLY;

-- fără index ~1.5s
-- cu index ~1-6 ms
SELECT *
FROM test_date
ORDER BY id
FETCH FIRST 5 ROWS ONLY;


SELECT *
FROM test_date
ORDER BY id
OFFSET 5 ROWS 
FETCH NEXT 5 ROWS ONLY;

-- ~2-2.5s
SELECT *
FROM test_date
ORDER BY id
OFFSET 5e6 ROWS 
FETCH NEXT 5 ROWS ONLY;

-- ~4-5s
SELECT *
FROM test_date
ORDER BY id
OFFSET 1e7 ROWS 
FETCH NEXT 5 ROWS ONLY;

-- fără index: ~13s
SELECT *
FROM test_date
ORDER BY timp
OFFSET 1e7 ROWS 
FETCH NEXT 5 ROWS ONLY;


-- ~12ms
SELECT *
FROM test_date
WHERE id > 1e7
ORDER BY id
FETCH NEXT 5 ROWS ONLY;



-- setup tabela de test

CREATE TABLE test_date (
    id NUMBER GENERATED ALWAYS AS IDENTITY(
        START WITH 1 INCREMENT BY 1
    ),
    text varchar2(10),
    timp date
);

DROP TABLE test_date;

CREATE INDEX test_date_id_idx ON test_date(id);

DROP INDEX test_date_id_idx;

SELECT *
FROM test_date
WHERE id > 0e6
ORDER BY id
FETCH FIRST 5 ROWS ONLY;

-- ctrl+shift+e pt explain plan
SELECT *
FROM test_date
ORDER BY id
offset 1e6 ROWS FETCH FIRST 5 ROWS ONLY;

SELECT COUNT(*)
FROM test_date;

-- ~15-20s/1e6
-- generarea în sine ia f puțin
DECLARE
    TYPE tip IS TABLE OF DATE INDEX BY PLS_INTEGER;
    v tip;

    t1 NUMBER;
    t2 NUMBER;
    dt DATE := sysdate;
    --nr NUMBER := 2e6;
    --nr NUMBER := 1e5;
    nr NUMBER := 2e5;
BEGIN
    t1 := DBMS_UTILITY.GET_TIME;
    FOR i IN 1..nr LOOP
        v(i) := dt;
    END LOOP;

    t2 := DBMS_UTILITY.GET_TIME;
    DBMS_OUTPUT.PUT_LINE(
        'generare: ' ||
        (t2 - t1) / 100 || ' s'
    );
    t1 := DBMS_UTILITY.GET_TIME;
    FORALL i IN v.first..v.last
        INSERT INTO test_date(text, timp)
        VALUES(
            --'bbbbbbbbbb',
            --'cc',
            --'ddd',
            --'eheh',
            --'haha',
            --'hihi',
            'mai repede',
            v(i)
        );
    t2 := DBMS_UTILITY.GET_TIME;
    DBMS_OUTPUT.PUT_LINE(
        'inserare: ' ||
        (t2 - t1) / 100 || ' s'
    );
END;

-- ~90-100s/1e6
DECLARE
    t1 NUMBER;
    t2 NUMBER;
    dt DATE := sysdate;
BEGIN
    t1 := DBMS_UTILITY.GET_TIME;
    FOR i IN 1..2e5 LOOP
        --INSERT INTO test_date(text, timp)
        --VALUES(
        --    DBMS_RANDOM.STRING('a', 10),
        --    SYSDATE + i/100000
        --);
        --INSERT INTO test_date(text, timp)
        --VALUES(
        --    'aaaaaaaaaa',
        --    SYSDATE + i/100000
        --);
        INSERT INTO test_date(text, timp)
        VALUES(
            --'aaaaaaaaaa',
            --'ups...',
            'vrem acasa',
            dt
        );
    END LOOP;
    t2 := DBMS_UTILITY.GET_TIME;
    DBMS_OUTPUT.PUT_LINE((t2 - t1) / 100 || ' s');
END;



-- end conexiune db oracle local user normal


-------------------------------------------------------------------------------

-- begin conexiune db local mariadb user normal

-- end conexiune db local mariadb user normal

-------------------------------------------------------------------------------

-- begin conexiune db local postgres user normal


-- end conexiune db local postgres user normal

-------------------------------------------------------------------------------

