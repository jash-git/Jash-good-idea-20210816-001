--如果某字符串的長度大於5，就打印該字符串
DECLARE @A VARCHAR(20)
SET @A='SQL数据库开发'
IF LEN(@A)>5
SELECT @A