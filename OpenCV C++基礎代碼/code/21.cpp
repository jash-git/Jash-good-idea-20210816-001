void QuickDemo::rotate_demo(Mat &image)
{
    Mat dst, M;
    int h = image.rows;//定义图片的高度
    int w = image.cols;//定义图片的宽度
    M = getRotationMatrix2D(Point(w / 2, h / 2),45,1.0);
    doublecos = abs(M.at<double>(0, 0));
    doublesin = abs(M.at<double>(0, 1));
    int nw = cos * w + sin * h;
    int nh = sin * w + cos * h;
    M.at<double>(0, 2) += (nw / 2 - w / 2);
    M.at<double>(1, 2) += (nh / 2 - h / 2);
    //参数1原来图像的中心位置。参数2角度是多少。参数3是图像本身大小的放大缩小
    warpAffine(image, dst, M,Size(nw,nh),INTER_LINEAR,0, Scalar(0, 0, 255));
    imshow("旋转演示", dst);
}