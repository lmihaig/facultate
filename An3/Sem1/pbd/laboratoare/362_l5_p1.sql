DECLARE
  CURSOR c(filtru varchar2) IS
  	SELECT FIRST_name AS nume, phone_number AS tel
  	FROM employees
    WHERE phone_NUMBER LIKE filtru;
BEGIN
	FOR ang IN c('%4') LOOP
		dbms_output.put_line(ang.nume || ' ' || ang.tel);	
	end LOOP;
	
	dbms_output.put_line('------------------');
	
	FOR ang IN c('5%') LOOP
		dbms_output.put_line(ang.nume || ' ' || ang.tel);	
	end LOOP;
	dbms_output.put_line('------------------');
	
	FOR ang IN c('%5') LOOP
		dbms_output.put_line(ang.nume || ' ' || ang.tel);	
	end LOOP;

	FOR ang IN c('%5; drop table emp2_mcm;-- ') LOOP
		dbms_output.put_line(ang.nume || ' ' || ang.tel);	
	end LOOP;

	
END;


DECLARE
  c sys_refcursor;
  filtru varchar2(40) := '''%5''; drop table emp2_mcm;--';
BEGIN
	OPEN c FOR
	'SELECT FIRST_name AS nume, phone_number AS tel ' ||
  	'FROM employees ' ||
    'WHERE phone_NUMBER LIKE ' || filtru;
END;






SELECT * FROM emp2_mcm;


DECLARE
  CURSOR c is
    SELECT *
    FROM employees;
  TYPE tab IS TABLE OF c%rowtype;

  t tab;
BEGIN
	OPEN c;
	FETCH c
	BULK COLLECT INTO t;
    CLOSE c;
   
    FOR i IN t.FIRST..t.LAST LOOP
    	dbms_output.put_line(i || ' ' || t(i).first_name);
    end LOOP;
   
    
END;


