
#include"tcpSocket.h"
const char* getFileName(const char* fullPath);
bool recvAndSaveFile(SOCKET s, const char* fileName);
int main()
{
  init_Socket();

  SOCKET fd = create_clientSocket("127.0.0.1");
  printf("connet server successed..\n");

  while (true)
  {
    //向服务器发送需要获取的文件名
    char filePath[100] = "";
    printf("请输入要downLoad的文件名:");
    gets_s(filePath, 100);
    send(fd, filePath, strlen(filePath), 0);


    const char * saveFileName = getFileName(filePath);
    recvAndSaveFile(fd, saveFileName);

  }
  
  closesocket(fd);
  close_Socket();
  system("pause");
  return 0;
}
//从完整路径中获取文件名
const char* getFileName(const char* fullPath)
{
  char* resStr = NULL;
  if ((resStr = strrchr(fullPath, '/')) == NULL)
  {
    resStr = strrchr(fullPath, '\\');
  }
  return resStr + 1;
}
//从服务器接受并保存文件
bool recvAndSaveFile(SOCKET s, const char* fileName)
{
  //总文件大小
  size_t fileSize = -1;
  //接收文件大小
  recv(s, &fileSize, sizeof(size_t), 0);
  printf("recv filesize:%llu\n", fileSize);

  FILE* fp = fopen(fileName, "wb+");
  if (fp == NULL)
  {
    perror("file open failed:");
    return false;
  }

  char* fileBuf = calloc(SendSize, sizeof(char));
  if (!fileBuf)
  {
    printf("[error line:%d] memeory alloc failed\n", __LINE__);
    return false;
  }

  size_t recvSize = 0;        //当前接受到的文件总大小
  while (recvSize < fileSize)  //如果没有接收完整，则继续接收
  {
    int ret = recv(s, fileBuf, SendSize, 0);
    if (ret > 0)
    {
      //实际接收到多少数据，就写入多少数据
      fwrite(fileBuf, sizeof(char), ret, fp);
    }
    else if (ret <= 0)
    {
      printf("服务器下线...\n");
      break;
    }
    recvSize += ret;
    printf("%lfM/%lfM\n", (double)recvSize/1024/1024, (double)fileSize /1024/1024);
    //printf("当前接受到(%.2lf)MB的数据，剩余(%.2lf)MB未接收\n", (double)ret / 1024 / 1024, (double)(g_fileSzie - recvSize)/1024/1024);
    //printf("当前接受到(%d)Byte的数据，剩余(%llu)Byte未接收\n", ret,g_fileSzie-recvSize);
  }
  fclose(fp);
  printf("总共接受到 %llu Byte的数据\n", recvSize);
  free(fileBuf);

  return false;
}