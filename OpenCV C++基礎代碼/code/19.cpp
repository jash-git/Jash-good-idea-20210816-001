void QuickDemo::resize_demo(Mat &image)
{
    Mat zoomin, zoomout;
    int h = image.rows;
    int w = image.cols;
    resize(image, zoomin, Size(w/2, h/2),0,0,INTER_LINEAR);
    //线性差值操作。
    imshow("zoomin", zoomin);; 
    resize(image, zoomout, Size(w*1.5, h*1.5), 0, 0, INTER_LINEAR);
    imshow("zoomin", zoomout);//
}