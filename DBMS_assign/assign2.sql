-- Employee( Emp_id, Dept_id, Emp_fname, Emp_lname, Emp_Position, Emp_salary,Emp_JoinDate)
-- Dept ( Dept_id, Dept_name,Dept_location ,)
-- Project( Proj_id,Dept_id ,Proj_Name,Proj_Location,Proj_cost,Proj_year)


-- Create view (simple), index, sequence and synonym based on above tables.
-- Note: Use referential integrity constraints while creating tables with on delete cascade
-- options.

-- 1. Insert at least 10 records in the Employee table and insert other tables accordingly.
-- 2. Display all Employee details with Department ‘Computer’ and ‘IT’ and Employee first name starting with 'p' or 'h'.
-- 3. lists the number of different Employee Positions.
-- 4. Give 10% increase in Salary of the Employee whose Birthdate before 1985.
-- 5. Delete Department details which location is ‘Mumbai’.
-- 6. Find the names of Projects with location ‘pune’ .
-- 7. Find the project having cost in between 100000 to 500000.
-- 8. Find the project having maximum price and find average of Project cost
-- 9. Display all employees with Emp _id and Emp name in decreasing order of Emp_lname
-- 10. Display Proj_name,Proj_location ,Proj_cost of all project started in 2004,2005,2007



use test;
show tables;

create table employee(
    emp_id INT PRIMARY KEY,
    Dept_id INT ,
    Emp_fname VARCHAR(255), 
    Emp_lname VARCHAR(255), 
    Emp_Position VARCHAR(255), 
    Emp_salary INT,
    Emp_JoinDate DATE
);
create table dept(
    Dept_id INT PRIMARY KEY, 
    dept_name VARCHAR(255),
    dept_location VARCHAR(255) 
);
create table project(
    proj_id INT PRIMARY KEY,
    Dept_id INT,
    Proj_Name VARCHAR(255),
    Proj_Location VARCHAR(255),
    Proj_cost INT,
    Proj_year DATE
);


INSERT INTO employee(emp_id ,Dept_id,Emp_fname , Emp_lname, Emp_Position, Emp_salary,Emp_JoinDate)
VALUES (10 , 101 , 'ajinkya' , 'mogal' , 'manager' , 100000  , '2020-9-25'),
(1 , 102 , 'peeyush' , 'kulgude' , 'Consultant' , 100000  , '2021-7-25'),
(2 , 101 , 'ninad' , 'more' , 'product manager' , 30000  , '2019-2-25'),
(3 , 103 , 'soham' , 'badjate' , 'advisor' , 300000  , '2017-1-25'),
(4 , 102 , 'ankit' , 'mogal' , 'advisor' , 564000  , '2015-3-25'),
(5 , 102 , 'parth' , 'jadhav' , 'manager' , 980000  , '2021-4-25'),
(6 , 103 , 'krishna' , 'patil' , 'Consultant' , 90000  , '2022-4-25'),
(7 , 102 , 'madhava' , 'pawar' , 'senior advisor' , 23000  , '2023-9-25'),
(8 , 103 , 'madhusudhan' , 'modi' , 'content head' , 32000  , '2022-11-25'),
(9 , 101 , 'kanha' , 'gandhi' , 'manager' , 50000  , '2020-10-25');

select * from employee;

INSERT INTO dept(Dept_id,Dept_name, Dept_location)
VALUES (101 , 'IT' , 'pune' ),
( 102 , 'Computer' , 'nashik' ),
(103 , 'hardware' , 'nagpur' );

INSERT INTO dept(Dept_id,Dept_name, Dept_location)
VALUES (104 , 'IT' , 'new delhi' ),
(106 , 'Computer' , 'new delhi' ),
( 105 , 'Computer' , 'chennai' ),
(107 , 'hardware' , 'chennai' ),
( 108 , 'Computer' , 'Mumbai' ),
(109 , 'hardware' , 'Mumbai' );

select * from dept;


create table project(
    proj_id INT PRIMARY KEY,
    Dept_id INT,
    Proj_Name VARCHAR(255),
    Proj_Location VARCHAR(255),
    Proj_cost INT,
    Proj_year DATE
);
INSERT INTO project (proj_id,Dept_id,Proj_Name,Proj_Location ,Proj_cost ,Proj_year )
VALUES 
	(1001,101,'voluptatum','New delhi',2212462,'2015-05-14'),
	(1007,101,'odio','pune',3031102,'2017-01-7'),
	(4003,103,'debitis','nagapur',2621647,'2016-1-14'),
	(4006,103,'beatae','chennai',4670329,'2020-03-05'),
	(4007,102,'explicabo','nashik',4373152,'2023-04-07'),
	(1008,102,'sunt','chennai',1252457,'2022-12-01'),
	(1015,102,'maiores','Mumbai',2387308,'2021-11-16'),
	(1041,101,'quis','Mumbai',2332175,'2015-12-30'),
	(1043,102,'rerum','pune Reinhold',1199693,'2015-11-10'),
	(1500,101,'est','nashik',3076611,'2016-11-4')
;


-- ********************
-- 2. Display all Employee details with Department ‘Computer’ and ‘IT’ and Employee
first name starting with 'p' or 'h'.
emp_id ,Dept_id,Emp_fname , Emp_lname, Emp_Position, Emp_salary,Emp_JoinDate
Dept_id,Dept_name, Dept_location

SELECT * FROM employee 
WHERE (Dept_id IN (SELECT Dept_id FROM dept WHERE Dept_name = 'Computer' OR Dept_name = 'IT')) 
        AND (Emp_fname LIKE 'p%' OR Emp_fname LIKE 'h%');



-- *****************
-- 3.lists the number of different Employee Positions.

SELECT DISTINCT Emp_Position FROM employee;



-- **************
-- 4.Give 10% increase in Salary of the Employee whose Birthdate before 1985.


INSERT INTO employee
VALUES (11 , 103 , 'prakash' , 'mahale' , 'Consultant' , 100000  , '1980-7-25'),
(12 , 102 , 'prinkesh' , 'kale' , 'Consultant' , 100000  , '1978-7-16'),
(13 , 103 , 'sahil' , 'gore' , 'senior advisor' , 100000  , '1984-7-21');

UPDATE employee
set Emp_salary = Emp_salary * 1.1
WHERE YEAR(Emp_JoinDate) < '1985';


-- **********************************

-- 5. Delete Department details which location is ‘Mumbai’.

DELETE FROM dept 
WHERE Dept_location = 'Mumbai';

INSERT INTO dept(Dept_id,Dept_name, Dept_location)
VALUES ( 108 , 'Computer' , 'Mumbai' ),
(109 , 'hardware' , 'Mumbai' );

-- **************************************
-- 6. Find the names of Projects with location ‘pune’ .
-- proj_id,Dept_id,Proj_Name,Proj_Location ,Proj_cost ,Proj_year

SELECT Proj_Name FROM project
WHERE Proj_Location = 'pune';


-- *****************************************
-- 7. Find the project having cost in between 100000 to 500000.


SELECT * from project
where Proj_cost <= 500000 AND Proj_cost >= 100000;


SELECT * FROM project WHERE Proj_cost BETWEEN 1000000 AND 5000000;

-- **************************
-- 8. Find the project having maximum price and find average of Project cost

SELECT MAX(Proj_cost) AS max , AVG(Proj_cost) AS average FROM project;


-- ***********************************
-- 9. Display all employees with Emp _id and Emp name in decreasing order of Emp_lname
-- emp_id ,Dept_id,Emp_fname , Emp_lname, Emp_Position, Emp_salary,Emp_JoinDate

SELECT emp_id , Emp_fname ,Emp_lname  FROM employee
ORDER BY Emp_lname DESC;

-- *********************************
-- 10. Display Proj_name,Proj_location ,Proj_cost of all project started in 2004,2005,2007
-- proj_id,Dept_id,Proj_Name,Proj_Location ,Proj_cost ,Proj_year

SELECT Proj_Name  ,Proj_Location , Proj_cost FROM project
WHERE YEAR(Proj_year) IN(2004 , 2005 , 2007);

-- in my table
SELECT Proj_Name  ,Proj_Location , Proj_cost , Proj_year FROM project
WHERE YEAR(Proj_year) IN(2014 , 2015 , 2017);