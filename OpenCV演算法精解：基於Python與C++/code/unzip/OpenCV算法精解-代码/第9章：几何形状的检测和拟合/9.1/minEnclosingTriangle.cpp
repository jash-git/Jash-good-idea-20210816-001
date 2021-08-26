#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
#include<iostream>
using namespace std;
int main(int argc, char*argv[])
{	
	
	//�㼯
	//vector<Point2f> points;
	//points.push_back(Point2f(1, 1));
	//points.push_back(Point2f(5, 1));
	//points.push_back(Point2f(1, 10));
	//points.push_back(Point2f(5, 10));
	//points.push_back(Point2f(2, 5));
	//����㼯����С���ֱ������
	
	//ת��Ϊ 5 �� 1 �е� 2 ͨ�� Mat
	//points = points.reshape(2, 5);
	/*
	//����㼯����С���ֱ������
	//Rect rect = boundingRect(points);
	//��㼯��͹��
	vector<Point2f> hull;
	convexHull(points,hull);
	//��ӡ�õ������ĵ㣨͹����
	for (int i = 0; i < hull.size(); i++)
	{
		cout << hull[i] << ",";
	}
	//
	*/
	// 5 �� 2 �еĵ�ͨ�� Mat
	Mat points = (Mat_<float>(5, 2) << 1, 1, 5, 1, 1, 10, 5, 10, 2, 5);
	//points = points.reshape(2, 5);//ת��Ϊ 2 ͨ������/
	vector<Point> triangle;//�洢�����ε���������
	//�㼯��С���������
	double area = minEnclosingTriangle(points, triangle);
	cout << "�����ε���������:";
	for (int i = 0; i < 3; i++)
		cout << triangle[i] << ",";
	cout << "��С��������ε������"<< area << endl;	
	return 0;
}