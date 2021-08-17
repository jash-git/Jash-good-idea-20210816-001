--如果字符串的長度大於10，就打印該字符串，否則打印"字符串長度太短"
DECLARE @A VARCHAR(20)
SET @A='SQL数据库开发'
IF LEN(@A)>10
SELECT @A
ELSE
SELECT '字符串长度太短'