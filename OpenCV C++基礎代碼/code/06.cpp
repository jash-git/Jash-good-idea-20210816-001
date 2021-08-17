Mat  src, dst, m;
int lightness = 50;//定义初始的亮度为50
static void on_track(int ,void*) 
{
    m = Scalar(lightness,lightness,lightness);//创建调整亮度的数值
    subtract(src, m, dst);//定义亮度变化为减
    imshow("亮度调整", dst);//显示调整亮度之后的图片
}
void QuickDemo::tracking_bar_demo(Mat &image)
{
    namedWindow("亮度调整",WINDOW_AUTOSIZE);
    dst = Mat::zeros(image.size(), image.type());//图片的初始化创建一个和image大小相等，种类相同的图像
    m = Mat::zeros(image.size(), image.type());//图片的初始化创建一个和image大小相等，种类相同的图像
    src = image;//给src赋值
    int max_value = 100;//定义最大值为100
    createTrackbar("Value Bar:", "亮度调整", &lightness, max_value,on_track);//调用函数实现功能。
    on_track(50, 0);
}