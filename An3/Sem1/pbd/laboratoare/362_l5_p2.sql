-- L5 362??

DECLARE
  CURSOR c IS
    SELECT *
    FROM test_date;
  TYPE tab IS TABLE OF c%rowtype;
  t tab;
  nr NUMBER := 0;
  
  medie NUMBER := 0;
BEGIN
    OPEN c;

    LOOP
        FETCH c
        BULK COLLECT INTO t LIMIT 1e6;
        dbms_output.put_line('nr: ' || nr || ', rowcount: ' || c%rowcount);
        --EXIT WHEN c%notfound;
        EXIT WHEN c%rowcount = nr;
        nr := nr + t.count;

        FOR i IN t.FIRST..t.LAST LOOP
            medie := medie + (sysdate - t(i).timp);
        end LOOP;
        medie := medie / t.count;
        dbms_output.put_line('medie: ' || medie);
        
    END LOOP;

    CLOSE c;

END;

SELECT *
FROM test_date;
SELECT count(*)
FROM test_date;

