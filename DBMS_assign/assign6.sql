 -- Cursors: (All types: Implicit, Explicit, Cursor FOR Loop, 
-- Parameterized Cursor)


-- Write a PL/SQL block of code using parameterized Cursor, that 
-- will merge the data available in the newly created table 
-- N_EmpId with the data available in the table O_EmpId.
-- If the data in the first table already exist in the second table then 
-- that data should be skipped.

CREATE TABLE O_RollCall (
    roll INT,
    sname VARCHAR(40)
);

-- Insert some sample data into the O_RollCall table
INSERT INTO O_RollCall (roll, sname)
VALUES
    (1, 'Alice'),
    (2, 'Bob'),
    (3, 'Charlie'),
    (4, 'David'),
    (5, 'Eve');

-- Create the N_RollCall table
CREATE TABLE N_RollCall (
    roll INT,
    sname VARCHAR(40)
);
SELECT * FROM O_RollCall;
SELECT * FROM N_RollCall;
DELIMITER $
CREATE PROCEDURE proc_cur(R int)
BEGIN
	DECLARE N VARCHAR(40);
	DECLARE VAR1,F1 int default 0;
    
	DECLARE C1 CURSOR FOR SELECT roll,sname FROM O_RollCall WHERE roll<=R;
	DECLARE CONTINUE HANDLER FOR NOT FOUND SET VAR1:=1;
    
	OPEN C1;
	LABEL: LOOP
		FETCH C1 INTO R,N;
		SELECT EXISTS (SELECT roll,sname FROM N_RollCall WHERE roll=R) INTO F1;
		SELECT F1;
        
		IF F1=0 THEN
		INSERT INTO N_RollCall VALUES(R,N);
		END IF;
        
		IF VAR1=1 THEN
		CLOSE C1;
		LEAVE LABEL;
		END IF;
        
	END LOOP;
	SELECT* FROM N_RollCall;
END$

CALL proc_cur(2);
SELECT * FROM N_RollCall;
CALL proc_cur(5);