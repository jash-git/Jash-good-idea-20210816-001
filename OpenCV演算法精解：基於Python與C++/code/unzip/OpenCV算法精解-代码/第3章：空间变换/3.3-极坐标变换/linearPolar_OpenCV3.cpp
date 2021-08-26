#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
using namespace cv;
#include<iostream>
using namespace std;
int main(int argc, char*argv[])
{
	//输入图像
	Mat src = imread(argv[1], IMREAD_ANYCOLOR);
	if (!src.data)
		return -1;
	//极坐标变换
	Mat dst;
	linearPolar(src, dst, Point2f(508, 503), 550, CV_INTER_LINEAR);
	cout << src.size() << endl;
	cout << float(360)/dst.size().height << endl;
	cout << float(550) / dst.size().width << endl;
	//显示原图和极坐标变换图
	imshow("原图", src);
	imshow("极坐标变换图", dst);
	//imwrite("dst.jpg", dst);
	waitKey(0);
	return 0;
}