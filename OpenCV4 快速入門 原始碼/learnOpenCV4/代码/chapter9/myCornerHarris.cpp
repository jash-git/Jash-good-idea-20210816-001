#include <opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;


int main()
{
	Mat img = imread("lena.png", IMREAD_COLOR);
	if (!img.data)
	{
		cout << "��ȡͼ�������ȷ��ͼ���ļ��Ƿ���ȷ" << endl;
		return -1;
	}

	//ת�ɻҶ�ͼ��
	Mat gray;
	cvtColor(img, gray, COLOR_BGR2GRAY);

	//����Harrisϵ��
	Mat harris;
	int blockSize = 2;  //����뾶
	int apertureSize = 3;  //
	cornerHarris(gray, harris, blockSize, apertureSize, 0.04);
	
	//��һ�����ڽ�����ֵ�ȽϺͽ����ʾ
	Mat harrisn;
	normalize(harris, harrisn, 0, 255, NORM_MINMAX);
	//��ͼ����������ͱ��CV_8U
	convertScaleAbs(harrisn, harrisn);
	
	//Ѱ��Harris�ǵ�
	vector<KeyPoint> keyPoints;
	for (int row = 0; row < harrisn.rows; row++)
	{
		for (int col = 0; col < harrisn.cols; col++)
		{
			int R = harrisn.at<uchar>(row, col);
			if (R > 125)
			{
				//��ǵ����KeyPoint��
				KeyPoint keyPoint;
				keyPoint.pt.y = row;
				keyPoint.pt.x = col;
				keyPoints.push_back(keyPoint);
			}
		}
	}

	//���ƽǵ�����ʾ���
	drawKeypoints(img, keyPoints, img);
	imshow("ϵ������", harrisn);
	imshow("Harris�ǵ�", img);
	waitKey(0);
	return 0;
}
