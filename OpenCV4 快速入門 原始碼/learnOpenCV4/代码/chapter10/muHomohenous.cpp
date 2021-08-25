#include <opencv2\opencv.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

int main()
{
	system("color F0");  //����DOS������ɫ

	//����������ά����
	vector<Point3f> points3;
	points3.push_back(Point3f(3, 6,1.5));
	points3.push_back(Point3f(23, 32, 1));

	//���������ת�������
	Mat points4;
	convertPointsToHomogeneous(points3, points4);

	//�������ת���������
	vector<Point2f> points2;
	convertPointsFromHomogeneous(points3, points2);

	cout << "***********�������ת���������*************" << endl;
	for (int i = 0; i < points3.size(); i++)
	{
		cout << "������꣺" << points3[i];
		cout<< "   ��������꣺" << points2[i] << endl;
	}

	cout << "***********���������ת�������*************" << endl;
	for (int i = 0; i < points3.size(); i++)
	{
		cout << "������꣺" << points3[i];
		cout << "   ��������꣺" << points4.at<Vec4f>(i, 0) << endl;
	}

	waitKey(0);
	return 0;
}