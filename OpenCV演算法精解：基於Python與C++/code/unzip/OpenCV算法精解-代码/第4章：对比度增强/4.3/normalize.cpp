#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
#include<iostream>
using namespace std;
int main(int argc, char*argv[])
{
	//ÊäÈë¾ØÕó
	Mat src = (Mat_<float>(2, 2) << 55, 80, 100, 255);
	// MINMAX
	Mat dst;
	normalize(src, dst, 10,NORM_L1, CV_32FC1);
	//normalize(src,dst,10,0,CV_MI)
	for (int r = 0; r < src.rows; r++)
	{
		for (int c = 0; c < src.cols; c++)
		{
			cout << dst.at<float>(r, c) << ",";
		}
	}
	return 0;
}