#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
using namespace cv;
#include<vector>
#include<iostream>
using namespace std;
int main(int argc, char*argv[])
{
	//构造旋转矩形
	RotatedRect rRect(Point2f(200,200),Point2f(90,150),-60);
	//计算旋转矩形的四个顶点，存储为一个 4 行 2 列的单通道 float 类型的 Mat
	Mat vertices;
	boxPoints(rRect, vertices);
	//打印四个顶点
	cout << vertices << endl;
	//在黑色画板上画出该旋转矩形
	Mat img=Mat::zeros(Size(400, 400), CV_8UC1);
	for (int i = 0; i < 4; i++)
	{
		//相邻的点
		Point p1 = vertices.row(i);
		int j = (i + 1) % 4;
		Point p2 = vertices.row(j);
		//画出直线
		line(img, p1, p2, Scalar(255), 3);
	}
	//显示旋转矩形
	imshow("旋转矩形", img);
	waitKey(0);
	return 0;
}