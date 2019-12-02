USE DatabaseAlex6;
GO 

DELETE FROM Lab6.STUDENTS;
GO 
DELETE FROM Lab6.GROUPS;  
GO 

INSERT INTO Lab6.GROUPS VALUES ('iu9-51', 'nika', 0, 0, 'Skorb'), ('iu9-52', 'janush', 0, 0, 'Dubashka'), ('iu9-53', 'dima', 0, 0, 'Golub');

INSERT INTO Lab6.STUDENTS VALUES ('sasha', 19, 1, 'Chelyabinsk', 'iu9-52'), ('alena', 20, 1, 'Novgorod', 'iu9-51'),
('ilya', 20, 0, 'Belgorod', 'iu9-53'), ('filon', 20, 0, 'Moscow', 'iu9-51');
GO

--DIRTY READ CHECK

--POSSIBLE

--SET TRANSACTION ISOLATION LEVEL READ UNCOMMITTED;
--GO
--BEGIN TRANSACTION;
--SELECT * FROM Lab6.GROUPS;
--SELECT * FROM Lab6.STUDENTS;
--UPDATE Lab6.STUDENTS
--SET FullName = 'KEK'
--WHERE PlaceOfBirth <> 'Moscow'
--INSERT INTO Lab6.GROUPS VALUES ('iu9-54', 'starosta4', 0, 0, 'Magazoff');
--INSERT INTO Lab6.STUDENTS VALUES ('daniil', 20, 1, 'Belgorod', 'iu9-52');
--WAITFOR DELAY '00:00:05';
--ROLLBACK;
--GO

--SELECT * FROM Lab6.GROUPS;
--SELECT * FROM Lab6.STUDENTS;

--NOT POSSIBLE

--SET TRANSACTION ISOLATION LEVEL READ COMMITTED;
--GO
--BEGIN TRANSACTION;
--SELECT * FROM Lab6.GROUPS;
--SELECT * FROM Lab6.STUDENTS;
--UPDATE Lab6.STUDENTS
--SET FullName = 'KEK'
--WHERE PlaceOfBirth <> 'Moscow'
--INSERT INTO Lab6.GROUPS VALUES ('iu9-54', 'starosta4', 0, 0, 'Magazoff');
--INSERT INTO Lab6.STUDENTS VALUES ('daniil', 20, 1, 'Belgorod', 'iu9-52');
--WAITFOR DELAY '00:00:05';
--ROLLBACK;
--GO

--SELECT * FROM Lab6.GROUPS;
--SELECT * FROM Lab6.STUDENTS;

--NOT POSSIBLE

--SET TRANSACTION ISOLATION LEVEL REPEATABLE READ;
--GO
--BEGIN TRANSACTION;
--SELECT * FROM Lab6.GROUPS;
--SELECT * FROM Lab6.STUDENTS;
--UPDATE Lab6.STUDENTS
--SET FullName = 'KEK'
--WHERE PlaceOfBirth <> 'Moscow'
--INSERT INTO Lab6.GROUPS VALUES ('iu9-54', 'starosta4', 0, 0, 'Magazoff');
--INSERT INTO Lab6.STUDENTS VALUES ('daniil', 20, 1, 'Belgorod', 'iu9-52');
--WAITFOR DELAY '00:00:05';
--ROLLBACK;
--GO

--SELECT * FROM Lab6.GROUPS;
--SELECT * FROM Lab6.STUDENTS;


--NOT POSSIBLE

SET TRANSACTION ISOLATION LEVEL SNAPSHOT;
GO
BEGIN TRANSACTION;
SELECT * FROM Lab6.GROUPS;
SELECT * FROM Lab6.STUDENTS;
UPDATE Lab6.STUDENTS
SET FullName = 'KEK'
WHERE PlaceOfBirth <> 'Moscow'
INSERT INTO Lab6.GROUPS VALUES ('iu9-54', 'starosta4', 0, 0, 'Magazoff');
INSERT INTO Lab6.STUDENTS VALUES ('daniil', 20, 1, 'Belgorod', 'iu9-52');
WAITFOR DELAY '00:00:05';
ROLLBACK;
GO

SELECT * FROM Lab6.GROUPS;
SELECT * FROM Lab6.STUDENTS;

--NOT POSSIBLE

--SET TRANSACTION ISOLATION LEVEL SERIALIZABLE;
--GO
--BEGIN TRANSACTION;
--SELECT * FROM Lab6.GROUPS;
--SELECT * FROM Lab6.STUDENTS;
--UPDATE Lab6.STUDENTS
--SET FullName = 'KEK'
--WHERE PlaceOfBirth <> 'Moscow'
--INSERT INTO Lab6.GROUPS VALUES ('iu9-54', 'starosta4', 0, 0, 'Magazoff');
--INSERT INTO Lab6.STUDENTS VALUES ('daniil', 20, 1, 'Belgorod', 'iu9-52');
--WAITFOR DELAY '00:00:05';
--ROLLBACK;
--GO

--SELECT * FROM Lab6.GROUPS;
--SELECT * FROM Lab6.STUDENTS;

SELECT resource_type, resource_associated_entity_id,  
    request_status, request_mode,request_session_id,  
    resource_description   
    FROM sys.dm_tran_locks  
    WHERE resource_database_id = 11  