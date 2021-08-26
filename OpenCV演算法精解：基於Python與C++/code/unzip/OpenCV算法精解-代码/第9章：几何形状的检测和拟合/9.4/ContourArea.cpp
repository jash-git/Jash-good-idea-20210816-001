#include<opencv2/core.hpp>
#include<opencv2/imgproc.hpp>
using namespace cv;
#include<iostream>
using namespace std;
int main(int argc, char*argv[])
{
	//点集
	/*
	vector<Point> points;
	points.push_back(Point2f(0, 0));
	points.push_back(Point2f(50, 30));
	points.push_back(Point2f(100, 0));
	points.push_back(Point2f(100, 100));
	*/
	//Mat points =(Mat_<float >(4, 2) << 0, 0, 50, 30, 100, 0, 100,100);
	Mat points = (Mat_<Vec2f >(4, 1) << Vec2f(0, 0), Vec2f(50, 30), Vec2f(100, 0), Vec2f(100, 100));
	//计算点集的所围区域的周长和面积
	double length1 = arcLength(points,false);
	double length2 = arcLength(points, true);
	double area = contourArea(points);
	//打印周长和面积
	cout << "首尾不相连的周长:" << length1 << endl;
	cout << "首尾相连的周长:" << length2 << endl;
	cout << "面积:" << area << endl;
	return 0;
}