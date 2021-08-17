static void on_lightness(int b ,void* userdata) 
{
    Mat image = *((Mat*)userdata);
    Mat dst = Mat::zeros(image.size(), image.type());
    Mat m = Mat::zeros(image.size(), image.type());
    m = Scalar(b,b,b);
    addWeighted(image,1.0,m,0,b,dst);//融合两张图
    imshow("亮度&对比度调整", dst);
}
static void on_contrast(int b, void* userdata)
{
    Mat image = *((Mat*)userdata);
    Mat dst = Mat::zeros(image.size(), image.type());
    Mat m = Mat::zeros(image.size(), image.type());
    double contrast = b / 100.0;
    addWeighted(image, contrast, m, 0.0, 0, dst);//融合两张图
    imshow("亮度&对比度调整", dst);
}
void QuickDemo::tracking_bar_demo(Mat &image)
{
    namedWindow("亮度&对比度调整",WINDOW_AUTOSIZE);
    int lightness = 50;
    int max_value = 100;
    int contrast_value = 100;
    createTrackbar("Value Bar:", "亮度&对比度调整", &lightness, max_value, on_lightness,(void*)(&image));
    createTrackbar("Contrast Bar:", "亮度&对比度调整", &contrast_value, 200, on_contrast, (void*)(&image));
    on_lightness(50, &image);
}