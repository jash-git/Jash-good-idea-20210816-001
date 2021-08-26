#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
#include<iostream>
using namespace std;
int main(int argc, char*argv[])
{
	//点集
	//Mat points = (Mat_<double>(5, 2) << 1, 1, 5, 1, 1, 10, 5, 10, 2, 5);
	vector<Point2f> points;
	points.push_back(Point2f(1, 1));
	points.push_back(Point2f(5, 1));
	points.push_back(Point2f(1, 10));
	points.push_back(Point2f(5, 10));
	points.push_back(Point2f(2, 5));
	//计算点集的最小外包旋转矩形
	RotatedRect rRect = minAreaRect(points);
	Rect rect = boundingRect(points);
	//打印旋转矩形的信息:
	cout <<"旋转矩形的角度:" <<rRect.angle << endl;
	cout <<"旋转矩形的中心:"<< rRect.center << endl;
	cout << "旋转矩形的尺寸:" << rRect.size << endl;
	cout << rect << endl;
	return 0;
}