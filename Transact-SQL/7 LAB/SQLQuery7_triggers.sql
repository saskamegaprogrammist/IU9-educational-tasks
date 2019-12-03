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

CREATE FUNCTION MusicApp.GetFileIdByFileName (@FileName VARCHAR(500))
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


--DROP VIEW MusicApp.FileAndComposition;
--GO
--CREATE VIEW MusicApp.FileAndComposition WITH SCHEMABINDING  AS  
--SELECT COMPOSITION.FullName FROM MusicApp.COMPOSITION
--INNER JOIN MusicApp.FILEITEM ON FILEITEM.CompositionID = COMPOSITION.CompositionID
--GO

--SELECT * FROM MusicApp.FileAndComposition;
--GO