-- SQL Queries all types of Join, Sub-Query and View:
-- Write at least10 SQL queries for suitable database application using SQL DML statements

Show databases;
use teassign;
show tables;

-- Employee( Emp_id, Dept_id, Emp_fname, Emp_lname, Emp_Position, Emp_salary,Emp_JoinDate)
-- Dept ( Dept_id, Dept_name,location)
-- Project( Proj_id,Dept_id ,Proj_Name,Proj_Location,Proj_cost,Proj_year)

-- (emp_id ,Dept_id,Emp_fname , Emp_lname, Emp_Position, Emp_salary,Emp_JoinDate)
-- (Dept_id,Dept_name, Dept_location)
-- (proj_id,Dept_id,Proj_Name,Proj_Location ,Proj_cost ,Proj_year )
-- Find Employee details and Department details using NATURAL JOIN.

select * from employee 
inner join Dept 
Where employee.Dept_id = dept.Dept_id;

SELECT * FROM employee as emp
NATURAL JOIN Dept AS dept;

-- SELECT emp.emp_id AS "Employee ID",
-- 	emp.emp_fname AS "Name",
-- 	emp.emp_lname AS "Surname",
-- 	emp.emp_position AS "Position",
-- 	dep.dept_name AS "Department",
-- 	dep.dept_loc AS "Dept. Location",
-- 	emp.emp_salary AS "Salary",
-- 	emp.emp_jdate AS "Joining Date"
-- FROM employee AS emp
-- NATURAL JOIN dept AS dep
-- ;


-- Find the emp_fname,Emp_position,location, Emp_JoinDate who have same Dept id.


SELECT emp.Emp_fname , emp.Emp_Position , Dept.Dept_location , emp.Emp_JoinDate , Dept.Dept_id
FROM employee AS emp
left JOIN Dept 
ON emp.Dept_id = Dept.Dept_id;
-- WHERE Dept_id IN (select Dept_id From Dept group by Dept_id);


SELECT emp.emp_fname AS "Name",
	emp.emp_position AS "Position",
	dep.dept_loc AS "Location",
	emp.emp_jdate AS "Joining Date",
	dep.dept_name AS "Department"
	FROM employee as emp
LEFT JOIN dept as dep
ON emp.dept_id = dep.dept_id
;



select * from employee;
select * from Dept;
select * from project;

INSERT INTO dept(Dept_id,Dept_name, Dept_location)
VALUES (110 , 'IT' , 'Hyderabad' );
INSERT INTO project (proj_id,Dept_id,Proj_Name,Proj_Location ,Proj_cost ,Proj_year )
VALUES (4001,101,'Antitatum','Hyderabad',2212462,'2015-05-14');
-- Find the Employee details ,Proj_id,Project cost who does not have Project location as ‘Hyderabad’.


SELECT * from employee as emp 
Left join project as pro
on (pro.Proj_location != "Hyderabad") AND (emp.Dept_id = pro.Dept_id)
order by emp_id asc
;

SELECT
    emp.emp_id AS "Employee ID",
    emp.emp_fname AS "Name",
    emp.emp_lname AS "Surname",
    emp.emp_position AS "Position",
    emp.emp_salary AS "Salary",
    emp.emp_jdate AS "Joining Date",
    pr.proj_cost AS "Project Cost"
FROM employee AS emp
RIGHT JOIN project as pr
    ON (pr.proj_location != "Hyderabad") AND (emp.dept_id = pr.dept_id)
GROUP BY emp.emp_id;


-- Find Department Name ,employee name, Emp_position for which project year is 2020
-- (emp_id ,Dept_id,Emp_fname , Emp_lname, Emp_Position, Emp_salary,Emp_JoinDate)
-- (Dept_id,Dept_name, Dept_location)
-- (proj_id,Dept_id,Proj_Name,Proj_Location ,Proj_cost ,Proj_year )

SELECT dpt.Dept_name , emp.Emp_fname , emp.Emp_Position from employee as emp
cross join Dept as dpt
on (dpt.Dept_id = emp.Dept_id)
cross join project as pr
on (pr.Dept_id = dpt.Dept_id) ANd (Proj_year between '2020-01-01' AND '2020-12-31');


SELECT
	edj.dept_name AS "Dept. Name",
	edj.emp_fname AS "Employee Name",
	edj.emp_position AS "Position"
FROM (
	SELECT 
		employee.dept_id,
		employee.emp_fname,
		employee.emp_position,
		dept.dept_name
	FROM employee
	LEFT JOIN dept
	ON 
		employee.dept_id = dept.dept_id
) AS edj
RIGHT JOIN project AS pr
ON 
	edj.dept_id = pr.dept_id
WHERE
	pr.proj_year = 2020
; 


-- Display emp_position, dept_name who have Project cost >30000
SELECT dpt.Dept_name , emp.Emp_Position ,emp.emp_id ,  pr.Proj_cost, pr.Proj_Name from employee as emp
left join Dept as dpt
on (dpt.Dept_id = emp.Dept_id)
right join project as pr
on (pr.Dept_id = dpt.Dept_id) ANd (pr.Proj_cost > 30000)
order by emp.emp_id;

SELECT 
	edj.emp_position AS "Position",
	edj.dept_name AS "Dept. Name"
FROM (
	SELECT *
	FROM employee
	NATURAL JOIN dept
	WHERE employee.dept_id = dept.dept_id
) AS edj
RIGHT JOIN project AS pr
ON 
	edj.dept_id = pr.dept_id
WHERE 
	pr.proj_cost > 30000
;


-- Find the names of all the Projects that started in the year 2015.

SELECT Proj_Name AS "Project Name" , Proj_year
FROM project 
WHERE Year(Proj_year) = 2015
;

-- List the Dept_name having no_of_emp =  10
SElect  dpt.Dept_name , count(dpt.Dept_id) from employee as emp , Dept as dpt
where dpt.Dept_id = emp.Dept_id 
group by dpt.Dept_id
having count(dpt.Dept_id) = 4 ;

SElect dpt.Dept_name , count(dpt.Dept_id )  from employee as emp
left join Dept as dpt
on  dpt.Dept_id = emp.Dept_id 
group by dpt.Dept_id 
having count(dpt.Dept_id) = 4;


SELECT 
	edj1.dept_name
FROM (
	SELECT
		COUNT(EDJ.emp_id) AS "CNT", EDJ.dept_name
	FROM (
		SELECT 
			dept.dept_id,
			dept.dept_name,
			employee.emp_id
		FROM dept
		LEFT JOIN employee
		ON 
			dept.dept_id = employee.dept_id
		) as EDJ
	GROUP BY EDJ.dept_id
	) AS edj1
WHERE CNT = 10;


-- Display the total number of employee who have joined any project before 2009
-- (Used complex view)
-- (emp_id ,Dept_id,Emp_fname , Emp_lname, Emp_Position, Emp_salary,Emp_JoinDate)
-- (Dept_id,Dept_name, Dept_location)
-- (proj_id,Dept_id,Proj_Name,Proj_Location ,Proj_cost ,Proj_year )
select count(distinct emp.emp_id) as m from employee as emp 
natural join project 
where year(Proj_year) > '2017'
;


create view temp as 
	select e.emp_id , p.Proj_year 
    from employee as e , project as p
    where e.Dept_id = p.Dept_id;
    
    
select distinct emp_id from temp
where year(Proj_year) > '2017';

CREATE VIEW edv AS
	SELECT d.dept_id, e.emp_fname, p.proj_name, p.proj_year
	FROM employee AS e, dept AS d, project AS p
	WHERE d.dept_id = e.dept_id = p.dept_id
	ORDER BY dept_id
;

SELECT DISTINCT emp_fname 
FROM edv 
WHERE proj_year < 2009
;

-- Create a view showing employee and dept details

CREATE VIEW ed_deets AS
	SELECT 
		e.dept_id,
		e.emp_fname,
		e.emp_lname,
		e.emp_position,
		e.emp_salary,
		e.emp_jdate,
		d.dept_name,
		d.dept_loc
	FROM
		employee AS e,
		dept AS d
	WHERE
		e.dept_id = d.dept_id
	ORDER BY
		dept_id
;

SELECT * FROM ed_deets;

-- 

ALTER TABLE employee
MODIFY emp_id INT PRIMARY KEY NOT NULL AUTO_INCREMENT,
MODIFY dept_id INT DEFAULT 1,
MODIFY emp_fname VARCHAR(20) DEFAULT NULL,
MODIFY emp_lname VARCHAR(20) DEFAULT NULL,
MODIFY emp_position VARCHAR(50) DEFAULT NULL,
MODIFY emp_salary INT DEFAULT NULL,
MODIFY emp_jdate DATE DEFAULT NULL
;

CREATE VIEW sv AS
	SELECT
		emp_fname,
		emp_lname,
		emp_position
	FROM
		employee
	ORDER BY 
		dept_id
;

SELECT * FROM sv;

INSERT INTO
	sv
VALUES
	("Shantanu", "Wable", "CTO"),
	("Riya", "Wani", "CFO"),
	("Atharva", "Zodpe", "GM")
;

DELETE FROM sv
WHERE emp_fname = 'dolores';

UPDATE sv
SET emp_lname = 'UPDATE'
WHERE emp_fname = 'vero'
;