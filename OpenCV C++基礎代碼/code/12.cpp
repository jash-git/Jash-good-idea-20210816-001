void QuickDemo::inrange_demo(Mat &image)
{
    Mat hsv;
    cvtColor(image, hsv, COLOR_BGR2HSV);
    Mat mask;
    inRange(hsv,Scalar(35,43,46),Scalar(77,255,255),mask);
    //35,43,46根据图片中绿色最低来确定最小值。
    //77,255,255 提取
    //参数1低范围，参数2高范围
    //将hsv中的由低到高的像素点提取出来并且存储到mask当中。
    imshow("mask",hsv);
    Mat redback = Mat::zeros(image.size(), image.type());
    redback = Scalar(40, 40, 200);
    bitwise_not(mask, mask);
    imshow("mask", mask);
    image.copyTo(redback, mask);//把redback复制到mask，mask通过inRange得到。
    imshow("roi提取", hsv);
}