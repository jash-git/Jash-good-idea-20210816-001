void QuickDemo::random_drawing()
{
    Mat canvas = Mat::zeros(Size(512,512), CV_8UC3);
    int w = canvas.cols;
    int h = canvas.rows;
    RNG rng(12345);
    while (true) 
    {
        int c = waitKey(10);
        if (c == 27) 
        {
            break;
        }
        int x1 = rng.uniform(0,canvas.cols);
        int y1 = rng.uniform(0, h);
        int x2 = rng.uniform(0, canvas.cols);
        int y2 = rng.uniform(0, h);
        int b  = rng.uniform(0, 255);
        int g  = rng.uniform(0, 255);
        int r  = rng.uniform(0, 255);
        canvas = Scalar(0,0,0);
        line(canvas, Point(x1, y1), Point(x2, y2), Scalar(b,g,r), 8, LINE_AA,0);//line_AA表示去掉锯齿 
        imshow("随机绘制演示", canvas);
    }
}