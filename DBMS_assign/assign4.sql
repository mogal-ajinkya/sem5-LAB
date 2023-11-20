-- Unnamed PL/SQL code block: Use of Control structure
-- and Exception handling is mandatory. Write a PL/SQL
-- block of code for the following requirements:-
-- Schema:
-- 1. Borrower(Roll,Name,DateofIssue, NameofBook, Status)
-- 2. Fine (Roll, Date, Amt)
-- Accept Roll & N ame of book from user.
-- Check the number of days (from date of issue), if days
-- are between 15 to 30 then fine amount will be Rs 5per day.
-- If no. of days>30, per day fine will be Rs 50 per day &
-- for days less than 30, Rs. 5 per day.
-- After submitting the book, status will change from I to R.
-- If condition of fine is true, then details will be stored into
-- fine table.
-- Frame the problem statement for writing PL/SQL block
-- inline with above statement

use teassign;

CREATE TABLE borrower(
	roll_no int primary key,
	studname varchar(255),
	dateOfIssue date,
	nameOfBook varchar(255),
	bookstatus varchar(255)
); 
CREATE TABLE fine(
	roll_no int,
	curDate date,
	amount int
); 
drop table borrower;
drop table fine;
INSERT INTO borrower
VALUES  (1, "Rahul","2023-04-10", "Three Mistakes", 'I'),
		(2 , "Anup", "2023-04-20","Belated Party", 'I'),
		(3, "Janvi", "2023-05-10", "Atomic Habits",  'I'),
		(4, "Vedant","2023-05-25", "Eat that frog",  'I'),
		(5, "Aditya", "2023-06-23", "Will by Will",  'I');

SELECT * FROM fine;
SELECT * FROM borrower;
SELECT DATEDIFF("2023-06-23", dateOfIssue) as diff FROM borrower WHERE roll_no = 4;


DROP PROCEDURE IF EXISTS update_fine;
DELIMITER $
CREATE PROCEDURE update_fine
( in roll int, in bookName varchar(255), in cDate date)
BEGIN
	DECLARE fineAmount, diff INT;
    
	SET diff = (SELECT DATEDIFF(cDate, dateOfIssue) FROM borrower WHERE roll = roll_no);
    
	IF diff > 30 THEN
		SET fineAmount = diff * 50;
		INSERT INTO fine VALUES( roll, cDate, fineAmount);
		UPDATE borrower SET bookstatus = 'R' WHERE roll_no = roll;
	ELSEIF diff <= 30 AND diff > 14 THEN
		SET fineAmount = diff * 5;
		INSERT INTO fine VALUES( roll, cDate, fineAmount);
		UPDATE borrower SET bookstatus = 'R' WHERE roll_no = roll;
	END IF;
END $
DELIMITER ;
SHOW PROCEDURE STATUS WHERE db = 'teassign';
call update_fine(2,'Belated Party','2023-05-16');
call update_fine(3,'Atomic Habits','2023-06-10');
call update_fine(4, 'Eat that frog','2023-06-10');

select * from Fine ;
   select * from Borrower ;