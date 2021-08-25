#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

//������������
void drawapp(Mat result, Mat img2)
{
	for (int i = 0; i < result.rows; i++)
	{
		//���һ����������һ�����������
		if (i == result.rows - 1)
		{
			Vec2i point1 = result.at<Vec2i>(i);
			Vec2i point2 = result.at<Vec2i>(0);
			line(img2, point1, point2, Scalar(0, 0, 255), 2, 8, 0);
			break;
		}
		Vec2i point1 = result.at<Vec2i>(i);
		Vec2i point2 = result.at<Vec2i>(i + 1);
		line(img2, point1, point2, Scalar(0, 0, 255), 2, 8, 0);
	}
}

int main(int argc, const char *argv[])
{
	Mat img = imread("approx.png");
	if (img.empty())	{		cout << "��ȷ��ͼ���ļ������Ƿ���ȷ" << endl;		return -1;	}
	// ��Ե���
	Mat canny;
	Canny(img, canny, 80, 160, 3, false);
	//��������
	Mat kernel = getStructuringElement(0, Size(3, 3));
	dilate(canny, canny, kernel);

	// �������������
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(canny, contours, hierarchy, 0, 2, Point());

	//���ƶ����
	for (int t = 0; t < contours.size(); t++)
	{
		//����С��Ӿ�����ȡ��������
		RotatedRect rrect = minAreaRect(contours[t]);
		Point2f center = rrect.center;
		circle(img, center, 2, Scalar(0, 255, 0), 2, 8, 0);

		Mat result;
		approxPolyDP(contours[t], result, 4, true);  //��������
		drawapp(result, img);
		cout << "corners : " << result.rows << endl;

		//�ж���״�ͻ�������
		if (result.rows == 3)
		{
			putText(img, "triangle", center, 0, 1, Scalar(0, 255, 0), 1, 8);
		}
		if (result.rows == 4)
		{
			putText(img, "rectangle", center, 0, 1, Scalar(0, 255, 0), 1, 8);
		}
		if (result.rows == 8)
		{
			putText(img, "poly-8", center, 0, 1, Scalar(0, 255, 0), 1, 8);
		}
		if (result.rows > 12)
		{
			putText(img, "circle", center, 0, 1, Scalar(0, 255, 0), 1, 8);
		}
	}
	imshow("result", img);
	waitKey(0);
	return 0;
}