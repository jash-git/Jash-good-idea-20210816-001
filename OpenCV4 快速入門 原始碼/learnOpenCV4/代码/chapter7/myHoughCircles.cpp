#include <opencv2\opencv.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

int main()
{
	Mat img = imread("keys.jpg");
	if (img.empty())
	{
		cout << "��ȷ��ͼ���ļ������Ƿ���ȷ" << endl;
		return -1;
	}
	imshow("ԭͼ", img);
	Mat gray;
	cvtColor(img, gray, COLOR_BGR2GRAY);
	GaussianBlur(gray, gray, Size(9, 9), 2, 2);  //ƽ���˲�

												 //���Բ��
	vector<Vec3f> circles;
	double dp = 2; //
	double minDist = 10;  //����Բ��֮�����С����
	double	param1 = 100;  //Canny��Ե���Ľϴ���ֵ
	double	param2 = 100;  //�ۼ�����ֵ
	int min_radius = 20;  //Բ�ΰ뾶����Сֵ
	int max_radius = 100;  //Բ�ΰ뾶�����ֵ
	HoughCircles(gray, circles, HOUGH_GRADIENT, dp, minDist, param1, param2,
		min_radius, max_radius);

	//ͼ���б�ǳ�Բ��
	for (size_t i = 0; i < circles.size(); i++)
	{
		//��ȡԲ��
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		//��ȡ�뾶
		int radius = cvRound(circles[i][2]);
		//����Բ��
		circle(img, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		//����Բ
		circle(img, center, radius, Scalar(0, 0, 255), 3, 8, 0);
	}

	//��ʾ���
	imshow("Բ�����", img);
	waitKey(0);
	return 0;
}