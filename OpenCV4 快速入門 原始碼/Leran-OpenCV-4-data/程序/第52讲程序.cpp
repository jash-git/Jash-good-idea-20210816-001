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

	for (int i = 0; i < corners.size(); i++)
	{
		//���ǵ�����KeyPoint����
		KeyPoint keyPoint;
		keyPoint.pt = corners[i];
		keyPoints.push_back(keyPoint);
	}

	//��drawKeypoints()�������ƽǵ�����
	drawKeypoints(img, keyPoints, img);
	imshow("�ǵ���", img);
	waitKey(0);
	return 0;
}
