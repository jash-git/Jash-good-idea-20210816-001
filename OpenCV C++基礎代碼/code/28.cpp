void QuickDemo::bifilter_demo(Mat &image)
{
    Mat dst;
    bilateralFilter(image,dst,0,100,0);
    //参数1代表原图，参数2代表处理之后的图像，参数3色彩空间。参数4表示坐标空间，双边是指 色彩空间和坐标空间。
    namedWindow("双边模糊", WINDOW_FREERATIO);//创建了一个新窗口，参数1表示名称，第二个参数代表一个自由的比例
    imshow("双边模糊", dst);//表示显示在新创建的
}