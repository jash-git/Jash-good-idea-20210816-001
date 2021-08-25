#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

int main()
{
	Mat img = imread("stuff.jpg");
	if (img.empty())	{		cout << "��ȷ��ͼ���ļ������Ƿ���ȷ" << endl;		return -1;	}
	Mat img1, img2;
	img.copyTo(img1);  //����������������Ӿ���
	img.copyTo(img2);  //�������������С��Ӿ���
	imshow("img", img);

	// ȥ�������ֵ��
	Mat canny;
	Canny(img, canny, 80, 160, 3, false);
	imshow("", canny);

	//�������㣬��ϸС��϶���
	Mat kernel = getStructuringElement(0, Size(3, 3));
	dilate(canny, canny, kernel);

	// �������������
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(canny, contours, hierarchy, 0, 2, Point());

	//Ѱ����������Ӿ���
	for (int n = 0; n < contours.size(); n++)
	{
		// �����Ӿ���
		Rect rect = boundingRect(contours[n]);
		rectangle(img1, rect, Scalar(0, 0, 255), 2, 8, 0);

		// ��С��Ӿ���
		RotatedRect rrect = minAreaRect(contours[n]);
		Point2f points[4];
		rrect.points(points);  //��ȡ��С��Ӿ��ε��ĸ�����
		Point2f cpt = rrect.center;  //��С��Ӿ��ε�����

									 // ������ת����������λ��
		for (int i = 0; i < 4; i++)
		{
			if (i == 3)
			{
				line(img2, points[i], points[0], Scalar(0, 255, 0), 2, 8, 0);
				break;
			}
			line(img2, points[i], points[i + 1], Scalar(0, 255, 0), 2, 8, 0);
		}
		//���ƾ��ε�����
		circle(img, cpt, 2, Scalar(255, 0, 0), 2, 8, 0);
	}

	//���������Ӿ��εĽ��
	imshow("max", img1);
	imshow("min", img2);
	waitKey(0);
	return 0;
}