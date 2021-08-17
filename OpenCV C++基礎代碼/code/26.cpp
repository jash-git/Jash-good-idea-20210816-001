void QuickDemo::blur_demo(Mat &image)
{
    Mat dst;
    blur(image, dst, Size(15, 15), Point(-1, -1));
    //参数1原始图像，参数2卷积之后的图像，参数3卷积的矩阵大小，支持单行或者单列的卷积操作，参数4卷积的起始点。
    imshow("图像卷积操作", dst);
}