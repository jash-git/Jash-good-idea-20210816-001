void QuickDemo::key_demo(Mat &image) 
{
    Mat dst= Mat::zeros(image.size(), image.type());
    while (true) 
    {
        char c = waitKey(100);//停顿100ms 做视频处理都是1
        if (c == 27) { //esc 退出应用程序
            break;
        }
        if (c == 49)//key#1
        {
            std::cout <<"you enter key #1" << std::endl;
            cvtColor(image, dst, COLOR_BGR2GRAY);
        }
        if (c == 50)//key#1
        {
            std::cout << "you enter key #2"  << std::endl;
            cvtColor(image, dst, COLOR_BGR2HSV);
        }
        if (c == 51)//key#1
        {
            std::cout << "you enter key #3" << std::endl;
            dst = Scalar(50, 50, 50);
            add(image,dst,dst);
        }
        imshow("键盘响应",dst);
        std::cout << c << std::endl;
    }
}