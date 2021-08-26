#include<opencv2\core.hpp>
#include<opencv2\highgui.hpp>
#include<opencv2\imgproc.hpp>
using namespace cv;
#include<vector>
#include<iostream>
using namespace std;
int main(int argc, char*argv[])
{
	//�㼯Χ�ɵ�����
	vector<Point> contour;
	contour.push_back(Point(0, 0));
	contour.push_back(Point(50, 30));
	contour.push_back(Point(100, 100));
	contour.push_back(Point(100, 0));
	//�����㼯Χ�ɵ�����
	Mat img = Mat::zeros(Size(130, 130), CV_8UC1);
	int num = contour.size();//�������
	for (int i = 0; i < num-1; i++)
	{
		//��ֱ�������໥��
		line(img, contour[i], contour[i + 1], Scalar(255), 1);
	}
	//��β����
	line(img, contour[0], contour[num - 1], Scalar(255), 1);
	//��ע���λ��
	circle(img, Point(80, 40), 3, Scalar(255),CV_FILLED );
	circle(img, Point(50, 0), 3, Scalar(255), CV_FILLED);
	circle(img, Point(40, 80), 3, Scalar(255), CV_FILLED);
	//����������
	double dist1 = pointPolygonTest(contour, Point2f(80, 40), true);
	cout << "dist1��" << dist1 << endl;
	//����������
	double dist2 = pointPolygonTest(contour, Point2f(50, 0), true);
	cout << "dist2��" << dist2 << endl;
	//����������
	double dist3 = pointPolygonTest(contour, Point2f(40, 80), true);
	cout << "dist3��" << dist3 << endl;
	//��ʾ�㼯Χ�ɵ���������������ע��
	imshow("����", img);
	waitKey(0);
	return 0;
}