void QuickDemo::pixel_statistic_demo(Mat &image)
{
    double minv, maxv;//定义最值
    Point minLoc, maxLoc;//定义最值地址
    std::vector<Mat>mv;//mv是一个Mat类型的容器 装在这个容器内
    split(image, mv);
    for (int i = 0; i < mv.size(); i++) 
    {
        //分别打印各个通道的数值
        minMaxLoc(mv[i], &minv, &maxv, &minLoc, &maxLoc, Mat());//求出图像的最大值和最小值。
        std::cout <<"No.channels:"<<i<<"minvalue:" << minv << "maxvalue:" << maxv << std::endl;
    }
    Mat mean, stddev;
    meanStdDev(image, mean, stddev);//求出图像的均值和方差
    std::cout << "mean:" << mean << std::endl;
    std::cout << "stddev:" << stddev << std::endl;
}