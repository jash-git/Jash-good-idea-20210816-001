#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

int main()
{
	system("color F0");  //�������������ɫ
	Mat img = imread("approx.png");
	if (img.empty())
	{
		cout << "��ȷ��ͼ���ļ������Ƿ���ȷ" << endl;
		return -1;
	}
	// ��Ե���
	Mat canny;
	Canny(img, canny, 80, 160, 3, false);
	//��������
	Mat kernel = getStructuringElement(0, Size(3, 3));
	dilate(canny, canny, kernel);

	// ��������
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(canny, contours, hierarchy, 0, 2, Point());

	//����ͼ���е�һ�����ص㲢����Բ��
	Point point = Point(250, 200);
	circle(img, point, 2, Scalar(0, 0, 255), 2, 8, 0);

	//�����
	for (int t = 0; t < contours.size(); t++)
	{
		//����С��Ӿ�����ȡ��������
		RotatedRect rrect = minAreaRect(contours[t]);
		Point2f center = rrect.center;
		circle(img, center, 2, Scalar(0, 255, 0), 2, 8, 0);  //����Բ�ĵ�
															 //�����ⲿ����������ľ���
		double dis = pointPolygonTest(contours[t], point, true);
		//�����ڲ�����������ľ���
		double dis2 = pointPolygonTest(contours[t], center, true);
		//�������
		cout << "�ⲿ������������룺" << dis << endl;
		cout << "�ڲ�������������룺" << dis2 << endl;
	}
	return 0;
}