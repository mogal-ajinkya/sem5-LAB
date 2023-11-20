-- Named PL/SQL Block: PL/SQL Stored Procedure and
-- Stored Function.
-- Write a Stored Procedure namely proc_Grade for the
-- categorization of student. If marks scored by students in
-- examination is <=1500 and marks>=990 then student will
-- be placed in distinction category if marks scored are 
-- between 989 and900 category is first class, if 
-- marks899and 825 category is Higher Second Class.
-- Write a PL/SQLblock to use procedure created with
-- above requirement.
-- Stud_Marks(name, total_marks) 
-- Result(Roll,Name, Class)

show databases;
use teassign;
show tables;


CREATE TABLE stud_marks (
  ROLL_NO INT,
  STUD_NAME VARCHAR(255),
  TOTAL_MARKS INT
);
create table result(
	STUD_NAME varchar(255),
	ROLL_NO INT,
	CLASS varchar(255)
);
INSERT INTO stud_marks (ROLL_NO , STUD_NAME, Total_Marks)
VALUES
	(1 , 'John Doe', 1200),
	(2 ,'Jane Smith', 950),
	(3 ,'Alice Johnson', 1050),
	(4 ,'Bob Brown', 800);
    
SELECT * FROM stud_marks;
SELECT * FROM result;

SHOW PROCEDURE STATUS WHERE db = 'teassign';
SHOW PROCEDURE STATUS WHERE db = 'teassign';
 
drop table result;
DROP FUNCTION IF EXISTS func;

DELIMITER $
SELECT * FROM stud_marks$
CREATE FUNCTION func
(ROLL_NO INT) RETURNS varchar(255) DETERMINISTIC
BEGIN	

	DECLARE m INT;
	DECLARE c VARCHAR(255);

	SELECT TOTAL_MARKS INTO m FROM stud_marks WHERE stud_marks.ROLL_NO=ROLL_NO;
	if m <= 1500 and m >= 990 then
	set c := 'distinction class';
	elseif m <= 990 and m >= 900 then
	set c := 'first class';
	elseif m <= 899 and m >= 825 then
	set c := 'higher second class';
	else
	set c := 'other';
	end if;
return c;
end$
DELIMITER ;

SHOW PROCEDURE STATUS WHERE db = 'teassign';
DROP PROCEDURE IF EXISTS proc_grade;

DELIMITER $

CREATE PROCEDURE proc_grade()
BEGIN
	DECLARE max_num int;
	DECLARE iterator int;
	DECLARE c varchar(255);
    DECLARE n varchar(255);
	DECLARE EXIT HANDLER FOR SQLException SELECT "Table is not found!";
    
	SELECT max(ROLL_NO) into max_num from stud_marks;
	SELECT min(ROLL_NO) into iterator from stud_marks;
    
	while iterator <= max_num do
		
		IF EXISTS(select STUD_NAME from stud_marks where stud_marks.ROLL_NO=iterator) then
		SELECT STUD_NAME INTO n from stud_marks WHERE stud_marks.ROLL_NO=iterator;
        SET c := func(iterator);
		INSERT result VALUES (n ,iterator, c) ON DUPLICATE KEY UPDATE class=c;
		END IF;
		SET iterator := iterator + 1;
	END WHILE;
    
END$
DELIMITER ;

SHOW FUNCTION STATUS WHERE db = 'teassign';
SHOW PROCEDURE STATUS WHERE db = 'teassign';
 
CALL proc_grade();
SELECT * FROM result;