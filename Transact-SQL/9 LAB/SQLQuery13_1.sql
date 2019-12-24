USE master;
GO

IF DB_ID('DatabaseAlex13_1') IS NOT NULL
DROP DATABASE DatabaseAlex13_1;

CREATE DATABASE DatabaseAlex13_1
ON PRIMARY
( NAME = DatabaseAlex13_1_dat,
    FILENAME = 'C:\Program Files\Microsoft SQL Server\MSSQL11.SQLEXPRESS\MSSQL\DATA\DatabaseAlex13_1_dat.mdf',
    SIZE = 10,
    MAXSIZE = 50,
    FILEGROWTH = 5 )
LOG ON
( NAME = DatabaseAlex13_1_log,
    FILENAME = 'C:\Program Files\Microsoft SQL Server\MSSQL11.SQLEXPRESS\MSSQL\DATA\DatabaseAlex13_1_dat_log.ldf',
    SIZE = 5MB,
    MAXSIZE = 25MB,
    FILEGROWTH = 5MB );
GO
	
USE DatabaseAlex13_1;
GO 

SET ANSI_PADDING ON;


CREATE TABLE STUDENTS_Regions (
	StudentID INT ,
	FullName VARCHAR(100) NOT NULL, 
	Age INT NOT NULL,
	PlaceOfBirth VARCHAR(100) NOT NULL CHECK (PlaceOfBirth <> 'Moscow'),
	GROUPID INT ,
	CONSTRAINT id_birth PRIMARY KEY (StudentID, PlaceOfBirth)
)ON [PRIMARY];
GO

CREATE VIEW STUDENTS AS 
	SELECT * FROM DatabaseAlex13_1..STUDENTS_Regions
	UNION ALL
	SELECT * FROM DatabaseAlex13_2..STUDENTS_Moscow
GO


INSERT INTO STUDENTS VALUES (1, 'sasha', 19, 'Chelyabinsk', 52), 
							(2,'alena', 20, 'Novgorod', 51),
							(3, 'filon', 20, 'Moscow', 51),
							(4, 'vasya', 20, 'Moscow', 51),
							(5, 'uma', 19, 'Derbent', 52),
							(6, 'misha', 20, 'Ekaterinburg', 52),
							(7, 'ilya', 20, 'Belgorod', 53),
							(8, 'nastya', 19, 'Donbass', 53);
GO

TRUNCATE TABLE STUDENTS_Regions;

SELECT * FROM STUDENTS;

UPDATE STUDENTS
SET PlaceOfBirth = 'Moscow'
WHERE PlaceOfBirth = 'Chelyabinsk';
GO

SELECT * FROM STUDENTS_Regions;

DELETE FROM STUDENTS
WHERE PlaceOfBirth = 'Moscow';
GO

SELECT * FROM STUDENTS;
SELECT * FROM STUDENTS_Regions;

UPDATE STUDENTS_Regions
SET StudentID = 12, PlaceOfBirth = 'sdad'
WHERE PlaceOfBirth = 'Donbass';
GO

CREATE TABLE STUDENTS_Regions_1 (
	StudentID INT ,
	FullName VARCHAR(100) NOT NULL, 
	Age INT NOT NULL,
	PlaceOfBirth VARCHAR(100) NOT NULL CHECK (PlaceOfBirth <> 'Moscow'),
	GROUPID INT ,
	CONSTRAINT birth PRIMARY KEY (PlaceOfBirth)
)ON [PRIMARY];
GO

CREATE VIEW STUDENTS_1 AS 
	SELECT * FROM DatabaseAlex13_1..STUDENTS_Regions_1
	UNION ALL
	SELECT * FROM DatabaseAlex13_2..STUDENTS_Moscow_1
GO


INSERT INTO STUDENTS_1 VALUES (1, 'sasha', 19, 'Chelyabinsk', 52), 
							(2,'alena', 20, 'Novgorod', 51),
							(3, 'filon', 20, 'Moscow', 51),
							(4, 'vasya', 20, 'Moscow', 51),
							(5, 'uma', 19, 'Derbent', 52),
							(6, 'misha', 20, 'Ekaterinburg', 52),
							(7, 'ilya', 20, 'Belgorod', 53),
							(8, 'nastya', 19, 'Donbass', 53);
GO

UPDATE STUDENTS_Regions_1
SET StudentID = 12, PlaceOfBirth = 'sdad'
WHERE PlaceOfBirth = 'Donbass';
GO