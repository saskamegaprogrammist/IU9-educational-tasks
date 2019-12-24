USE DatabaseAlex13_1;
GO 

DROP TABLE STUDENTS_Info;
CREATE TABLE STUDENTS_Info (
	StudentID INT PRIMARY KEY ,
	FullName VARCHAR(100) NOT NULL, 
	Age INT NOT NULL,
	PlaceOfBirth VARCHAR(100) NOT NULL,
)ON [PRIMARY];
GO

DROP VIEW STUDENTS_Full;
GO

CREATE VIEW STUDENTS_Full AS
	SELECT f.StudentId, f.FullName, f.Age, f.PlaceOfBirth, s.GROUPID, s.Scolarship
	  FROM DatabaseAlex13_1..STUDENTS_Info f
	  JOIN DatabaseAlex13_2..STUDENTS_Group s
	  ON f.StudentId = s.StudentId;
GO


CREATE TRIGGER FullInsert ON STUDENTS_Full
INSTEAD OF INSERT 
AS 
BEGIN
	IF 	(SELECT COUNT(*) FROM STUDENTS_Full sf
			INNER JOIN inserted i ON sf.StudentID = i.StudentID
			) <> 0
			THROW 51000, 'Student exists', 1;
	ELSE 
	INSERT INTO DatabaseAlex13_2.dbo.STUDENTS_Group (StudentID, GROUPID, Scolarship)
		SELECT
				StudentID, GROUPID, Scolarship
			FROM
				inserted 
	INSERT INTO DatabaseAlex13_1.dbo.STUDENTS_Info (StudentID, FullName, Age, PlaceOfBirth)
		SELECT
			StudentID, FullName, Age, PlaceOfBirth
		FROM
			inserted 
END;
GO

--INSERT INTO STUDENTS_Info VALUES (1, 'sasha', 19, 'Chelyabinsk'),
--							(2,'alena', 20, 'Novgorod'),
--							(3, 'filon', 20, 'Moscow'),
--							(4, 'vasya', 20, 'Moscow'),
--							(5, 'uma', 19, 'Derbent'),
--							(6, 'misha', 20, 'Ekaterinburg'),
--							(7, 'ilya', 20, 'Belgorod'),
--							(8, 'nastya', 19, 'Donbass')
--GO

INSERT INTO STUDENTS_Full (StudentID, FullName, Age, PlaceOfBirth, GROUPID, Scolarship) VALUES
	(1, 'sasha', 19, 'Chelyabinsk', 52, 0), (2,'alena', 20, 'Novgorod', 51, 4000),
	(3, 'filon', 20, 'Moscow', 51, 2000), (4, 'vasya', 20, 'Moscow', 51, 0)
GO

DROP TRIGGER FullUpd
CREATE TRIGGER FullUpd ON STUDENTS_Full
INSTEAD OF UPDATE
AS 
BEGIN
	IF 	(SELECT COUNT(*) FROM STUDENTS_Full sf
			INNER JOIN inserted i ON sf.StudentID = i.StudentID
			) <> (SELECT COUNT(*) FROM inserted)
			THROW 51000, 'Student dont exist', 1;
	ELSE 
		IF UPDATE(StudentID) OR UPDATE(FullName)
		THROW 51000, 'Can not update this fields', 1;  
		ELSE
		UPDATE DatabaseAlex13_2.dbo.STUDENTS_Group
		SET DatabaseAlex13_2.dbo.STUDENTS_Group.GROUPID = COALESCE(i.GROUPID, DatabaseAlex13_2.dbo.STUDENTS_Group.GROUPID),
				DatabaseAlex13_2.dbo.STUDENTS_Group.Scolarship = COALESCE(i.Scolarship,DatabaseAlex13_2.dbo.STUDENTS_Group.Scolarship)
		FROM DatabaseAlex13_2.dbo.STUDENTS_Group
		JOIN inserted as i
		ON DatabaseAlex13_2.dbo.STUDENTS_Group.StudentID = i.StudentID

		UPDATE DatabaseAlex13_1.dbo.STUDENTS_Info
		SET DatabaseAlex13_1.dbo.STUDENTS_Info.PlaceOfBirth = COALESCE(i.PlaceOfBirth, DatabaseAlex13_1.dbo.STUDENTS_Info.PlaceOfBirth),
				DatabaseAlex13_1.dbo.STUDENTS_Info.Age = COALESCE(i.Age,DatabaseAlex13_1.dbo.STUDENTS_Info.Age)
		FROM DatabaseAlex13_1.dbo.STUDENTS_Info
		JOIN inserted as i
		ON DatabaseAlex13_1.dbo.STUDENTS_Info.StudentID = i.StudentID
END;
GO

SELECT * FROM STUDENTS_Full;
GO
UPDATE STUDENTS_Full
SET Scolarship=4000
WHERE PlaceOfBirth='Moscow'
GO
SELECT * FROM STUDENTS_Full;
GO

DROP TRIGGER FullDelete

CREATE TRIGGER FullDelete ON STUDENTS_Full
INSTEAD OF DELETE
AS 
BEGIN
	IF 	(SELECT COUNT(*) FROM STUDENTS_Full sf
			INNER JOIN deleted i ON sf.StudentID = i.StudentID
			) <> (SELECT COUNT(*) FROM deleted)
			THROW 51000, 'Student dont exist', 1;
	ELSE 
		DELETE FROM DatabaseAlex13_2.dbo.STUDENTS_Group
		FROM DatabaseAlex13_2.dbo.STUDENTS_Group
		JOIN deleted as d
		ON DatabaseAlex13_2.dbo.STUDENTS_Group.StudentID = d.StudentID
		
		DELETE FROM DatabaseAlex13_1.dbo.STUDENTS_Info
		FROM DatabaseAlex13_1.dbo.STUDENTS_Info
		JOIN deleted as d
		ON DatabaseAlex13_1.dbo.STUDENTS_Info.StudentID = d.StudentID
END;
GO


SELECT * FROM STUDENTS_Full;
GO
DELETE FROM STUDENTS_Full
WHERE PlaceOfBirth='Chelyabinsk'
GO
SELECT * FROM STUDENTS_Full;
GO