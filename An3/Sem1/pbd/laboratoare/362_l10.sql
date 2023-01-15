create table test362(
    id int,
    nume varchar2(50)
);

select 'ce'
from dual;

select *
from test362;

insert into test362 values (1, 'test');
insert into test362 values (2, 'test3');
insert into test362 values (3, 'test33', sysdate-1);

commit;

alter table test362 add (zi date);

update test362
set zi = sysdate - 5
where nume = 'test3';

drop table test362;



/

set serverout on;

create or replace trigger trig_test_ddl
after
delete
on emp2_mcm
for each row
begin
  dbms_output.put_line('test trigger');
end;
/

delete
from emp2_mcm;

rollback;

truncate table emp2_mcm;



select *
from employees
where department_id = 60;

struct rec_ang {
  number id,
  char* first_name
};
/

create or replace type rec_ang_stocat is object(
  id number,
  nume varchar2(50)
);
/

declare
  type rec_ang is record(
    id employees.employee_id%type,
    nume employees.first_name%type
  );
  v_rec_ang rec_ang;
  v_ang employees%rowtype;
begin
  select *
  into v_ang
  from employees
  where employee_id = 123;
  dbms_output.put_line(v_ang.first_name || ' ' || v_ang.salary);
end;
/




declare
  type rec_ang is record(
    id employees.employee_id%type,
    nume employees.first_name%type
  );
  v_rec_ang rec_ang;
  v_ang employees%rowtype;

  type var_ang is varray(200) of employees%rowtype;
  vec_var_ang var_ang;
  --typedef std::array<rec_ang, 200> varr_ang;
  type tab_ang is table of employees%rowtype;
  type tab_ang_idx is table of employees%rowtype index by pls_integer;
  v_tab tab_ang_idx;
begin
/*  select *
  into v_ang
  from employees
  where employee_id = 123;
  dbms_output.put_line(v_ang.first_name || ' ' || v_ang.salary);
*/
  select *
  bulk collect into v_tab
  from employees
  where department_id = 30;

  for i in v_tab.first..v_tab.last loop
    dbms_output.put_line(v_tab(i).first_name || ' ' || v_tab(i).salary);
  end loop;
end;
/

declare
  type tab_ang_idx is table of employees%rowtype index by pls_integer;
  v_tab tab_ang_idx;

  cursor c(dep_id employees.department_id%type) is
    select *
    from employees
    where department_id = dep_id;
begin
/*  select *
  into v_ang
  from employees
  where employee_id = 123;
  dbms_output.put_line(v_ang.first_name || ' ' || v_ang.salary);
*/
  open c(30);
  --fetch c
  --into v_tab;
  fetch c
  bulk collect into v_tab;
  
  close c;

  for i in v_tab.first..v_tab.last loop
    dbms_output.put_line(v_tab(i).first_name || ' ' || v_tab(i).salary);
  end loop;
end;
/

declare
  type tab_ang_idx is table of employees%rowtype index by pls_integer;
  v_tab tab_ang_idx;

  cursor c(dep_id employees.department_id%type) is
    select *
    from employees
    where department_id = dep_id;
  idx number := 1;
begin
/*  select *
  into v_ang
  from employees
  where employee_id = 123;
  dbms_output.put_line(v_ang.first_name || ' ' || v_ang.salary);
*/
  open c(60);
  --fetch c
  --into v_tab;
  loop
    fetch c
    bulk collect into v_tab limit 2;
    dbms_output.put_line('c%rowcount: ' || c%rowcount);
    dbms_output.put_line('v_tab.count: ' || v_tab.count);
    --exit when c%notfound;
    exit when v_tab.count = 0;
    dbms_output.put_line('batch nr ' || idx);
    idx := idx+1;
    for i in v_tab.first..v_tab.last loop
      dbms_output.put_line('--> ' || v_tab(i).first_name || ' ' || v_tab(i).salary);
    end loop;
  end loop;
  close c;
end;
/

create or replace function f1
return number
is
begin
  return 2;
end;
/

create or replace procedure p1
is
begin
  dbms_output.put_line('p1');
end;
/

select f1
from dual;

/
begin
  p1;
  dbms_output.put_line(f1);
end;

/

create or replace procedure prc_test(dep employees.department_id%type)
is
  type tab_ang_idx is table of employees%rowtype index by pls_integer;
  v_tab tab_ang_idx;

  cursor c(dep_id employees.department_id%type) is
    select *
    from employees
    where department_id = dep_id;
  idx number := 1;
begin
/*  select *
  into v_ang
  from employees
  where employee_id = 123;
  dbms_output.put_line(v_ang.first_name || ' ' || v_ang.salary);
*/
  open c(dep);
  --fetch c
  --into v_tab;
  loop
    fetch c
    bulk collect into v_tab limit 2;
    dbms_output.put_line('c%rowcount: ' || c%rowcount);
    dbms_output.put_line('v_tab.count: ' || v_tab.count);
    --exit when c%notfound;
    exit when v_tab.count = 0;
    dbms_output.put_line('batch nr ' || idx);
    idx := idx+1;
    for i in v_tab.first..v_tab.last loop
      dbms_output.put_line('--> ' || v_tab(i).first_name || ' ' || v_tab(i).salary);
    end loop;
  end loop;
  close c;
end prc_test;
/

begin
  prc_test(60);
  dbms_output.put_line('-----------');
  prc_test(50);
end;
/


