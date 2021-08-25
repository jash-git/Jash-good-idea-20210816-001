#include <opencv2\opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	system("color F0");  //�������������ɫ
	float points[25] = { 1,2,3,4,5,
		6,7,8,9,10,
		11,12,13,14,15,
		16,17,18,19,20,
		21,22,23,24,25 };
	Mat data(5, 5, CV_32FC1, points);
	//X����Y����������˲����Ĺ���
	Mat a = (Mat_<float>(3, 1) << -1, 3, -1);
	Mat b = a.reshape(1, 1);
	Mat ab = a*b;
	//��֤��˹�˲��Ŀɷ�����
	Mat gaussX = getGaussianKernel(3, 1);
	Mat gaussData, gaussDataXY;
	GaussianBlur(data, gaussData, Size(3, 3), 1, 1, BORDER_CONSTANT);
	sepFilter2D(data, gaussDataXY, -1, gaussX, gaussX, Point(-1, -1), 0, BORDER_CONSTANT);
	//�������ָ�˹�˲��ļ�����
	cout << "gaussData=" << endl
		<< gaussData << endl;
	cout << "gaussDataXY=" << endl
		<< gaussDataXY << endl;
	//�����˲��Ŀɷ�����
	Mat dataYX, dataY, dataXY, dataXY_sep;
	filter2D(data, dataY, -1, a, Point(-1, -1), 0, BORDER_CONSTANT);
	filter2D(dataY, dataYX, -1, b, Point(-1, -1), 0, BORDER_CONSTANT);
	filter2D(data, dataXY, -1, ab, Point(-1, -1), 0, BORDER_CONSTANT);
	sepFilter2D(data, dataXY_sep, -1, b, b, Point(-1, -1), 0, BORDER_CONSTANT);
	//��������˲��������˲��ļ�����
	cout << "dataY=" << endl
		<< dataY << endl;
	cout << "dataYX=" << endl
		<< dataYX << endl;
	cout << "dataXY=" << endl
		<< dataXY << endl;
	cout << "dataXY_sep=" << endl
		<< dataXY_sep << endl;
	//��ͼ��ķ������
	Mat img = imread("lena.png");
	if (img.empty())
	{
		cout << "��ȷ��ͼ���ļ������Ƿ���ȷ" << endl;
		return -1;
	}
	Mat imgYX, imgY, imgXY;
	filter2D(img, imgY, -1, a, Point(-1, -1), 0, BORDER_CONSTANT);
	filter2D(imgY, imgYX, -1, b, Point(-1, -1), 0, BORDER_CONSTANT);
	filter2D(img, imgXY, -1, ab, Point(-1, -1), 0, BORDER_CONSTANT);
	imshow("img", img);
	imshow("imgY", imgY);
	imshow("imgYX", imgYX);
	imshow("imgXY", imgXY);
	waitKey(0);
	return 0;
}