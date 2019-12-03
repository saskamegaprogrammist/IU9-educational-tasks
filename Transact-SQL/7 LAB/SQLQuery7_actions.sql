USE DatabaseAlex7;
GO 

INSERT INTO MusicApp.CONTRIBUTOR VALUES
('alex', 'Spiridonova Alex', CONVERT (date, CURRENT_TIMESTAMP), 'programmer');

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
SELECT * FROM MusicApp.TABS;
GO

INSERT INTO MusicApp.FILEITEM (FileName, CompositionID, ContributorNick, DataType) VALUES
('libertango_1.txt', MusicApp.GetFileIdByFileName('LiberTango'), 'alex', 'TABS');