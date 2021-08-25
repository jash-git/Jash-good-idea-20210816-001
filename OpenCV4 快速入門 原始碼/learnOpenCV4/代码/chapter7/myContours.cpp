#include <opencv2\opencv.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

int main()
{
	system("color F0");  //�������������ɫ
	Mat img = imread("keys.jpg");
	if (img.empty())
	{
		cout << "��ȷ��ͼ���ļ������Ƿ���ȷ" << endl;
		return -1;
	}
	imshow("ԭͼ", img);
	Mat gray, binary;
	cvtColor(img, gray, COLOR_BGR2GRAY);  //ת���ɻҶ�ͼ
	GaussianBlur(gray, gray, Size(13, 13), 4, 4);  //ƽ���˲�
	threshold(gray, binary, 170, 255, THRESH_BINARY | THRESH_OTSU);  //����Ӧ��ֵ��

																	 // �������������
	vector<vector<Point>> contours;  //����
	vector<Vec4i> hierarchy;  //��������ṹ����
	findContours(binary, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point());
	//��������
	for (int t = 0; t < contours.size(); t++)
	{
		drawContours(img, contours, t, Scalar(0, 0, 255), 2, 8);
	}
	//��������ṹ������
	for (int i = 0; i < hierarchy.size(); i++)
	{
		cout << hierarchy[i] << endl;
	}

	//��ʾ���
	imshow("���������", img);
	waitKey(0);
	return 0;
}