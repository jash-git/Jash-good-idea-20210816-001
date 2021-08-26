#include<opencv2/core.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>
using namespace cv;
#include<iostream>
using namespace std;
int main(int argc, char*argv[])
{
	/*
	//输入矩阵
	Mat src = (Mat_<float>(2, 2) << -55, 80, 100, 255);
	// MINMAX
	Mat dst;
	normalize(src, dst, 1, 0,NORM_MINMAX, CV_32FC1);
	cout << dst << endl;
	*/
	//读入图像
	Mat src = imread(argv[1], CV_LOAD_IMAGE_ANYCOLOR);
	if (!src.data)
		return -1;
	//直方图正规化
	Mat dst;
	normalize(src, dst, 255, 0, NORM_MINMAX, CV_8U);
	//显示
	imshow("原图", src);
	imshow("直方图正规化", dst);
	waitKey(0);
	return 0;
}