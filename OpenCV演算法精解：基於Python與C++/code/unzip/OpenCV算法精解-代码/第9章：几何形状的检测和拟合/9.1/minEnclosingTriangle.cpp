#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
#include<iostream>
using namespace std;
int main(int argc, char*argv[])
{	
	
	//点集
	//vector<Point2f> points;
	//points.push_back(Point2f(1, 1));
	//points.push_back(Point2f(5, 1));
	//points.push_back(Point2f(1, 10));
	//points.push_back(Point2f(5, 10));
	//points.push_back(Point2f(2, 5));
	//计算点集的最小外包直立矩形
	
	//转换为 5 行 1 列的 2 通道 Mat
	//points = points.reshape(2, 5);
	/*
	//计算点集的最小外包直立矩形
	//Rect rect = boundingRect(points);
	//求点集的凸包
	vector<Point2f> hull;
	convexHull(points,hull);
	//打印得到最外侧的点（凸包）
	for (int i = 0; i < hull.size(); i++)
	{
		cout << hull[i] << ",";
	}
	//
	*/
	// 5 行 2 列的单通道 Mat
	Mat points = (Mat_<float>(5, 2) << 1, 1, 5, 1, 1, 10, 5, 10, 2, 5);
	//points = points.reshape(2, 5);//转换为 2 通道矩阵/
	vector<Point> triangle;//存储三角形的三个顶点
	//点集最小外包三角形
	double area = minEnclosingTriangle(points, triangle);
	cout << "三角形的三个顶点:";
	for (int i = 0; i < 3; i++)
		cout << triangle[i] << ",";
	cout << "最小外包三角形的面积："<< area << endl;	
	return 0;
}