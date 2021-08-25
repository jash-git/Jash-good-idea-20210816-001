#include <opencv2\opencv.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

int main()
{
	system("color F0");  //�������������ɫ
	//���ĸ����ʾ����������
	vector<Point> contour;
	contour.push_back(Point2f(0, 0));
	contour.push_back(Point2f(10, 0));
	contour.push_back(Point2f(10, 10));
	contour.push_back(Point2f(5, 5));
	double area = contourArea(contour);
	cout << "area =" << area << endl;

	Mat img = imread("coins.jpg");
	if (img.empty())
	{
		cout << "��ȷ��ͼ���ļ������Ƿ���ȷ" << endl;
		return -1;
	}
	imshow("ԭͼ", img);
	Mat gray, binary;
	cvtColor(img, gray, COLOR_BGR2GRAY);  //ת���ɻҶ�ͼ
	GaussianBlur(gray, gray, Size(9, 9), 2, 2);  //ƽ���˲�
	threshold(gray, binary, 170, 255, THRESH_BINARY | THRESH_OTSU);  //����Ӧ��ֵ��

																	 // �������
	vector<vector<Point>> contours;  //����
	vector<Vec4i> hierarchy;  //��������ṹ����
	findContours(binary, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point());

	//����������
	for (int t = 0; t < contours.size(); t++)
	{
		double area1 = contourArea(contours[t]);
		cout << "��" << t << "�������=" << area1 << endl;
	}
	return 0;
}
