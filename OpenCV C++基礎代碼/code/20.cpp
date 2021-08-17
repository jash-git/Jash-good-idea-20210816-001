void QuickDemo::flip_demo(Mat &image)
{
    Mat dst;
    flip(image, dst, 0);//上下翻转 x对称
    flip(image, dst, 1);//左右翻转 y对称
    flip(image, dst, -1);//旋转180°
    imshow("图像翻转",dst);
}