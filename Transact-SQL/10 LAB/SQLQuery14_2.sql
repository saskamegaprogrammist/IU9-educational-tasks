USE DatabaseAlex13_2;
GO 

DROP TABLE STUDENTS_Group;
CREATE TABLE STUDENTS_Group (
	StudentID INT PRIMARY KEY,
	GROUPID INT,
	Scolarship INT
) ON [PRIMARY];
GO

DROP VIEW STUDENTS_Full;
GO

CREATE VIEW STUDENTS_Full AS
	SELECT f.StudentId, f.FullName, f.Age, f.PlaceOfBirth, s.GROUPID, s.Scolarship
	  FROM DatabaseAlex13_1..STUDENTS_Info f
	  JOIN DatabaseAlex13_2..STUDENTS_Group s
	  ON f.StudentID = s.StudentID;
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

INSERT INTO STUDENTS_Full (StudentID, FullName, Age, PlaceOfBirth, GROUPID, Scolarship) VALUES
	(43, 'alex', 21, 'moscow', 53, 2000), (44, 'alexx', 22, 'moscow', 53, 2000)


SELECT * FROM STUDENTS_Full;
GO
		
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
