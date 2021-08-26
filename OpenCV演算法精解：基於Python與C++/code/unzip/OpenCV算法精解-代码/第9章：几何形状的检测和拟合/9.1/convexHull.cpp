#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
#include<iostream>
using namespace std;
int main(int argc, char*argv[])
{
	//点集
	Mat points = (Mat_<int>(5, 2) << 1, 1, 5, 1, 1, 10, 5, 10, 2, 5);
	//构成凸包的点
	vector<int> hull;
	convexHull(Mat(points), hull);
	//打印构成凸包的点
	for (int i = 0; i < hull.size; i++)
	{
		cout << hull[i] <<",";
	}
	return 0;
}