SELECT AVG(SALARY)  FROM EMPLOYEES e 
WHERE  LENGTH(e.LAST_NAME) > 4
	AND EXTRACT(MONTH FROM e.HIRE_DATE) = 1
	AND e.DEPARTMENT_ID != (SELECT DEPARTMENT_ID  
							FROM EMPLOYEES e2 
							WHERE SALARY = (SELECT MIN(SUM(e.SALARY)) FROM EMPLOYEES e GROUP BY e.DEPARTMENT_ID))
GROUP BY DEPARTMENT_ID;



--SELECT to_date(round(avg(to_number(to_char(HIRE_DATE , 'J')))),'J') FROM EMPLOYEES e
--GROUP BY DEPARTMENT_ID ;
--
--SELECT MEDIAN(HIRE_DATE)  FROM EMPLOYEES e
--GROUP BY DEPARTMENT_ID ;
--
--
--SELECT to_char(sysdate, 'J') FROM DUAL;
--


DECLARE
  TYPE tabel IS RECORD (
    department_id employees.department_id%TYPE,
    salary_sum NUMBER,
    count_employee NUMBER
  );
  TYPE location_salary_sum_t IS TABLE OF tabel;
  location_salary_sums location_salary_sum_t;
  min_salary NUMBER := 9999999;
  avg_salary NUMBER;
  location NUMBER;
BEGIN
  SELECT department_id, SUM(salary) AS salary_sum, COUNT(*) as count_employee
  BULK COLLECT INTO location_salary_sums
  FROM employees
  WHERE length(last_name) >= 5 AND EXTRACT(MONTH FROM hire_date) = 1 and department_id <= 110
  GROUP BY department_id;
  --SELECT MIN(salary_sum) INTO min_salary FROM location_salary_sums;
  FOR i IN location_salary_sums.FIRST .. location_salary_sums.LAST LOOP
    IF location_salary_sums(i).salary_sum < min_salary THEN
        min_salary := location_salary_sums(i).salary_sum;
    END IF;
  END loop;
  dbms_output.put_line('The minimum value is: ' || min_salary);
  FOR i IN location_salary_sums.FIRST .. location_salary_sums.LAST LOOP
    location := location_salary_sums(i).department_id;
    avg_salary := location_salary_sums(i).salary_sum / location_salary_sums(i).count_employee;
    IF location_salary_sums(i).salary_sum > min_salary THEN
      DBMS_OUTPUT.PUT_LINE('Department: ' || location || ', Average salary: ' || avg_salary);
    END IF;
  END LOOP;
END;
/

--newest
DECLARE
    CURSOR c_avg_salary IS 
        SELECT department_id, AVG(salary) avg_salary, SUM(salary) sal
        FROM employees
        WHERE length(last_name) >= 5 AND TO_CHAR(hire_date, 'MON') = 'IAN' and department_id <= 110
        GROUP BY department_id;

    l_location employees.department_id%TYPE;
    l_avg_salary employees.salary%TYPE;
    l_min_location_salary employees.salary%TYPE;
BEGIN
    SELECT MIN(location_total) INTO l_min_location_salary
    FROM (SELECT department_id, SUM(salary) location_total
        FROM employees
        WHERE length(last_name) >= 5 AND TO_CHAR(hire_date, 'MON') = 'IAN' and department_id <= 110
        GROUP BY department_id);
    FOR c_record IN c_avg_salary
    LOOP
        dbms_output.put_line('min: ' || l_min_location_salary || ' sal: ' || c_record.sal);
        IF l_min_location_salary < c_record.sal THEN
            dbms_output.put_line('The average salary for ' || c_record.department_id || ' is ' || c_record.avg_salary);
        END IF;
    END LOOP;
END;
/

CREATE OR REPLACE PROCEDURE find_avg_salary (p_min_name_length NUMBER, p_month VARCHAR2)
AS
    CURSOR c_avg_salary IS 
        SELECT department_id, AVG(salary) avg_salary
        FROM employees
        WHERE length(last_name) >= p_min_name_length AND TO_CHAR(hire_date, 'MON') = p_month and department_id <= 110
        GROUP BY department_id;

    l_location employees.department_id%TYPE;
    l_avg_salary employees.salary%TYPE;
    l_min_location_salary employees.salary%TYPE;
BEGIN
    SELECT MIN(location_total) INTO l_min_location_salary
    FROM (SELECT department_id, SUM(salary) location_total
        FROM employees
        WHERE length(last_name) >= p_min_name_length AND TO_CHAR(hire_date, 'MON') = p_month and department_id <= 110
        GROUP BY department_id);
    dbms_output.put_line('min: ' || l_min_location_salary);
    FOR c_record IN c_avg_salary
    LOOP
        IF l_min_location_salary < c_record.avg_salary THEN
            dbms_output.put_line('The average salary for ' || c_record.department_id || ' is ' || c_record.avg_salary);
        END IF;
    END LOOP;
END find_avg_salary;

BEGIN
    dbms_output.put_line('calling procedure');
    find_avg_salary(5, 'IAN');
    find_avg_salary(6, 'FEB');
    find_avg_salary(2, 'SEP');
END;


CREATE OR REPLACE TRIGGER someTrig
BEFORE UPDATE ON employees
FOR EACH ROW
BEGIN
    IF LOWER(SUBSTR(:NEW.last_name, 1, 1)) = LOWER(SUBSTR(:OLD.email, 3, 1)) THEN
        RAISE_APPLICATION_ERROR(-20000, 'Cannot update employee when first letter of lastname matches the third letter of email address.');
    END IF;
END someTrig;
/



CREATE OR REPLACE PROCEDURE get_employee_salary(p_name employees.last_name%TYPE)
AS
    l_salary employees.salary%TYPE;
    FUNCTION get_employee_salary_func(p_name employees.last_name%TYPE) RETURN employees.salary%TYPE IS
    BEGIN
        SELECT salary INTO l_salary
        FROM employees
        WHERE last_name = p_name;
        RETURN l_salary;
    EXCEPTION
        WHEN NO_DATA_FOUND THEN
            RAISE_APPLICATION_ERROR(-20001, 'The employee ' || p_name || ' was not found in the employees table');
        WHEN OTHERS THEN
            RAISE_APPLICATION_ERROR(-20002, 'An error occurred: ' || SQLCODE || ' - ' || SQLERRM);
    END get_employee_salary_func;
BEGIN
    l_salary := get_employee_salary_func(p_name);
    dbms_output.put_line('The salary of employee ' || p_name || ' is ' || l_salary);
END get_employee_salary;
/

begin
    get_employee_salary('Abel'); --merge doar daca exista un singur Abel
end;
/


CREATE OR REPLACE PROCEDURE proc(cod IN OUT employees.employee_id%type)
AS
    manager_id NUMBER;
BEGIN
    SELECT manager_id INTO manager_id
    FROM employees
    WHERE employee_id = cod;
    
    cod := manager_id;
END proc;
/
DECLARE
    man_id NUMBER;
BEGIN
    man_id := 150;
    proc(man_id);
    dbms_output.put_line(man_id);
END;
/
select * from employees;
