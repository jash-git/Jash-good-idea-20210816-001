
//获取文件大小(Byte)
size_t fileSize(const char* fileName);
bool readAndSendFile(SOCKET s, const char* fileName);
#include"tcpSocket.h"
int main()
{
  init_Socket();

  SOCKET serfd = create_serverSocket();
  printf("server create successed ,wait client connet...\n");
  //等待客户端连接
  SOCKET clifd = accept(serfd, NULL, NULL);
  if (clifd == INVALID_SOCKET)
  {
    err("accept");
  }
  while (1)
  {
    
    //可以和客户端进行通信了
    printf("等待客户端，请求数据...\n");
    //接受客户端请求的文件名
    char clientFileNames[100] = "";
    int ret = recv(clifd, clientFileNames, 100, 0);  
    if (ret <= 0)
    {
      closesocket(clifd);
      break;
    }
    readAndSendFile(clifd, clientFileNames);
    
  }



  closesocket(serfd);
  close_Socket();
  system("pause");
  return 0;
}
//获取文件大小(Byte)
size_t fileSize(const char* fileName)
{
  FILE* fp = fopen(fileName, "rb");
  if (fp == NULL)
  {
    perror("file open failed:");
    return -1;
  }
  char* buf = calloc(SendSize, sizeof(char));
  if (!buf)
  {
    printf("内存申请失败\n");
    return -1;
  }
    
  size_t size = 0;
  while (!feof(fp))
  {
    int ret = fread(buf, sizeof(char), SendSize, fp);
    size += ret;
  }

  fclose(fp);
  return size;
}

bool readAndSendFile(SOCKET s, const char* fileName)
{
  //获取文件大小
  size_t fileSzie = fileSize(fileName);
  if (fileSzie == (size_t)-1)
  {
    printf("get file size failed\n");
    return false;
  }


  //发送文件大小
  send(s, &fileSzie, sizeof(size_t), 0);
  

  FILE* read = fopen(fileName, "rb");
  if (!read)
  {
    perror("file open failed");
    return false;
  }

  size_t nblock = fileSzie / SendSize;        //计算分成100M的包，可以分多少块        
  size_t remain = fileSzie - nblock * SendSize;    //看有没有剩下的字节
  printf("nblock:%llu  remain:%llu\n", nblock, remain);

  //分配内存
  char*  fileBuf = calloc(SendSize, sizeof(char));
  if (!fileBuf)
  {
    printf("[error line:%d] memeory alloc failed\n", __LINE__);
    return false;
  }

  for (int i = 0; i < nblock; i++)
  {
    //把文件读到内存中来
    int len =  fread(fileBuf, sizeof(char), SendSize, read);
    //发送
    int ret = send(s, fileBuf, len, 0);
    if (ret == SOCKET_ERROR)
    {
      err("Send");
      return false;
    }

    printf("第%02d块发送成功,共(%d)Byte\n",i,ret);
  }

  //发送多余的数据
  if (remain != 0)
  {
    //把文件读到内存中来
    fread(fileBuf, sizeof(char), remain, read);
    //发送
    int ret = send(s, fileBuf, remain, 0);
    if (ret == SOCKET_ERROR)
    {
      err("Send");
      return false;
    }
    printf("最后一块发送成功,共(%d)Byte\n", ret);

  }    
  printf("\nAll file send successfully，totoa %llu Byte\n", nblock * SendSize + remain);

  free(fileBuf);

  fclose(read);
  return true;
}