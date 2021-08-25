#include <opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat img = imread("lena.png");
	if (!img.data)
	{
		cout << "��ȡͼ�������ȷ��ͼ���ļ��Ƿ���ȷ" << endl;
		return -1;
	}
	//������ڵڶ��ַ������ƽǵ�
	Mat img2;
	img.copyTo(img2);
	Mat gray;
	cvtColor(img, gray, COLOR_BGR2GRAY);
	// Detector parameters

	//��ȡ�ǵ�
	int maxCorners = 100;  //���ǵ���Ŀ
	double quality_level = 0.01;  //�����ȼ�������˵��ֵ����ѽǵ�ı�����ϵ
	double minDistance = 0.04;  //�����ǵ�֮�����Сŷʽ����
	vector<Point2f> corners;
	goodFeaturesToTrack(gray, corners, maxCorners, quality_level, minDistance, Mat(), 3, false);

	//���ƽǵ�
	vector<KeyPoint> keyPoints;  //��Žǵ��KeyPoint�࣬���ں��ڻ��ƽǵ�ʱ��
	RNG rng(10086);
	for (int i = 0; i < corners.size(); i++) 
	{
		//��һ�ַ�ʽ���ƽǵ㣬��circle()�������ƽǵ�
		int b = rng.uniform(0, 256);
		int g = rng.uniform(0, 256);
		int r = rng.uniform(0, 256);
		circle(img, corners[i], 5, Scalar(b, g, r), 2, 8, 0);

		//���ǵ�����KeyPoint����
		KeyPoint keyPoint;
		keyPoint.pt = corners[i];
		keyPoints.push_back(keyPoint);
	}

	//�ڶ��ַ�ʽ���ƽǵ㣬��drawKeypoints()����
	drawKeypoints(img2, keyPoints, img2);
	//������ƽǵ�Ľ��
	imshow("��circle()�������ƽǵ���", img);
	imshow("ͨ�����ƹؼ��㺯�����ƽǵ���", img2);
	waitKey(0);
	return 0;
}
