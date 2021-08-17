//参数1表示鼠标事件。
Point sp(-1, -1);//鼠标的开始的位置
Point ep(-1, -1);
Mat temp;
static void on_draw(int event,int x,int y,int flags,void *userdata)
{
    Mat image = *((Mat*)userdata);
    if(event == EVENT_LBUTTONDOWN)//如果鼠标的左键按下
    {
        sp.x = x;
        sp.y = y;
        std::cout << "start point" <<sp<< std::endl;
    }
    elseif (event == EVENT_LBUTTONUP)
    {
        ep.x = x;
        ep.y = y;
        int dx = ep.x - sp.x;
        int dy = ep.y - sp.y;
        if (dx > 0 && dy > 0) 
        {
            Rect box(sp.x, sp.y, dx, dy);
            imshow("ROI区域", image(box));
            rectangle(image, box, Scalar(0, 0, 255), 2, 8, 0);
            imshow("鼠标绘制", image);
            sp.x = -1;
            sp.y = -1;//复位，为下一次做准备
        }
    }
    elseif (event == EVENT_MOUSEMOVE) 
    {
        if (sp.x > 0 && sp.y > 0)
        {
            ep.x = x;
            ep.y = y;
            int dx = ep.x - sp.x;
            int dy = ep.y - sp.y;
            if (dx > 0 && dy > 0)
            {
                Rect box(sp.x, sp.y, dx, dy);
                temp.copyTo(image);
                rectangle(image, box, Scalar(0, 0, 255), 2, 8, 0);
                imshow("鼠标绘制", image);
            }
        }
    }
}
void QuickDemo::mouse_drawing_demo(Mat &image)
{
    namedWindow("鼠标绘制", WINDOW_AUTOSIZE);
    setMouseCallback("鼠标绘制", on_draw,(void*)(&image));
    //设置窗口的回调函数。参数1表示名称，参数2表示调用on_draw
    imshow("鼠标绘制", image);
    temp = image.clone();
}