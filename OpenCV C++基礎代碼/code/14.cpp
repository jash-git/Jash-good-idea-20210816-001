void QuickDemo::drawing_demo(Mat &image)
{
    Rect rect;
    rect.x = 200;
    rect.y = 200;
    rect.width = 100;
    rect.height = 100;
    Mat bg = Mat::zeros(image.size(),image.type());
    rectangle(image, rect, Scalar(0, 0, 255), -1, 8, 0);
    //参数1为绘图的底图或者画布名称，参数2位图片的起始，宽度，高度
    //参数3代表填充颜色。参数4大于0是线小于0是填充
    //参数5表示邻域填充，参数6默认值为0
    circle(bg, Point(350, 400), 15, Scalar(0, 0, 255), 2, LINE_AA, 0);
    //参数2位图片中心位置，参数3为半径为15的圆
    Mat dst;
    //addWeighted(image, 0.7, bg, 0.3, 0, dst);
    RotatedRect rtt;
    rtt.center = Point(200, 200);
    rtt.size = Size(100, 200);
    rtt.angle = 0.0;
    line(bg,Point(100,100),Point(350,400), Scalar(0, 0, 255), 8, LINE_AA, 0);//line_AA表示去掉锯齿
    ellipse(bg,rtt, Scalar(0, 0, 255), 2, 8);
    imshow("矩形的绘制",bg);
}