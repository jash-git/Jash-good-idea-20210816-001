void QuickDemo::color_style_demo(Mat &image) 
{
    int colormap[] = {
        COLORMAP_AUTUMN ,
        COLORMAP_BONE,
        COLORMAP_CIVIDIS,
        COLORMAP_DEEPGREEN,
        COLORMAP_HOT,
        COLORMAP_HSV,
        COLORMAP_INFERNO,
        COLORMAP_JET,
        COLORMAP_MAGMA,
        COLORMAP_OCEAN,
        COLORMAP_PINK,
        COLORMAP_PARULA,
        COLORMAP_RAINBOW,
        COLORMAP_SPRING,
        COLORMAP_TWILIGHT,
        COLORMAP_TURBO,
        COLORMAP_TWILIGHT,
        COLORMAP_VIRIDIS,
        COLORMAP_TWILIGHT_SHIFTED,
        COLORMAP_WINTER
    };

    Mat dst;
    int index = 0;
    while (true) 
    {
        char c = waitKey(100);//停顿100ms 做视频处理都是1
        if (c == 27) { //esc 退出应用程序
            break;
        }
        if (c == 49)//key#1 按下按键1时，保存图片到指定位置
        {
            std::cout << "you enter key #1" << std::endl;
            imwrite("D:/gray.jpg", dst);
        }
        applyColorMap(image, dst, colormap[index%19]);//循环展示19种图片
        index++;
        imshow("循环播放", dst);
    }
}