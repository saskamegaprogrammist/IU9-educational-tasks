USE master;
GO

IF DB_ID('DatabaseAlex7') IS NOT NULL
DROP DATABASE DatabaseAlex7;

CREATE DATABASE DatabaseAlex7
ON PRIMARY
( NAME = DatabaseAlex7_dat,
    FILENAME = 'C:\Program Files\Microsoft SQL Server\MSSQL11.SQLEXPRESS\MSSQL\DATA\DatabaseAlex7_dat.mdf',
    SIZE = 10,
    MAXSIZE = 50,
    FILEGROWTH = 5 )
LOG ON
( NAME = DatabaseAlex7_log,
    FILENAME = 'C:\Program Files\Microsoft SQL Server\MSSQL11.SQLEXPRESS\MSSQL\DATA\DatabaseAlex7_dat_log.ldf',
    SIZE = 5MB,
    MAXSIZE = 25MB,
    FILEGROWTH = 5MB );
GO
	
USE DatabaseAlex7;
GO 

CREATE SCHEMA MusicApp;
GO


CREATE TABLE MusicApp.COMPOSITION (
	CompositionID INT PRIMARY KEY NOT NULL IDENTITY(1,1),
	FullName VARCHAR(50) NOT NULL,
)ON [PRIMARY];


CREATE TABLE MusicApp.INSTRUMENT (
	InstrumentName VARCHAR(50) PRIMARY KEY NOT NULL,
	Section VARCHAR(50) NOT NULL,
)ON [PRIMARY];

CREATE TABLE MusicApp.IS_FOR ( --when inserting a composition, should provide an instrument, but if deleting instument, setting null
	InstrumentName VARCHAR(50),
	CompositionID INT NOT NULL ,
	CONSTRAINT FK_CompositionIDIsFor FOREIGN KEY (CompositionID)
			 REFERENCES MusicApp.COMPOSITION (CompositionID) ON DELETE CASCADE, --can't update instrument's composition
	CONSTRAINT FK_InstrumentNameIsFor FOREIGN KEY (InstrumentName)
			 REFERENCES MusicApp.INSTRUMENT (InstrumentName) ON DELETE SET NULL , --shouldn't update rows in this table, only insert/delete
)

CREATE TABLE MusicApp.COMPOSER (
	ComposerID INT PRIMARY KEY NOT NULL IDENTITY(1,1),
	ComposerFullName VARCHAR(100) NOT NULL,
	DateOfBirth DATE NOT NULL, 
	Style VARCHAR(50) NOT NULL,
	CONSTRAINT ComposerFullName CHECK (ComposerFullName LIKE '% %'),
)ON [PRIMARY];


CREATE TABLE MusicApp.COMPOSED (
	ComposerID INT NOT NULL,
	CompositionID INT NOT NULL ,
	CONSTRAINT FK_CompositionIDComposed FOREIGN KEY (CompositionID)
			 REFERENCES MusicApp.COMPOSITION (CompositionID) ON DELETE CASCADE, --can't update composer's composition
	CONSTRAINT FK_ComposerIDComposed FOREIGN KEY (ComposerID)
			 REFERENCES MusicApp.COMPOSER (ComposerID), -- can't delete composer if he has a composition, shouldn't update rows in this table, only insert/delete
)

CREATE TABLE MusicApp.CONTRIBUTOR (
	ContributorNick VARCHAR(100) PRIMARY KEY NOT NULL,
	ContributorFullName VARCHAR(100) NOT NULL,
	DateRegistered DATE NOT NULL, 
	Profession VARCHAR(100),
	CONSTRAINT ContributorFullName CHECK (ContributorFullName LIKE '% %'),
)ON [PRIMARY];

CREATE TABLE MusicApp.FILEITEM (
	FileName VARCHAR(500) PRIMARY KEY NOT NULL,
	CompositionID INT NOT NULL,
	ContributorNick VARCHAR(100) NOT NULL,
	Authorship BIT DEFAULT 0,
	DownloadsNumber INT DEFAULT 0,	
	DataType VARCHAR(20) NOT NULL,
	CONSTRAINT FK_CompositionID FOREIGN KEY (CompositionID)
			 REFERENCES MusicApp.COMPOSITION (CompositionID) , --can't delete composition if it has files, can't update file's composition
	CONSTRAINT FK_ContributorNick FOREIGN KEY (ContributorNick) 
			REFERENCES MusicApp.CONTRIBUTOR (ContributorNick) , --can't delete contributor if it has files, can't update file's contibutor
	CONSTRAINT DataType CHECK (DataType IN ('NOTES','TABS', 'AUDIO')),
)ON [PRIMARY];

CREATE TABLE MusicApp.NOTES (
	FileName VARCHAR(500) PRIMARY KEY NOT NULL,
	DatePublished DATE, 
	Press VARCHAR(100),
	CONSTRAINT FK_FileNameNotes FOREIGN KEY (FileName) 
			REFERENCES MusicApp.FILEITEM (FileName) ON DELETE CASCADE, --can't update surrogate key
)ON [PRIMARY];


CREATE TABLE MusicApp.TABS (
	FileName VARCHAR(500) PRIMARY KEY NOT NULL,
	Difficulty VARCHAR(20) DEFAULT 'EASY',
	TabsKey VARCHAR(10),
	CONSTRAINT FK_FileNameTabs FOREIGN KEY (FileName) 
			REFERENCES MusicApp.FILEITEM (FileName) ON DELETE CASCADE, --can't update surrogate key
	CONSTRAINT Difficulty CHECK (Difficulty IN ('HARD','MEDIUM', 'EASY')),
)ON [PRIMARY];


CREATE TABLE MusicApp.AUDIO (
	FileName VARCHAR(500) PRIMARY KEY NOT NULL,
	Length TIME DEFAULT '00:00:00', 
	Performer VARCHAR(100),
	CONSTRAINT FK_FileNameAudio FOREIGN KEY (FileName) 
			REFERENCES MusicApp.FILEITEM (FileName) ON DELETE CASCADE, --can't update surrogate key
	CONSTRAINT Performer CHECK (Performer LIKE '% %'),
)ON [PRIMARY];


GO


SET TRANSACTION ISOLATION LEVEL SNAPSHOT;
GO

