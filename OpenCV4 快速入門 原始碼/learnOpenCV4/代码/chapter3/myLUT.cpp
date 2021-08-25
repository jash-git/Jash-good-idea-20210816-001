#include <opencv2\opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	//LUT���ұ��һ��
	uchar lutFirst[256];
	for (int i = 0; i<256; i++)
	{
		if (i <= 100)
			lutFirst[i] = 0;
		if (i > 100 && i <= 200)
			lutFirst[i] = 100;
		if (i > 200)
			lutFirst[i] = 255;
	}
	Mat lutOne(1, 256, CV_8UC1, lutFirst);

	//LUT���ұ�ڶ���
	uchar lutSecond[256];
	for (int i = 0; i<256; i++)
	{
		if (i <= 100)
			lutSecond[i] = 0;
		if (i > 100 && i <= 150)
			lutSecond[i] = 100;
		if (i > 150 && i <= 200)
			lutSecond[i] = 150;
		if (i > 200)
			lutSecond[i] = 255;
	}
	Mat lutTwo(1, 256, CV_8UC1, lutSecond);

	//LUT���ұ������
	uchar lutThird[256];
	for (int i = 0; i<256; i++)
	{
		if (i <= 100)
			lutThird[i] = 100;
		if (i > 100 && i <= 200)
			lutThird[i] = 200;
		if (i > 200)
			lutThird[i] = 255;
	}
	Mat lutThree(1, 256, CV_8UC1, lutThird);

	//ӵ����ͨ����LUT���ұ����
	vector<Mat> mergeMats;
	mergeMats.push_back(lutOne);
	mergeMats.push_back(lutTwo);
	mergeMats.push_back(lutThree);
	Mat LutTree;
	merge(mergeMats, LutTree);

	//����ͼ��Ĳ��ұ�
	Mat img = imread("lena.png");
	if (img.empty())	{		cout << "��ȷ��ͼ���ļ������Ƿ���ȷ" << endl;		return -1;	}
	Mat gray, out0, out1, out2;
	cvtColor(img, gray, COLOR_BGR2GRAY);
	LUT(gray, lutOne, out0);
	LUT(img, lutOne, out1);
	LUT(img, LutTree, out2);
	imshow("out0", out0);
	imshow("out1", out1);
	imshow("out2", out2);
	waitKey(0);
	return 0;
}
