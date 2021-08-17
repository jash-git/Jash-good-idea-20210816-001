void QuickDemo::gaussian_blur_demo(Mat &image)
{
    Mat dst;
    GaussianBlur(image, dst, Size(5, 5), 15);
    imshow("高斯模糊", dst);
    //参数1表示初始图像，参数2表示处理后的图像，参数3表示高斯矩阵大小 正数而且是奇数，
    //参数4表示西格玛x为15 西格玛y为15 
}