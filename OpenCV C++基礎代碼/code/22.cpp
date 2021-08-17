void QuickDemo::video_demo(Mat &image) 
{
    VideoCapture capture("D:/images/123.mp4");  //读取视频的地址
    Mat frame;//定义一个二值化的 frame

    while (true)
    {
        capture.read(frame); //读取视频
        //flip(frame, frame, 1);//图像镜像操作
        if(frame.empty())//如果视频为空的话 跳出操作
        {
            break;
        }
        imshow("frame", frame);//显示视频
        colorSpace_Demo(frame);//对视频调用之前的demo
        int c = waitKey(100);//停顿100ms 做视频处理都是1
        if (c == 27) { //esc 退出应用程序
            break;
        }
    }
    capture.release();//释放相机的资源
}