--有1到10這樣一組數字，從1按順序開始，遇到偶數就跳過，遇到奇數就打印出來，當遇到9就結束打印。
DECLARE @i int;
SET @i = 0;
WHILE(@i < 10)
BEGIN
    SET @i = @i + 1;
    IF(@i % 2 = 0)
    BEGIN
        PRINT ('跳过偶数数' + CAST(@i AS varchar));
        CONTINUE;
    END
    ELSE IF (@i = 9)
    BEGIN
        PRINT ('到' + CAST(@i AS varchar) + '就结束打印');
        BREAK;
    END
    PRINT @i;
END