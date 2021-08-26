#include<opencv2/core.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>
using namespace cv;
#include<iostream>
using namespace std;
int main(int argc, char*argv[])
{
	//����
	vector<Point> contour;
	contour.push_back(Point(20, 20));
	contour.push_back(Point(50, 70));
	contour.push_back(Point(20, 120));
	contour.push_back(Point(120, 120));
	contour.push_back(Point(100, 70));
	contour.push_back(Point(120, 20));
	//����������͹��
	vector<int> hull;
	convexHull(contour, hull, false, false);
	//����͹����ȱ��
	vector<Vec4i> defects;
	convexityDefects(contour, hull, defects);
	//��ӡ͹����ȱ��
	for (int i = 0; i < defects.size(); i++)
	{
		cout << defects[i] << endl;
	}
	return 0;
}