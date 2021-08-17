
void QuickDemo::polyline_drawing_demo(Mat &image)
{
    Mat canvas = Mat::zeros(Size(512, 512), CV_8UC3);
    Point p1(100, 100);
    Point p2(350, 100);
    Point p3(450, 280);
    Point p4(320, 450);
    Point p5(80, 400);
    std::vector<Point>pts;//将5个点装入一个容器内。
    pts.push_back(p1);//未初始化数组容量，只能用pushback操作
                      //如果初始化，可以用数组下标操作。
    pts.push_back(p2);
    pts.push_back(p3);
    pts.push_back(p4);
    pts.push_back(p5);
    //fillPoly(canvas, pts, Scalar(122, 155, 255), 8, 0);//填充多边形
    //polylines(canvas, pts, true, Scalar(0, 0, 255), 2, 8, 0);//绘制多边形
    /*
    参数1表示画布，参数2表示点集，参数3表示true，参数4颜色
    参数5表示线宽，参数6表示渲染方式，参数7表示相对左上角（0,0）的位置
    */
    //单个API搞定图片的绘制填充
    std::vector<std::vector<Point>>contours;
    contours.push_back(pts);
    drawContours(canvas,contours,-1, Scalar(0, 0, 255),-1);
    //参数2表示容器名称，参数3为正表示多边形的绘制，为负表示多边形的填充
    imshow("多边形绘制", canvas);
}