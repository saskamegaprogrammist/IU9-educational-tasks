USE master;
GO

IF DB_ID('DatabaseAlex') IS NOT NULL
DROP DATABASE DatabaseAlex;

CREATE DATABASE DatabaseAlex
ON PRIMARY
( NAME = DatabaseAlex_dat,
    FILENAME = 'C:\Program Files\Microsoft SQL Server\MSSQL11.SQLEXPRESS\MSSQL\DATA\DatabaseAlex_dat.mdf',
    SIZE = 10,
    MAXSIZE = 50,
    FILEGROWTH = 5 )
LOG ON
( NAME = DatabaseAlex_log,
    FILENAME = 'C:\Program Files\Microsoft SQL Server\MSSQL11.SQLEXPRESS\MSSQL\DATA\DatabaseAlex_dat_log.ldf',
    SIZE = 5MB,
    MAXSIZE = 25MB,
    FILEGROWTH = 5MB );
GO
	
USE DatabaseAlex;
GO 

CREATE SCHEMA Lab5;
GO


CREATE TABLE Lab5.GROUPS (
	GROUPID INT IDENTITY(1,1),
	GroupName VARCHAR(100) PRIMARY KEY , 
	GroupLeader VARCHAR(100) ,
	BudgetStudents INT,
	NumOfStudents INT,
	Tutor VARCHAR(100),
)ON [PRIMARY];

GO


CREATE TABLE Lab5.STUDENTS (
	StudentID INT PRIMARY KEY IDENTITY(1,1),
	FullName VARCHAR(100) NOT NULL, 
	Age INT NOT NULL,
	Budget BIT, 
	PlaceOfBirth VARCHAR(100),
	GroupName VARCHAR(100) ,
	CONSTRAINT FK_GroupId FOREIGN KEY (GroupName) REFERENCES Lab5.GROUPS (GroupName) ON DELETE SET NULL,
)ON [PRIMARY];
GO


SET IDENTITY_INSERT Lab5.STUDENTS OFF;  
GO  



CREATE TRIGGER Lab5.NewGroup ON Lab5.STUDENTS
INSTEAD OF INSERT 
AS 
BEGIN
	INSERT INTO Lab5.GROUPS ( 
        GroupName, NumOfStudents, BudgetStudents
    )
    SELECT
        i.GroupName, 0, 0
    FROM
        inserted i
    WHERE
        i.GroupName NOT IN (
            SELECT 
                GroupName
            FROM
                Lab5.GROUPS
			
        )
	GROUP BY GroupName;
	UPDATE Lab5.GROUPS
		SET NumOfStudents = NumOfStudents + St.Total,	
		BudgetStudents = BudgetStudents + St.Budget
		FROM 
			(SELECT GroupName as Name, COUNT(*) as Total,  SUM(CAST(Budget AS INT))  as Budget
			FROM inserted
			GROUP BY GroupName) as St
		WHERE Lab5.GROUPS.GroupName = St.Name
	INSERT INTO Lab5.STUDENTS (FullName, Age, Budget, PlaceOfBirth, GroupName)
    SELECT
       FullName, Age, Budget ,  PlaceOfBirth, GroupName
    FROM
        inserted 
END;
GO




--INSERT INTO Lab5.GROUPS VALUES ('iu9-51', 'nika', 0, 0, 'Skorb'), ('iu9-52', 'janush', 0, 0, 'Dubashka'), ('iu9-53', 'dima', 0, 0, 'Golub');

INSERT INTO Lab5.STUDENTS VALUES ('sasha', 19, 1, 'Chelyabinsk', 'iu9-52'), ('alena', 20, 1, 'Novgorod', 'iu9-51'),
('ilya', 20, 0, 'Belgorod', 'iu9-53'), ('filon', 20, 0, 'Moscow', 'iu9-51');
GO


CREATE TRIGGER Lab5.BudgetStudents ON Lab5.STUDENTS
AFTER UPDATE
AS 
IF (COLUMNS_UPDATED() & 8) = 8
BEGIN
	UPDATE Lab5.GROUPS
		SET BudgetStudents = St.Budget
		FROM 
			(SELECT GroupName as Name, SUM(CAST(Budget AS INT))  as Budget
			FROM Lab5.STUDENTS
			GROUP BY GroupName) as St
		WHERE Lab5.GROUPS.GroupName = St.Name
END;
GO

UPDATE Lab5.STUDENTS
SET Budget = 1
WHERE Lab5.STUDENTS.PlaceOfBirth <> 'Moscow'
GO	


CREATE TRIGGER Lab5.DeleteStudent ON Lab5.GROUPS
AFTER DELETE
AS 
BEGIN
	IF (
		SELECT COUNT(*)
		FROM Lab5.STUDENTS
		WHERE GroupName IS NOT NULL
		) > 0 
		THROW 51000, 'Deleted Existed Group', 1; 
END;
GO

DELETE FROM Lab5.GROUPS  
WHERE GroupName = 'iu9-51';  
GO  

SELECT * FROM Lab5.STUDENTS;
SELECT * FROM Lab5.GROUPS;


GO



CREATE VIEW Lab5.studentsGroup WITH SCHEMABINDING  AS  
SELECT FullName, GroupName, Age 
FROM Lab5.STUDENTS
WHERE (Budget=1)
GO

CREATE TRIGGER Lab5.ageViewTrigger ON Lab5.studentsGroup
INSTEAD OF INSERT 
AS 
BEGIN
	IF (SELECT COUNT(*)
		FROM inserted i
		WHERE
        i.GroupName NOT IN (
            SELECT 
                GroupName
            FROM
                Lab5.studentsGroup
        )) > 0
		THROW 51000, 'Cannot insert into view student with not existing group', 1; 
	ELSE 
		INSERT INTO Lab5.STUDENTS(FullName, Age, GroupName, Budget)
		SELECT
			FullName, Age, GroupName, 1
		FROM
			inserted 
END;
GO

SELECT * FROM Lab5.studentsGroup

INSERT INTO Lab5.studentsGroup VALUES ('anton', 'iu9-52', 20), ('stepan', 'iu9-53', 21);
GO

SELECT * FROM Lab5.studentsGroup
SELECT * FROM Lab5.STUDENTS;
SELECT * FROM Lab5.GROUPS;
GO

CREATE TRIGGER Lab5.ageViewTriggerUpd ON Lab5.studentsGroup
INSTEAD OF UPDATE 
AS 
BEGIN
	IF (SELECT COUNT(*)
		FROM inserted i
		WHERE
        i.GroupName NOT IN (
            SELECT 
                GroupName
            FROM
                Lab5.studentsGroup
        )) > 0
		THROW 51000, 'Cannot update view student with not existing group', 1; 
	ELSE 
		UPDATE Lab5.studentsGroup
		SET Lab5.studentsGroup.GroupName = i.GroupName,
			Lab5.studentsGroup.Age = i.Age
		FROM Lab5.studentsGroup
		JOIN inserted as i
		ON Lab5.studentsGroup.FullName = i.FullName

END;
GO


UPDATE Lab5.studentsGroup
SET GroupName = 'iu9-51'
WHERE Lab5.studentsGroup.Age = 20
GO	

SELECT * FROM Lab5.studentsGroup
SELECT * FROM Lab5.STUDENTS;
SELECT * FROM Lab5.GROUPS;
GO

CREATE TRIGGER Lab5.DeleteStudentView ON Lab5.studentsGroup
INSTEAD OF DELETE
AS 
BEGIN
	IF EXISTS (
		SELECT *
		FROM   Lab5.studentsGroup 
		WHERE (SELECT count(*)  FROM deleted
		WHERE deleted.GroupName = Lab5.studentsGroup.GroupName) = 1
		) 
		THROW 51000, 'Deleted Existed Group', 1; 
	DELETE FROM Lab5.studentsGroup 
	FROM Lab5.studentsGroup 
	JOIN deleted as d
	ON Lab5.studentsGroup.FullName = d.FullName 
END;
GO

DELETE FROM Lab5.studentsGroup  
WHERE GroupName = 'iu9-51';  
GO  

SELECT * FROM Lab5.studentsGroup
SELECT * FROM Lab5.STUDENTS;
SELECT * FROM Lab5.GROUPS;
GO