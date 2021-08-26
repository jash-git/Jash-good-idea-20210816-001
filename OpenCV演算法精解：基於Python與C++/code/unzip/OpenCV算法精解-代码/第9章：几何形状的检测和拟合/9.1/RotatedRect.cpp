#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
#include<iostream>
using namespace std;
int main(int argc, char*argv[])
{
	//�㼯
	//Mat points = (Mat_<double>(5, 2) << 1, 1, 5, 1, 1, 10, 5, 10, 2, 5);
	vector<Point2f> points;
	points.push_back(Point2f(1, 1));
	points.push_back(Point2f(5, 1));
	points.push_back(Point2f(1, 10));
	points.push_back(Point2f(5, 10));
	points.push_back(Point2f(2, 5));
	//����㼯����С�����ת����
	RotatedRect rRect = minAreaRect(points);
	Rect rect = boundingRect(points);
	//��ӡ��ת���ε���Ϣ:
	cout <<"��ת���εĽǶ�:" <<rRect.angle << endl;
	cout <<"��ת���ε�����:"<< rRect.center << endl;
	cout << "��ת���εĳߴ�:" << rRect.size << endl;
	cout << rect << endl;
	return 0;
}