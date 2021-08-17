DECLARE @i INT;
SET @i = 1;
PRINT @i;
SET @i = 2;
PRINT @i;
GOTO ME;
SET @i = 3; --这行被跳过了
PRINT @i;

ME:PRINT('跳到我了?');
PRINT @i