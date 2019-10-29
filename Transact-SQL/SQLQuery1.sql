USE master;
GO
/*
SELECT TABLE_NAME 
FROM master.INFORMATION_SCHEMA.TABLES 
WHERE TABLE_TYPE = 'BASE TABLE'
*/
IF DB_ID('FirstDatabaseAlex') IS NOT NULL
DROP DATABASE FirstDatabaseAlex;

CREATE DATABASE FirstDatabaseAlex
ON PRIMARY
( NAME = FirstDatabaseAlex_dat,
    FILENAME = 'C:\Program Files\Microsoft SQL Server\MSSQL11.SQLEXPRESS\MSSQL\DATA\FirstDatabaseAlex_dat.mdf',
    SIZE = 10,
    MAXSIZE = 50,
    FILEGROWTH = 5 )
LOG ON
( NAME = FirstDatabaseAlex_log,
    FILENAME = 'C:\Program Files\Microsoft SQL Server\MSSQL11.SQLEXPRESS\MSSQL\DATA\FirstDatabaseAlex_log.ldf',
    SIZE = 5MB,
    MAXSIZE = 25MB,
    FILEGROWTH = 5MB );
GO
	
USE FirstDatabaseAlex;
GO 


CREATE TABLE COMPOSITION (
	CompositionID INT IDENTITY (1, 1),
	FullTitle VARCHAR(100) NOT NULL
)ON [PRIMARY];
GO


ALTER DATABASE FirstDatabaseAlex
ADD FILEGROUP TestFilegroup;
GO

ALTER DATABASE FirstDatabaseAlex
ADD FILE
(
    NAME = FirstDatabaseAlex_dat_2,
    FILENAME = 'C:\Program Files\Microsoft SQL Server\MSSQL11.SQLEXPRESS\MSSQL\DATA\FirstDatabaseAlex_dat_2.ndf',
    SIZE = 5MB,
    MAXSIZE = 100MB,
    FILEGROWTH = 5MB
)
TO FILEGROUP TestFilegroup;
GO

ALTER DATABASE FirstDatabaseAlex
MODIFY FILEGROUP TestFilegroup DEFAULT;
GO


CREATE TABLE INSTRUMENT (
	InstrumentName VARCHAR(50) ,
	Section VARCHAR(100) NOT NULL
) ;
GO	

CREATE CLUSTERED INDEX IX_INSTRUMENT_InstrumentName 
    ON INSTRUMENT (InstrumentName) 
	ON [PRIMARY];   
GO  


ALTER DATABASE FirstDatabaseAlex
MODIFY FILEGROUP [PRIMARY] DEFAULT;
GO


ALTER DATABASE FirstDatabaseAlex
REMOVE FILE FirstDatabaseAlex_dat_2;
GO

ALTER DATABASE FirstDatabaseAlex
REMOVE FILEGROUP TestFilegroup;
GO




CREATE SCHEMA AlexSchema;
GO

ALTER SCHEMA AlexSchema TRANSFER COMPOSITION;  
GO  

DROP TABLE AlexSchema.COMPOSITION;  
DROP SCHEMA AlexSchema;  
GO  
