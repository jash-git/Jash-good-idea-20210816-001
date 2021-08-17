void QuickDemo::operators_demo(Mat &image)
{
    Mat dst = Mat::zeros(image.size(), image.type());
    Mat m = Mat::zeros(image.size(), image.type());
    dst = image - Scalar(50, 50, 50);
    m = Scalar(50, 50, 50);
    multiply(image,m,dst);//乘法操作 api
    imshow("乘法操作", dst);
    add(image, m, dst);//加法操作 api
    imshow("加法操作", dst);
    subtract(image, m, dst);//减法操作 api
    imshow("减法操作", dst);
    divide(image, m, dst);//除法操作 api
    namedWindow("加法操作", WINDOW_FREERATIO);
    imshow("加法操作", dst);
    //加法操作底层
    int dims = image.channels();
    int h = image.rows;
    int w = image.cols;
    for (int row = 0; row < h; row++)
    {
        for (int col = 0; col < w; col++)
        {
                Vec3b p1 = image.at<Vec3b>(row, col); //opencv特定的类型，获取三维颜色，3个值
                Vec3b p2 = m.at<Vec3b>(row, col);
                dst.at<Vec3b>(row, col)[0] = saturate_cast<uchar>(p1[0] + p2[0]);//saturate_cast用来防爆，小于0就是0，大于255就是255
                dst.at<Vec3b>(row, col)[1] = saturate_cast<uchar>(p1[1] + p2[1]);
                dst.at<Vec3b>(row, col)[2] = saturate_cast<uchar>(p1[2] + p2[2]);//对彩色图像读取它的像素值，并且对像素值进行改写。
        }
    }
    imshow("加法操作", dst);
}