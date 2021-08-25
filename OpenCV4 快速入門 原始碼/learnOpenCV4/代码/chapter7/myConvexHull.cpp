#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

int main()
{
	Mat img = imread("hand.png");
	if (img.empty())	{		cout << "��ȷ��ͼ���ļ������Ƿ���ȷ" << endl;		return -1;	}
	// ��ֵ��
	Mat gray, binary;
	cvtColor(img, gray, COLOR_BGR2GRAY);
	threshold(gray, binary, 105, 255, THRESH_BINARY);

	//����������ϸС����
	Mat k = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
	morphologyEx(binary, binary, MORPH_OPEN, k);
	imshow("binary", binary);

	// ��������
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(binary, contours, hierarchy, 0, 2, Point());
	for (int n = 0; n < contours.size(); n++)
	{
		//����͹��
		vector<Point> hull;
		convexHull(contours[n], hull);
		//����͹��
		for (int i = 0; i < hull.size(); i++)
		{
			//����͹������
			circle(img, hull[i], 4, Scalar(255, 0, 0), 2, 8, 0);
			//����͹��
			if (i == hull.size() - 1)
			{
				line(img, hull[i], hull[0], Scalar(0, 0, 255), 2, 8, 0);
				break;
			}
			line(img, hull[i], hull[i + 1], Scalar(0, 0, 255), 2, 8, 0);
		}
	}
	imshow("hull", img);
	waitKey(0);
	return 0;
}