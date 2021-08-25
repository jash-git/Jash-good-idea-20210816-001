#include <opencv2\opencv.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

int main()
{
	Mat img(500, 500, CV_8UC3, Scalar::all(0));
	RNG& rng = theRNG();  //���������

	while (true)
	{
		int i, count = rng.uniform(1, 101);
		vector<Point> points;
		//���������
		for (i = 0; i < count; i++)
		{
			Point pt;
			pt.x = rng.uniform(img.cols / 4, img.cols * 3 / 4);
			pt.y = rng.uniform(img.rows / 4, img.rows * 3 / 4);
			points.push_back(pt);
		}

		//Ѱ�Ұ�Χ�㼯�������� 
		vector<Point2f> triangle;
		double area = minEnclosingTriangle(points, triangle);

		//Ѱ�Ұ�Χ�㼯��Բ��
		Point2f center;
		float radius = 0;
		minEnclosingCircle(points, center, radius);

		//��������ͼƬ����������
		img = Scalar::all(0);
		Mat img2;
		img.copyTo(img2);

		//��ͼ���л��������
		for (i = 0; i < count; i++)
		{
			circle(img, points[i], 3, Scalar(255, 255, 255), FILLED, LINE_AA);
			circle(img2, points[i], 3, Scalar(255, 255, 255), FILLED, LINE_AA);
		}
			
		//����������
		for (i = 0; i < 3; i++)
		{
			if (i==2)
			{
				line(img, triangle[i], triangle[0], Scalar(255, 255, 255), 1, 16);
				break;
			}
			line(img, triangle[i], triangle[i + 1], Scalar(255, 255, 255), 1, 16);
		}

		//����Բ��
		circle(img2, center, cvRound(radius), Scalar(255, 255, 255), 1, LINE_AA);

		//������
		imshow("triangle", img);
		imshow("circle", img2);

		//��q������ESC���˳�����
		char key = (char)waitKey();
		if (key == 27 || key == 'q' || key == 'Q')
		{
			break;
		}
	}
	return 0;
}