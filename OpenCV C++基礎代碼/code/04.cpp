void QuickDemo::pixel_visit_demo(Mat &image)
{
    int dims = image.channels();
    int h = image.rows;
    int w = image.cols;
    for (int row = 0; row < h; row++) 
    {
        for (int col = 0; col < w; col++) 
        {
            if (dims == 1) //单通道的灰度图像
            {
                int pv = image.at<uchar>(row, col);//得到像素值
                image.at<uchar>(row, col) = 255 - pv;//给像素值重新赋值

            }
            if (dims == 3) //三通道的彩色图像
            {
                Vec3b bgr = image.at<Vec3b>(row, col); //opencv特定的类型，获取三维颜色，3个值
                image.at<Vec3b>(row, col)[0] = 255 - bgr[0];
                image.at<Vec3b>(row, col)[1] = 255 - bgr[1];
                image.at<Vec3b>(row, col)[2] = 255 - bgr[2];//对彩色图像读取它的像素值，并且对像素值进行改写。
            }
        }
    }
    namedWindow("像素读写演示", WINDOW_FREERATIO);
    imshow("像素读写演示", image);
}

//第二種為指針訪問模式，指定一個指針為圖片的首地址，通過循環遍歷，指針++，一次往後推。
void QuickDemo::pixel_visit_demo(Mat &image)
{
    int dims = image.channels();
    int h = image.rows;
    int w = image.cols;
    for (int row = 0; row < h; row++)
    {
        uchar *current_row = image.ptr<uchar>(row);

        for (int col = 0; col < w; col++)
        {
            if (dims == 1) //单通道的灰度图像
            {
                int pv = *current_row;//得到像素值
                    *current_row++ = 255 - pv;//给像素值重新赋值

            }
            if (dims == 3) //三通道的彩色图像
            {
                *current_row++ = 255 - *current_row; //指针每做一次运算，就向后移动一位
                *current_row++ = 255 - *current_row;
                *current_row++ = 255 - *current_row;
            }
        }
    }
    namedWindow("像素读写演示", WINDOW_FREERATIO);
    imshow("像素读写演示", image);

}