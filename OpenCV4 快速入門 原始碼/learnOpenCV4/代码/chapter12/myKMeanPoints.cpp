#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() 
{
	//����һ��500��500��ͼ��������ʾ������ͷ�����
	Mat img(500, 500, CV_8UC3,Scalar(255,255,255));
	RNG rng(10000);

	//����������ɫ
	Scalar colorLut[3] = 
	{
		Scalar(0, 0, 255),
		Scalar(0, 255, 0),
		Scalar(255, 0, 0),
	};

	//���������㼯������ÿ���㼯�е����Ŀ���
	int number = 3;
	int Points1 = rng.uniform(20, 200);
	int Points2 = rng.uniform(20, 200);
	int Points3 = rng.uniform(20, 200);
	int Points_num = Points1 + Points2 + Points3;
	Mat Points(Points_num, 1, CV_32FC2);
	
	int i = 0;
	for (; i < Points1; i++)
	{
		Point2f pts;
		pts.x = rng.uniform(100, 200);
		pts.y = rng.uniform(100, 200);
		Points.at<Point2f>(i, 0) = pts;
	}

	for (; i < Points1+ Points2; i++)
	{
		Point2f pts;
		pts.x = rng.uniform(300, 400);
		pts.y = rng.uniform(100, 300);
		Points.at<Point2f>(i, 0) = pts;
	}

	for (; i < Points1+ Points2+ Points3; i++)
	{
		Point2f pts;
		pts.x = rng.uniform(100, 200);
		pts.y = rng.uniform(390, 490);
		Points.at<Point2f>(i, 0) = pts;
	}

	// ʹ��KMeans
	Mat labels;  //ÿ��������������
	Mat centers;  //ÿ��������λ������
	kmeans(Points, number, labels, TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 10, 0.1), 3, KMEANS_PP_CENTERS, centers);

	// ���ݷ���Ϊÿ�������ò�ͬ����ɫ
	img = Scalar::all(255);
	for (int i = 0; i < Points_num; i++)
	{
		int index = labels.at<int>(i);
		Point point = Points.at<Point2f>(i);
		circle(img, point, 2, colorLut[index], -1, 4);
	}

	// ����ÿ�����������������Բ
	for (int i = 0; i < centers.rows; i++) 
	{
		int x = centers.at<float>(i, 0);
		int y = centers.at<float>(i, 1);
		cout << "��" << i + 1 << "����������꣺x=" << x << "  y=" << y << endl;
		circle(img, Point(x, y), 50, colorLut[i], 1, LINE_AA);
	}

	imshow("K���ڵ㼯������", img);
	waitKey(0);
	return 0;
}