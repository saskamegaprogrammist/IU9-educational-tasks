USE DatabaseAlex13_2;
GO 

CREATE TABLE GROUPS_15 (
	GROUPID INT PRIMARY KEY,
	GroupName VARCHAR(100) NOT NULL, 
	Tutor VARCHAR(100) NOT NULL,
)ON [PRIMARY];

GO


DROP TRIGGER Groups_Delete;

CREATE TRIGGER Groups_Delete ON GROUPS_15
INSTEAD OF DELETE
AS 
BEGIN
	DELETE FROM DatabaseAlex13_1.dbo.STUDENTS_15
	WHERE GROUPID IN (
		SELECT GROUPID from deleted)
	DELETE FROM GROUPS_15
		FROM GROUPS_15
		JOIN deleted as d
		ON GROUPS_15.GROUPID = d.GROUPID
END;
GO


CREATE TRIGGER Groups_Update ON GROUPS_15
INSTEAD OF Update
AS 
BEGIN
	IF UPDATE(GROUPID)
		THROW 51000, 'Can not update this field', 1;  
		ELSE
		UPDATE GROUPS_15
		SET GROUPS_15.GroupName = COALESCE(i.GroupName, GROUPS_15.GroupName),
				GROUPS_15.Tutor = COALESCE(i.Tutor, GROUPS_15.Tutor)
		FROM GROUPS_15
		JOIN inserted as i
		ON GROUPS_15.GROUPID = i.GROUPID
END;
GO

DELETE FROM GROUPS_15 
WHERE GROUPID = 53

INSERT INTO GROUPS_15 (GROUPID, GroupName, Tutor) VALUES
	(52, 'iu9-52', 'dubanov'), (53, 'iu9-53', 'golubkov')


SELECT * FROM GROUPS_15 ;
GO

UPDATE GROUPS_15 
SET Tutor = 'kek'
WHERE Tutor = 'dubanov'
