void QuickDemo::channels_demo(Mat &image)
{    
    std::vector<Mat>mv;
    split(image, mv);
    //imshow("蓝色", mv[0]);
    //0,1,2三个通道分别代表BGR。
    //关闭2个通道意味着开启一个通道。
    //imshow("绿色", mv[1]);
    //imshow("红色", mv[2]);
    Mat dst;
    mv[0] = 0;
    mv[2] = 0;
    merge(mv, dst);
    imshow("蓝色", dst);
    int from_to[] = { 0,2,1,1,2,0 };
    //把通道相互交换，第0->第2，第一->第一，第二->第0
    mixChannels(&image,1,&dst,1,from_to,3);//3表示3个通道
    //参数1指针引用图像->参数2引用到dst
    imshow("通道混合", dst);
}