USE DatabaseAlex7;
GO 

INSERT INTO MusicApp.CONTRIBUTOR VALUES
('alexxxx', 'Spiridonova Alex', CONVERT (date, CURRENT_TIMESTAMP), 'programmer');

SELECT * FROM MusicApp.CONTRIBUTOR;
GO

BEGIN TRANSACTION;
INSERT INTO MusicApp.COMPOSITION(FullName) VALUES
('LiberTango');
INSERT INTO MusicApp.FILEITEM (FileName, CompositionID, ContributorNick, DataType) VALUES
('libertango.wav', @@IDENTITY, 'alex', 'AUDIO');
COMMIT TRANSACTION;
GO

SELECT * FROM MusicApp.COMPOSITION;
SELECT * FROM MusicApp.FILEITEM;
SELECT * FROM MusicApp.AUDIO;
GO

INSERT INTO MusicApp.FILEITEM (FileName, CompositionID, ContributorNick, DataType) VALUES
('libertango_1.txt', MusicApp.GetCompositionIdByName('LiberTango'), 'alex', 'TABS');

INSERT INTO MusicApp.INSTRUMENT VALUES 
('flute', 'brass'), ('guitar', 'folk');

INSERT INTO MusicApp.COMPOSER (ComposerFullName, DateOfBirth, Style) VALUES 
('Petr Chaikovsky', CONVERT (date, '12-12-1844'), 'romantism'), 
('Modest Musorgsky', CONVERT (date, '14-02-1839'), 'romantism');

SELECT * FROM MusicApp.INSTRUMENT;
SELECT * FROM MusicApp.COMPOSER;
GO

SELECT ComposerID FROM MusicApp.COMPOSER
WHERE ComposerFullName = 'sfsdf sdf'

INSERT INTO MusicApp.IS_FOR VALUES ('flute', 1)
INSERT INTO MusicApp.IS_FOR VALUES ('flute', MusicApp.GetCompositionIdByName('LiberTangooo'))

SELECT * FROM MusicApp.IS_FOR;

INSERT INTO MusicApp.COMPOSED VALUES (1, 1)
INSERT INTO MusicApp.COMPOSED VALUES (11,0)

SELECT * FROM MusicApp.COMPOSED;

UPDATE MusicApp.COMPOSED SET CompositionID=5 WHERE ComposerID=1
UPDATE MusicApp.IS_FOR SET InstrumentName='kek' WHERE CompositionID=1

INSERT INTO MusicApp.CONTRIBUTOR VALUES
('alexxx', 'Welch Alex', CONVERT (date, CURRENT_TIMESTAMP), 'flutist');

SELECT * FROM MusicApp.CONTRIBUTOR;
GO

BEGIN TRANSACTION;
INSERT INTO MusicApp.COMPOSITION(FullName) VALUES
('Train');
INSERT INTO MusicApp.FILEITEM (FileName, CompositionID, ContributorNick, DataType) VALUES
('train.pdf', @@IDENTITY, 'alexxx', 'NOTES');
COMMIT TRANSACTION;
GO

SELECT * FROM MusicApp.NOTES;
GO

INSERT INTO MusicApp.FILEITEM (FileName, CompositionID, ContributorNick, DataType) VALUES
('train1.pdf', MusicApp.GetCompositionIdByName('Train'), 'alexxx', 'NOTES');

UPDATE MusicApp.FILEITEM
SET FileName = 'train1.pdf', DataType='NOTES' WHERE CompositionID=MusicApp.GetCompositionIdByName('Train')

UPDATE MusicApp.NOTES
SET Press = 'sdfsdf'
WHERE FileName= 'train1.pdf';

DELETE FROM MusicApp.NOTES
WHERE PRESS = 'sdfsdf'

DELETE FROM MusicApp.FILEITEM
WHERE FileName = 'train.pdf'

SELECT * FROM MusicApp.NOTES

BEGIN TRANSACTION;
INSERT INTO MusicApp.COMPOSITION(FullName) VALUES
('OverTheLove');
INSERT INTO MusicApp.FILEITEM (FileName, CompositionID, ContributorNick, DataType) VALUES
('OverTheLove.txt', @@IDENTITY, 'alexxx', 'TABS');
COMMIT TRANSACTION;
GO

INSERT INTO MusicApp.COMPOSER (ComposerFullName, DateOfBirth, Style) VALUES 
('Wolfgang Mozart', CONVERT (date, '11-01-1640'), 'classicism');

INSERT INTO MusicApp.COMPOSED VALUES (MusicApp.GetComposerIdByName('Paul Epworth'),
	MusicApp.GetCompositionIdByName('BreathOfTheLife'));

SELECT * FROM MusicApp.FILEITEM

DELETE FROM MusicApp.COMPOSITION WHERE CompositionID=3;

SELECT DISTINCT ContributorNick FROM MusicApp.FILEITEM;

SELECT * FROM  MusicApp.FileAndComposition;

INSERT INTO MusicApp.INSTRUMENT VALUES 
('electropiano', 'piano'), ('contrabass', 'strings');

INSERT INTO MusicApp.IS_FOR VALUES ('flute', MusicApp.GetCompositionIdByName('Train'))

SELECT * FROM  MusicApp.COMPOSED;

SELECT  MusicApp.COMPOSITION.CompositionID, FullName, COUNT(InstrumentName) as c  FROM MusicApp.COMPOSITION
LEFT JOIN MusicApp.IS_FOR ON COMPOSITION.CompositionID = IS_FOR.CompositionID
GROUP BY MusicApp.COMPOSITION.CompositionID, FullName

SELECT * FROM MusicApp.COMPOSITION
FULL OUTER JOIN MusicApp.IS_FOR ON COMPOSITION.CompositionID = IS_FOR.CompositionID
FULL OUTER JOIN MusicApp.COMPOSED ON COMPOSITION.CompositionID = COMPOSED.CompositionID

SELECT * FROM MusicApp.COMPOSITION
FULL OUTER JOIN MusicApp.IS_FOR ON COMPOSITION.CompositionID = IS_FOR.CompositionID

SELECT COMPOSITION.CompositionID FROM MusicApp.COMPOSITION
JOIN MusicApp.IS_FOR ON COMPOSITION.CompositionID = IS_FOR.CompositionID 
JOIN MusicApp.COMPOSED ON COMPOSITION.CompositionID = COMPOSED.CompositionID

SELECT * FROM MusicApp.COMPOSITION
RIGHT JOIN MusicApp.IS_FOR ON COMPOSITION.CompositionID = IS_FOR.CompositionID

SELECT DISTINCT MusicApp.FILEITEM.FileName, DATATYPE, DatePublished, Difficulty, Performer
FROM MusicApp.FILEITEM
LEFT JOIN MusicApp.AUDIO ON AUDIO.FileName = AUDIO.FileName
LEFT JOIN MusicApp.NOTES ON NOTES.FileName = NOTES.FileName
LEFT JOIN MusicApp.TABS ON TABS.FileName = TABS.FileName


UPDATE MusicApp.AUDIO
SET Performer='Florence and The Machine'
WHERE FileName='BreathOfTheLife.wav';

SELECT * FROM  MusicApp.AUDIO
WHERE Performer IS NULL;

INSERT INTO MusicApp.CONTRIBUTOR VALUES
('jason', 'Second User', CONVERT (date, CURRENT_TIMESTAMP), 'computer programmer');

SELECT * FROM  MusicApp.CONTRIBUTOR
WHERE Profession LIKE '%programmer'

SELECT * FROM  MusicApp.COMPOSITION
WHERE FullName LIKE LOWER('%train%');

SELECT DISTINCT Style FROM MusicApp.COMPOSER
WHERE Style IN ('indi', 'romantism')

SELECT  * FROM  MusicApp.CONTRIBUTOR
WHERE DateRegistered BETWEEN '23-12-2019' AND CONVERT (date, CURRENT_TIMESTAMP)

SELECT * FROM MusicApp.FILEITEM WHERE
EXISTS (
	SELECT * FROM MusicApp.TABS
		WHERE Difficulty <> 'EASY')

SELECT * FROM MusicApp.COMPOSER ORDER BY
DateOfBirth;

SELECT * FROM MusicApp.CONTRIBUTOR ORDER BY
DateRegistered DESC;

UPDATE MusicApp.FILEITEM SET 
DownloadsNumber = 4, DataType = 'NOTES'
WHERE CompositionID IN
	(SELECT CompositionID FROM
		MusicApp.COMPOSED
		WHERE ComposerID=MusicApp.GetComposerIdByName('Paul Epworth'))

SELECT * FROM MusicApp.NOTES ORDER BY
FileName


BEGIN TRANSACTION;
INSERT INTO MusicApp.COMPOSITION(FullName) VALUES
('FoundWhatIveBeenLookingFor');
INSERT INTO MusicApp.FILEITEM (FileName, CompositionID, ContributorNick, DataType) VALUES
('FoundWhatIveBeenLookingFor.txt', @@IDENTITY, 'alexxx', 'sdfsdf');
COMMIT TRANSACTION;
GO

UPDATE MusicApp.FILEITEM SET 
DownloadsNumber = 4, DataType = 'AUDIO'
WHERE CompositionID=4

--SELECT DownloadsNumber, FileName FROM MusicApp.FILEITEM
--GROUP BY DownloadsNumber, FileName HAVING DownloadsNumber >= 4


SELECT COUNT(*) as count, DataType, ContributorNick FROM MusicApp.FILEITEM
GROUP BY  DataType, ContributorNick

SELECT MAX(DownloadsNumber) as max, ContributorNick  FROM MusicApp.FILEITEM
GROUP BY ContributorNick HAVING ContributorNick <> 'alex'

SELECT DateRegistered, Profession, COUNT(*) FROM MusicApp.CONTRIBUTOR
where DateRegistered > '2019-12-22'
GROUP BY DateRegistered, Profession 

SELECT DateRegistered, Profession, COUNT(*) FROM MusicApp.CONTRIBUTOR
GROUP BY DateRegistered, Profession HAVING count(profession) > 1--DateRegistered > '2019-12-22'


SELECT COUNT(DownloadsNumber) as count, ContributorNick  FROM MusicApp.FILEITEM
GROUP BY ContributorNick HAVING ContributorNick <> 'alexxx'

SELECT MIN(DownloadsNumber)as min, ContributorNick  FROM MusicApp.FILEITEM
GROUP BY  ContributorNick

SELECT AVG(DownloadsNumber) as avg, DataType, ContributorNick  FROM MusicApp.FILEITEM
GROUP BY  DataType, ContributorNick

SELECT ComposerFullName, ComposerID FROM MusicApp.COMPOSER
GROUP BY ComposerFullName, ComposerID

SELECT SUM(DownloadsNumber) as avg, DataType, ContributorNick  FROM MusicApp.FILEITEM
GROUP BY  DataType, ContributorNick

SELECT FileName FROM MusicApp.AUDIO
UNION
SELECT FileName FROM MusicApp.TABS
UNION
SELECT FileName FROM MusicApp.NOTES


SELECT FileName FROM MusicApp.AUDIO
UNION ALL
SELECT FileName FROM MusicApp.TABS
UNION ALL
SELECT FileName FROM MusicApp.NOTES
UNION ALL
SELECT FileName FROM MusicApp.FILEITEM
ORDER BY FileName

SELECT FileName FROM MusicApp.AUDIO
UNION 
SELECT FileName FROM MusicApp.TABS
UNION 
SELECT FileName FROM MusicApp.NOTES
UNION 
SELECT FileName FROM MusicApp.FILEITEM
ORDER BY FileName

SELECT DISTINCT FullName FROM MusicApp.COMPOSITION
WHERE CompositionID IN (
SELECT CompositionID FROM MusicApp.IS_FOR
INTERSECT
SELECT CompositionID FROM MusicApp.COMPOSED)

SELECT DISTINCT FullName FROM MusicApp.COMPOSITION
WHERE CompositionID IN (
SELECT CompositionID FROM MusicApp.IS_FOR
EXCEPT
SELECT CompositionID FROM MusicApp.COMPOSED)

SELECT * FROM MusicApp.FILEITEM ORDER BY
FileName

SELECT * FROM MusicApp.CONTRIBUTOR


BEGIN TRANSACTION;
INSERT INTO MusicApp.COMPOSITION(FullName) VALUES
('SabreMassacre');
INSERT INTO MusicApp.FILEITEM (FileName, CompositionID, ContributorNick, DataType) VALUES
('SabreMassacre.PDF', @@IDENTITY, 'jason', 'NOTES');
COMMIT TRANSACTION;
GO