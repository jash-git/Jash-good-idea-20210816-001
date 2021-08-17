BEGIN
    PRINT(1);
    PRINT(2);
    RETURN ;
    PRINT(3); --在RETURN之后的代码不会被执行，因为会跳过当前批处理
    PRINT(4);
END
GO
BEGIN
    PRINT(5);
END
