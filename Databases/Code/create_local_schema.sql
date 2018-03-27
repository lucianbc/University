create user local_241 identified by local241;
grant connect to local_241;
grant unlimited tablespace to local_241;

select * from dba_roles;
grant create table to local_241;