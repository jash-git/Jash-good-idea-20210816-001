void QuickDemo::video_demo(Mat &image) 
{
    VideoCapture capture("D:/images/123.mp4");
    int frame_width = capture.get(CAP_PROP_FRAME_WIDTH);//获取视频的宽度
    int frame_height = capture.get(CAP_PROP_FRAME_HEIGHT);//获取视频的高度
    int count = capture.get(CAP_PROP_FRAME_COUNT);//视频总的帧数
    //fps是衡量处理视频的能力
    double fps = capture.get(CAP_PROP_FPS);
    std::cout << "frame width" << frame_width << std::endl;
    std::cout << "frame height" << frame_height << std::endl;
    std::cout << "frame FPS" << fps << std::endl;
    std::cout << "frame count" << count << std::endl;
    VideoWriter writer("D:/test.mp4",capture.get(CAP_PROP_FOURCC),fps,Size(frame_width, frame_height),true);
    //参数1 保存地址。参数2 获取图片的格式 参数3 图片的帧数 参数4 视频宽高 参数5 真
    Mat frame;
    while (true)
    {
        capture.read(frame);
        //flip(frame, frame, 1);//图像镜像操作
        if(frame.empty())
        {
            break;
        }
        imshow("frame", frame);
        colorSpace_Demo(frame);
        writer.write(frame);

        int c = waitKey(100);//停顿100ms 做视频处理都是1
        if (c == 27) { //esc 退出应用程序
            break;
        }
    }
    capture.release();//释放相机的资源
    writer.release();//释放存放的资源
}