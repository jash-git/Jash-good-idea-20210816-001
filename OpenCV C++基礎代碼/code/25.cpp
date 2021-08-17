void QuickDemo::histogram_eq_demo(Mat &image)
{
    Mat gray;
    cvtColor(image, gray, COLOR_BGR2GRAY);
    //直方图均衡化只支持灰度图像，不支持彩色图像。
    imshow("灰度图像", gray);
    Mat dst;
    equalizeHist(gray, dst);
    imshow("直方图均衡化", dst);
}
