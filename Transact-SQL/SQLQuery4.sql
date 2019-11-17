USE master;
GO

IF DB_ID('FourthDatabaseAlex') IS NOT NULL
DROP DATABASE FourthDatabaseAlex;

CREATE DATABASE FourthDatabaseAlex
ON PRIMARY
( NAME = FourthDatabaseAlex_dat,
    FILENAME = 'C:\Program Files\Microsoft SQL Server\MSSQL11.SQLEXPRESS\MSSQL\DATA\FourthDatabaseAlex_dat.mdf',
    SIZE = 10,
    MAXSIZE = 50,
    FILEGROWTH = 5 )
LOG ON
( NAME = FourthDatabaseAlex_log,
    FILENAME = 'C:\Program Files\Microsoft SQL Server\MSSQL11.SQLEXPRESS\MSSQL\DATA\FourthDatabaseAlex_dat_log.ldf',
    SIZE = 5MB,
    MAXSIZE = 25MB,
    FILEGROWTH = 5MB );
GO
	
USE FourthDatabaseAlex;
GO 

CREATE SCHEMA Lab4;
GO


CREATE TABLE Lab4.GROUPS (
	GROUPID INT PRIMARY KEY IDENTITY(1,1),
	GroupName VARCHAR(100) NOT NULL, 
	GroupLeader VARCHAR(100) NOT NULL,
	NumOfStudents INT,
	Tutor VARCHAR(100) NOT NULL,
)ON [PRIMARY];

GO


CREATE TABLE Lab4.STUDENTS (
	StudentID INT PRIMARY KEY IDENTITY(1,1),
	FullName VARCHAR(100) NOT NULL, 
	Age INT NOT NULL,
	PlaceOfBirth VARCHAR(100) NOT NULL,
	Budget BIT NOT NULL,  
	FourStatus BIT NOT NULL,
	ThreeStatus BIT NOT NULL,
	GROUPID INT ,
	CONSTRAINT FK_GroupId FOREIGN KEY (GROUPID) REFERENCES Lab4.GROUPS (GROUPID) ON DELETE CASCADE,
)ON [PRIMARY];
GO

INSERT INTO Lab4.GROUPS VALUES ('iu9-51', 'nika', 31, 'Skorb'), ('iu9-52', 'janush', 30, 'Dubashka'), ('iu9-53', 'dima', 0, 'Golub');

INSERT INTO Lab4.STUDENTS VALUES ('sasha', 19, 'Chelyabinsk', 1, 1, 0, (SELECT GROUPID from Lab4.GROUPS WHERE (GroupName = 'iu9-52'))), 
							('alena', 20, 'Novgorod', 1, 1, 0, (SELECT GROUPID from Lab4.GROUPS WHERE (GroupName = 'iu9-51'))),
							('filon', 20, 'Moscow', 0, 1, 1, (SELECT GROUPID from Lab4.GROUPS WHERE (GroupName = 'iu9-51'))),
							('vasya', 20, 'Moscow', 0, 1, 1, (SELECT GROUPID from Lab4.GROUPS WHERE (GroupName = 'iu9-51'))),
							('uma', 19, 'Derbent', 1, 1, 0, (SELECT GROUPID from Lab4.GROUPS WHERE (GroupName = 'iu9-52'))),
							('misha', 20, 'Ekaterinburg', 1, 0, 0, (SELECT GROUPID from Lab4.GROUPS WHERE (GroupName = 'iu9-52'))),
							('ilya', 20, 'Belgorod', 0, 1, 1, (SELECT GROUPID from Lab4.GROUPS WHERE (GroupName = 'iu9-53'))),
							('nastya', 19, 'Donbass', 1, 1, 0, (SELECT GROUPID from Lab4.GROUPS WHERE (GroupName = 'iu9-53'))),
							('natasha', 19, 'Moscow', 1, 1, 0, (SELECT GROUPID from Lab4.GROUPS WHERE (GroupName = 'iu9-52')));
GO

CREATE PROCEDURE Lab4.CursorFirst  
    @CursorFirstCursor CURSOR VARYING OUTPUT  
AS   
    SET NOCOUNT ON;  
    SET @CursorFirstCursor = CURSOR  
    FORWARD_ONLY STATIC LOCAL FOR  
      SELECT FullName, PlaceOfBirth  
      FROM Lab4.STUDENTS;  
    OPEN  @CursorFirstCursor;  
GO  


DECLARE @NewCursor CURSOR;  
EXECUTE Lab4.CursorFirst @CursorFirstCursor  = @NewCursor OUTPUT;  
FETCH NEXT FROM @NewCursor 
WHILE @@FETCH_STATUS = 0  
BEGIN  
	FETCH NEXT FROM @NewCursor  
END 
CLOSE @NewCursor
DEALLOCATE @NewCursor;  
GO  




CREATE FUNCTION Lab4.FirstFunction (@FourStatus BIT,  @ThreeStatus BIT, @Budget BIT)
RETURNS money
WITH SCHEMABINDING 
AS
BEGIN 
	DECLARE @Scolarship money;
	IF (@Budget = 0) 
	SET @Scolarship = 0 ;
	ELSE
		IF (@ThreeStatus = 1)
		SET @Scolarship = 0;
		ELSE
			IF (@FourStatus = 1 )
			SET @Scolarship = 2980.74
			ELSE
				SET @Scolarship = 3790.74
RETURN @Scolarship
END;
GO

ALTER PROCEDURE Lab4.CursorFirst  
    @CursorFirstCursor CURSOR VARYING OUTPUT  
AS   
    SET @CursorFirstCursor = CURSOR  
    SCROLL STATIC FOR  
      SELECT FullName, PlaceOfBirth, Lab4.FirstFunction(FourStatus, ThreeStatus, Budget) as Scolarship
      FROM Lab4.STUDENTS;  
    OPEN  @CursorFirstCursor;  
GO  

DECLARE @MyCursor CURSOR;  
EXEC Lab4.CursorFirst @CursorFirstCursor  = @MyCursor OUTPUT;  
FETCH NEXT FROM @MyCursor 
WHILE (@@FETCH_STATUS = 0) 
BEGIN;  
     FETCH NEXT FROM @MyCursor;  
END;  
CLOSE @MyCursor;  
DEALLOCATE @MyCursor;  
GO  

CREATE FUNCTION Lab4.SecondFunction (@PlaceOfBirth VARCHAR(100), @Scolarship money)
RETURNS BIT
WITH SCHEMABINDING 
AS
BEGIN 
	DECLARE @LUCKY BIT;
	IF (@PlaceOfBirth = 'Moscow' AND @Scolarship > 0)
		SET @LUCKY= 1;
	ELSE 
		SET @LUCKY= 0 ;
RETURN @LUCKY
END;
GO


CREATE PROCEDURE Lab4.CursorSecond  
AS   
	DECLARE @FullName VARCHAR(100), @PlaceOfBirth VARCHAR(100), @Scolarship money,  @CursorSecondCursor CURSOR ; 
	EXEC Lab4.CursorFirst @CursorFirstCursor  = @CursorSecondCursor OUTPUT;  
	FETCH NEXT FROM @CursorSecondCursor
	INTO @FullName, @PlaceOfBirth, @Scolarship;
	WHILE (@@FETCH_STATUS = 0) 
	BEGIN;  
		IF (Lab4.SecondFunction(@PlaceOfBirth, @Scolarship) = 1)
			PRINT 'FullName: ' + @FullName
		FETCH NEXT FROM @CursorSecondCursor
		INTO @FullName, @PlaceOfBirth, @Scolarship; 
	END;  
	CLOSE @CursorSecondCursor;  
	DEALLOCATE @CursorSecondCursor;
GO  

EXECUTE Lab4.CursorSecond;
GO

CREATE FUNCTION Lab4.TableFunction (@Age INT)
RETURNS TABLE 
AS
RETURN 
(	SELECT FullName, PlaceOfBirth, Lab4.FirstFunction(FourStatus, ThreeStatus, Budget) as Scolarship
    FROM Lab4.STUDENTS
	WHERE Age = @Age
);
GO

ALTER PROCEDURE Lab4.CursorFirst  
    @CursorFirstCursor CURSOR VARYING OUTPUT, 
	@Age INT 
AS   
    SET @CursorFirstCursor = CURSOR  
    SCROLL STATIC FOR  
      SELECT * FROM Lab4.TableFunction(@Age);  
    OPEN  @CursorFirstCursor;  
GO  

DECLARE @MyCursor CURSOR;  
EXEC Lab4.CursorFirst @CursorFirstCursor  = @MyCursor OUTPUT, @Age = 20;  
FETCH NEXT FROM @MyCursor 
WHILE (@@FETCH_STATUS = 0) 
BEGIN;  
     FETCH NEXT FROM @MyCursor;  
END;  
CLOSE @MyCursor;  
DEALLOCATE @MyCursor;  
GO 