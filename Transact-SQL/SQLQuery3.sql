USE master;
GO

IF DB_ID('ThirdDatabaseAlex') IS NOT NULL
DROP DATABASE ThirdDatabaseAlex;

CREATE DATABASE ThirdDatabaseAlex
ON PRIMARY
( NAME = ThirdDatabaseAlex_dat,
    FILENAME = 'C:\Program Files\Microsoft SQL Server\MSSQL11.SQLEXPRESS\MSSQL\DATA\ThirdDatabaseAlex_dat.mdf',
    SIZE = 10,
    MAXSIZE = 50,
    FILEGROWTH = 5 )
LOG ON
( NAME = ThirdDatabaseAlex_log,
    FILENAME = 'C:\Program Files\Microsoft SQL Server\MSSQL11.SQLEXPRESS\MSSQL\DATA\ThirdDatabaseAlex_dat_log.ldf',
    SIZE = 5MB,
    MAXSIZE = 25MB,
    FILEGROWTH = 5MB );
GO
	
USE ThirdDatabaseAlex;
GO 

CREATE SCHEMA Lab3;
GO

CREATE TABLE Lab3.GROUPS (
	GROUPID INT PRIMARY KEY IDENTITY(1,1),
	GroupName VARCHAR(100) NOT NULL, 
	GroupLeader VARCHAR(100) NOT NULL,
	NumOfStudents INT,
	Tutor VARCHAR(100) NOT NULL,
)ON [PRIMARY];

GO


CREATE TABLE Lab3.STUDENTS (
	StudentID INT PRIMARY KEY IDENTITY(1,1),
	FullName VARCHAR(100) NOT NULL, 
	Age INT NOT NULL,
	PlaceOfBirth VARCHAR(100) NOT NULL,
	Budget BIT NOT NULL,  
	GROUPID INT ,
	CONSTRAINT FK_GroupId FOREIGN KEY (GROUPID) REFERENCES Lab3.GROUPS (GROUPID) ON DELETE CASCADE,
)ON [PRIMARY];
GO

INSERT INTO Lab3.GROUPS VALUES ('iu9-51', 'nika', 31, 'Skorb'), ('iu9-52', 'janush', 30, 'Dubashka'), ('iu9-53', 'dima', 0, 'Golub');

INSERT INTO Lab3.STUDENTS VALUES ('sasha', 19, 'Chelyabinsk', 1, (SELECT GROUPID from Lab3.GROUPS WHERE (GroupName = 'iu9-52'))), 
							('alena', 20, 'Novgorod', 1,  (SELECT GROUPID from Lab3.GROUPS WHERE (GroupName = 'iu9-51'))),
							('filon', 20, 'Moscow', 0, (SELECT GROUPID from Lab3.GROUPS WHERE (GroupName = 'iu9-51'))),
							('vasya', 20, 'Moscow', 0, (SELECT GROUPID from Lab3.GROUPS WHERE (GroupName = 'iu9-51'))),
							('uma', 19, 'Derbent', 1, (SELECT GROUPID from Lab3.GROUPS WHERE (GroupName = 'iu9-52'))),
							('misha', 20, 'Ekaterinburg', 1, (SELECT GROUPID from Lab3.GROUPS WHERE (GroupName = 'iu9-52'))),
							('ilya', 20, 'Belgorod', 0, (SELECT GROUPID from Lab3.GROUPS WHERE (GroupName = 'iu9-53'))),
							('nastya', 19, 'Donbass', 1,  (SELECT GROUPID from Lab3.GROUPS WHERE (GroupName = 'iu9-53')));

GO

CREATE VIEW Lab3.group_students AS
SELECT GroupName, NumOfStudents
FROM Lab3.GROUPS;

GO

SELECT * from Lab3.group_students;
GO

CREATE VIEW Lab3.students_tutor AS
SELECT gr.Tutor, st.FullName
FROM Lab3.GROUPS as gr
JOIN STUDENTS as st
ON (gr.GROUPID=st.GROUPID);

GO

SELECT * from Lab3.students_tutor;
GO

CREATE VIEW Lab3.first_group_students AS
SELECT gr.GroupName, st.FullName
FROM Lab3.GROUPS as gr
JOIN STUDENTS as st
ON (gr.GROUPID=st.GROUPID)
WHERE (gr.GroupName='iu9-51')

GO

SELECT * from Lab3.first_group_students;
GO

CREATE INDEX I_NUM ON Lab3.GROUPS(NumOfStudents);

SELECT * from Lab3.GROUPS;

SET NUMERIC_ROUNDABORT OFF;
SET ANSI_PADDING, ANSI_WARNINGS, CONCAT_NULL_YIELDS_NULL, ARITHABORT,
   QUOTED_IDENTIFIER, ANSI_NULLS ON;
GO


CREATE VIEW Lab3.students_budget WITH SCHEMABINDING  AS  
SELECT FullName, Age, Budget 
FROM Lab3.STUDENTS
WHERE (Budget=1)
GO

CREATE UNIQUE CLUSTERED INDEX ID_Name
   ON Lab3.students_budget (FullName);
GO

SELECT * from Lab3.students_budget
ORDER BY FullName;
GO