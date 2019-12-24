CREATE TRIGGER MusicApp.FILEDataType ON MusicApp.FILEITEM
AFTER INSERT 
AS 
BEGIN
	INSERT INTO MusicApp.AUDIO (FileName)
	SELECT (FileName) FROM inserted
	WHERE DataType = 'AUDIO';
	INSERT INTO MusicApp.NOTES (FileName)
	SELECT (FileName) FROM inserted
	WHERE DataType = 'NOTES';
	INSERT INTO MusicApp.TABS (FileName)
	SELECT (FileName) FROM inserted
	WHERE DataType = 'TABS';
END;
GO

CREATE FUNCTION MusicApp.GetCompositionIdByName (@FileName VARCHAR(500))
RETURNS INT
WITH SCHEMABINDING 
AS
BEGIN 
	DECLARE @ID INT;
	SELECT @ID = CompositionID 
	FROM MusicApp.COMPOSITION
	WHERE FullName = @FileName
RETURN @ID
END;
GO


CREATE FUNCTION MusicApp.GetComposerIdByName (@ComposerName VARCHAR(500))
RETURNS INT
WITH SCHEMABINDING 
AS
BEGIN 
	DECLARE @ID INT;
	SELECT @ID = ComposerID 
	FROM MusicApp.COMPOSER
	WHERE ComposerFullName = @ComposerName
RETURN @ID
END;
GO

DROP VIEW MusicApp.FileAndComposition

CREATE VIEW MusicApp.FileAndComposition WITH SCHEMABINDING  AS  
SELECT COMPOSITION.FullName as Composition, FILEITEM.FileName as FileInfo FROM MusicApp.COMPOSITION
INNER JOIN MusicApp.FILEITEM ON FILEITEM.CompositionID = COMPOSITION.CompositionID
GO

 
CREATE TRIGGER MusicApp.CheckIsFor ON MusicApp.IS_FOR
INSTEAD OF INSERT 
AS 
BEGIN
	IF (SELECT COUNT(*) FROM inserted
		WHERE CompositionID = NULL OR InstrumentName = '' OR InstrumentName = NULL) <> 0
		THROW 51000, 'Can not insert empty values.', 1;
	ELSE 	 
		IF (SELECT COUNT(*) FROM COMPOSITION 
		JOIN (SELECT CompositionID as cid FROM inserted) as ins 
		ON COMPOSITION.CompositionID = ins.cid) <> 
			(SELECT COUNT(*) FROM inserted)
			THROW 51000, 'The composition does not exist.', 1; 
		ELSE
			IF (SELECT COUNT(*) FROM INSTRUMENT 
			JOIN (SELECT InstrumentName FROM inserted) as i 
			ON INSTRUMENT.InstrumentName = i.InstrumentName) <> 
				(SELECT COUNT(*) FROM inserted)
				THROW 51000, 'The instrument does not exist.', 1;
			ELSE
				INSERT INTO MusicApp.IS_FOR 
				SELECT * FROM inserted;
END;
GO

CREATE TRIGGER MusicApp.CheckComposed ON MusicApp.COMPOSED
INSTEAD OF INSERT 
AS 
BEGIN
	IF (SELECT COUNT(*) FROM inserted
		WHERE CompositionID = NULL OR ComposerID = NULL) <> 0
		THROW 51000, 'Can not insert empty values.', 1;
	ELSE 	 
		IF (SELECT COUNT(*) FROM COMPOSITION 
		JOIN (SELECT CompositionID as cid FROM inserted) as ins 
		ON COMPOSITION.CompositionID = ins.cid) <> 
			(SELECT COUNT(*) FROM inserted)
			THROW 51000, 'The composition does not exist.', 1; 
		ELSE
			IF (SELECT COUNT(*) FROM COMPOSER
			JOIN (SELECT ComposerID FROM inserted) as i 
			ON COMPOSER.ComposerID = i.ComposerID) <> 
				(SELECT COUNT(*) FROM inserted)
				THROW 51000, 'The composer does not exist.', 1;
			ELSE
				INSERT INTO MusicApp.COMPOSED
				SELECT * FROM inserted;
END;
GO

CREATE TRIGGER MusicApp.CheckComposedUpd ON MusicApp.COMPOSED
INSTEAD OF UPDATE
AS 
THROW 51000, 'Can not update this table.', 1;
GO

CREATE TRIGGER MusicApp.CheckIsForUpd ON MusicApp.IS_FOR
INSTEAD OF UPDATE
AS 
THROW 51000, 'Can not update this table.', 1;
GO

CREATE TRIGGER MusicApp.CheckFileIns ON MusicApp.FILEITEM
INSTEAD OF INSERT 
AS 
BEGIN
	IF (SELECT COUNT(*) FROM inserted
		WHERE CompositionID = NULL OR ContributorNick = NULL) <> 0
		THROW 51000, 'Can not insert empty values.', 1;
	ELSE 	 
		IF (SELECT COUNT(*) FROM COMPOSITION 
		JOIN (SELECT CompositionID as cid FROM inserted) as ins 
		ON COMPOSITION.CompositionID = ins.cid) <> 
			(SELECT COUNT(*) FROM inserted)
			THROW 51000, 'The composition does not exist.', 1; 
		ELSE
			IF (SELECT COUNT(*) FROM CONTRIBUTOR
			JOIN (SELECT ContributorNick FROM inserted) as i 
			ON CONTRIBUTOR.ContributorNick = i.ContributorNick) <> 
				(SELECT COUNT(*) FROM inserted)
				THROW 51000, 'The contributor does not exist.', 1;
			ELSE
				INSERT INTO MusicApp.FILEITEM
				SELECT * FROM inserted;
END;
GO

DROP TRIGGER MusicApp.CheckFileUpd 
CREATE TRIGGER MusicApp.CheckFileUpd ON MusicApp.FILEITEM
INSTEAD OF UPDATE
AS 
BEGIN
	IF (SELECT COUNT(*) FROM inserted
		WHERE CompositionID = NULL OR ContributorNick = NULL) <> 0
		THROW 51000, 'Can not insert empty values.', 1;
	ELSE 	 
		IF (SELECT COUNT(*) FROM COMPOSITION 
		JOIN (SELECT CompositionID as cid FROM inserted) as ins 
		ON COMPOSITION.CompositionID = ins.cid) <> 
			(SELECT COUNT(*) FROM inserted)
			THROW 51000, 'The composition does not exist.', 1; 
		ELSE
			IF (SELECT COUNT(*) FROM CONTRIBUTOR
			JOIN (SELECT ContributorNick FROM inserted) as i 
			ON CONTRIBUTOR.ContributorNick = i.ContributorNick) <> 
				(SELECT COUNT(*) FROM inserted)
				THROW 51000, 'The contributor does not exist.', 1;
			ELSE
				IF (SELECT COUNT(*) FROM FILEITEM
				JOIN inserted ON
					inserted.FileName = FILEITEM.FileName AND
					inserted.CompositionID = FILEITEM.CompositionID AND
					inserted.ContributorNick = FILEITEM.ContributorNick) <>
					(SELECT COUNT(*) FROM inserted)
				THROW 51000, 'You can not update filenames composition or contributor', 1;
				ELSE
					UPDATE FILEITEM
					SET Authorship = inserted.Authorship,
					 DownloadsNumber = inserted.DownloadsNumber, 
					 DataType = inserted.DataType
					 FROM inserted WHERE inserted.CompositionID = FILEITEM.CompositionID
END;
GO


CREATE INDEX comp_fullname ON  MusicApp.COMPOSITION (FullName);
CREATE INDEX composer_fullname ON  MusicApp.COMPOSER (ComposerFullName);
CREATE INDEX file_comp ON  MusicApp.FILEITEM (CompositionID);
