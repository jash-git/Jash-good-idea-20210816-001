#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	//����һ��500��500��ͼ��������ʾ������ͷ�����
	Mat img(500, 500, CV_8UC3, Scalar(255, 255, 255));
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

	for (; i < Points1 + Points2; i++)
	{
		Point2f pts;
		pts.x = rng.uniform(300, 400);
		pts.y = rng.uniform(100, 300);
		Points.at<Point2f>(i, 0) = pts;
	}

	for (; i < Points1 + Points2 + Points3; i++)
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

	imshow("K��ֵ���������", img);
	waitKey(0);

	Mat img2 = imread("people.jpg");
	if (!img2.data)
	{
		printf("��ȷ��ͼ���ļ��Ƿ�������ȷ");
		return -1;
	}

	Vec3b colorLut2[5] = {
		Vec3b(0, 0, 255),
		Vec3b(0, 255, 0),
		Vec3b(255, 0, 0),
		Vec3b(0, 255, 255),
		Vec3b(255, 0, 255)
	};

	//ͼ��ĳߴ磬���ڼ���ͼ�������ص����Ŀ
	int width = img2.cols;
	int height = img2.rows;

	// ��ʼ������
	int sampleCount = width*height;


	//��ͼ���������ת����ÿ��һ�����ݵ���ʽ
	Mat sample_data = img2.reshape(3, sampleCount);
	Mat data;
	sample_data.convertTo(data, CV_32F);

	//KMean����������ֵ���з���
	int number2 = 3;  //�ָ�����ɫ����
	Mat labels2;
	TermCriteria criteria = TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 10, 0.1);
	kmeans(data, number2, labels2, criteria, number2, KMEANS_PP_CENTERS);

	// ��ʾͼ��ָ���
	Mat result = Mat::zeros(img2.size(), img2.type());
	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			int index = row*width + col;
			int label = labels2.at<int>(index, 0);
			result.at<Vec3b>(row, col) = colorLut2[label];
		}
	}

	namedWindow("ԭͼ", WINDOW_NORMAL);
	imshow("ԭͼ", img2);
	namedWindow("�ָ��ͼ��", WINDOW_NORMAL);
	imshow("�ָ��ͼ��", result);

	waitKey(0);
	return 0;
}

