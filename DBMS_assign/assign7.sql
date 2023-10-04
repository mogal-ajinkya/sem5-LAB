-- Database Trigger (All Types: Row level and Statement
-- level triggers, Before and After Triggers).

-- Write a database trigger on Library table. The System should keep
-- track of the records that are being updated or deleted. The
-- old value of updated or deleted records should be added in
-- Library_Audit table.
-- Frame problem statement for writing Database
-- Triggers of all types, inline with above statement. The 
-- problem statement should clearly state the
-- requirements.'

SET SQL_SAFE_UPDATES=0;

use teassign;
CREATE TABLE Library (
    bid INT,
    bname VARCHAR(255),
    doi DATE,
    status CHAR(1)
);

INSERT INTO Library (bid, bname, doi, status)
VALUES
    (1, 'The Alchemist', '2023-09-10', 'I'),
    (2, 'To Kill a Mockingbird', '2023-09-11', 'I'),
    (3, 'The Great Gatsby', '2023-09-12', 'I'),
    (4, '1984', '2023-09-13', 'I'),
    (5, 'Brave New World', '2023-09-14', 'I'),
    (6, 'Lord of the Flies', '2023-09-15', 'I');
    
SELECT * FROM Library;

CREATE TABLE Library_Audit (
    book_id INT,
    book_name VARCHAR(255),
    new_bname VARCHAR(255),
    date_of_issue DATE,
    bstatus CHAR(1)
);

SELECT * FROM Library_Audit;



-- Insert trigger
delimiter $
create trigger insert_trigger before insert 
on Library 
for each row 
begin
	if new.bname LIKE '1%' then
	signal sqlstate '45000' set message_text='INCORRECT NAME';
	end if;
end$
DELIMITER ;

SHOW TRIGGERS FROM teassign;
INSERT INTO Library (bid, bname, doi, status)
VALUES (1, 'aganipankh', '2023-09-10', 'I');

DELETE FROM Library 
WHERE bname = 'aganipankh';
DELETE FROM Library 
WHERE bname = 'itis';
SELECT * FROM Library;


-- BEFORE UPDATE

create trigger update_trigger before update
on Library
for each row
insert into Library_Audit (book_id,book_name,date_of_issue,bstatus)values (OLD.bid,OLD.bname,OLD.doi,OLD.status);

UPDATE Library
set bname = 'hiii'
where bid = 1;

SELECT * FROM Library_Audit;

-- AFTER UPDATE

create trigger update_trigger1
after update on Library
for each row
insert into Library_Audit values(OLD.bid,OLD.bname,new.bname,OLD.doi,OLD.status);

UPDATE Library
set bname = 'hey'
where bid = 1;

SELECT * FROM Library_Audit;


-- before delete

create trigger delete_trigger1
before delete on Library
for each row
insert into Library_Audit (book_id,book_name,date_of_issue,bstatus)values (OLD.bid,OLD.bname,OLD.doi,OLD.status);

DELETE FROM Library 
WHERE bname = 'hey';
SELECT * FROM Library_Audit;

-- after delete

create trigger delete_trigger2
after delete on Library
for each row
insert into Library_Audit (book_id,book_name,date_of_issue,bstatus)values (OLD.bid,OLD.bname,OLD.doi,OLD.status);

drop trigger delete_trigger2;
DELETE FROM Library 
WHERE bname = 'hii';
SELECT * FROM Library_Audit;