#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

void findcontours(Mat &image, vector<vector<Point>> &contours)
{
	Mat gray, binary;
	vector<Vec4i> hierarchy;
	//ͼ��ҶȻ�
	cvtColor(image, gray, COLOR_BGR2GRAY);
	//ͼ���ֵ��
	threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
	//Ѱ������
	findContours(binary, contours, hierarchy, 0, 2);
}

int main()
{
	Mat img = imread("ABC.png");
	Mat img_B = imread("B.png");
	if (img.empty() || img_B.empty())	{		cout << "��ȷ��ͼ���ļ������Ƿ���ȷ" << endl;		return -1;	}
	resize(img_B, img_B, Size(), 0.5, 0.5);
	imwrite("B.png", img_B);
	imshow("B", img_B);

	// ������ȡ
	vector<vector<Point>> contours1;
	vector<vector<Point>> contours2;
	findcontours(img, contours1);
	findcontours(img_B, contours2);
	// hu�ؼ���
	Moments mm2 = moments(contours2[0]);
	Mat hu2;
	HuMoments(mm2, hu2);
	// ����ƥ��
	for (int n = 0; n < contours1.size(); n++)
	{
		Moments mm = moments(contours1[n]);
		Mat hum;
		HuMoments(mm, hum);
		//Hu��ƥ��
		double dist;
		dist = matchShapes(hum, hu2, CONTOURS_MATCH_I1, 0);
		if (dist < 1)
		{
			drawContours(img, contours1, n, Scalar(0, 0, 255), 3, 8);
		}
	}
	imshow("match result", img);
	waitKey(0);
	return 0;
}