#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat img = imread("HoughLines.jpg", IMREAD_GRAYSCALE);
	if (img.empty())	{		cout << "��ȷ��ͼ���ļ������Ƿ���ȷ" << endl;		return -1;	}
	Mat edge;

	//����Եͼ�񣬲���ֵ��
	Canny(img, edge, 80, 180, 3, false);
	threshold(edge, edge, 170, 255, THRESH_BINARY);

	//���ý�������ʽ����任��ȡֱ��
	vector<Vec4i> linesP1, linesP2;
	HoughLinesP(edge, linesP1, 1, CV_PI / 180, 150, 30, 10);  //����������������10
	HoughLinesP(edge, linesP2, 1, CV_PI / 180, 150, 30, 30);  //����������������30

															  //��������������������10ֱ�߼����
	Mat img1;
	img.copyTo(img1);
	for (size_t i = 0; i < linesP1.size(); i++)
	{
		line(img1, Point(linesP1[i][0], linesP1[i][1]),
			Point(linesP1[i][2], linesP1[i][3]), Scalar(255), 3);
	}

	//��������������������30ֱ�߼����
	Mat img2;
	img.copyTo(img2);
	for (size_t i = 0; i < linesP2.size(); i++)
	{
		line(img2, Point(linesP2[i][0], linesP2[i][1]),
			Point(linesP2[i][2], linesP2[i][3]), Scalar(255), 3);
	}

	//��ʾͼ��
	imshow("img1", img1);
	imshow("img2", img2);
	waitKey(0);
	return 0;
}