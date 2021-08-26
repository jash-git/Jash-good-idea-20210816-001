#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
using namespace cv;
#include<iostream>
using namespace std;
int main(int argc, char*argv[])
{
	//画布
	Mat img = Mat::zeros(Size(150, 150), CV_8UC1);

	//点集 1
	vector<Point> points1;
	points1.push_back(Point2f(0, 0));
	points1.push_back(Point2f(100, 100));
	points1.push_back(Point2f(50, 30));
	points1.push_back(Point2f(100, 0));
	//点集 2
	vector<Point> points2;
	points1.push_back(Point2f(0, 0));
	points1.push_back(Point2f(50, 30));
	points1.push_back(Point2f(100, 0));
	points1.push_back(Point2f(100, 100));
	//Mat points1 = (Mat_<float >(4, 2) << 0, 0, 50, 30, 100, 0, 100, 100);
	//点集 2
	vector<vector<Point>> points;
	points.push_back(points1);
	points.push_back(points2);
	int npt[2];
	npt[0] = points1.size();
	npt[1] = points2.size();
	for (int n = 0; n < points.size(); n++)
	{
		//drawContours(img, points, n, Scalar(255), 2);
		polylines(img, points[n], true, Scalar(255));
		//fillPoly(img, points[n], Scalar(255));
	}
	fillPoly(img, points, Scalar(255));
	//fillPoly(img, points, npt, points.size(), Scalar(255));
	imshow("img", img);
	waitKey(0);
	return 0;
}