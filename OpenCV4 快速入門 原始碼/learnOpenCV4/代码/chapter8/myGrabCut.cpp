#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat img = imread("lena.png");
	if (!img.data)  //��ֹ�����ȡͼ��
	{
		cout<<"��ȡͼ�������ȷ��ͼ���ļ��Ƿ���ȷ" << endl; 
		return 0;
	}

	//���ƾ���
	Mat imgRect;
	img.copyTo(imgRect);  //����ͼ�񣬷�ʽ���ƾ��ο�Խ������Ӱ��
	Rect rect(80, 30, 340, 390);
	rectangle(imgRect, rect, Scalar(255, 255, 255),2);
	imshow("ѡ��ľ�������", imgRect);

	//���зָ�
	Mat bgdmod = Mat::zeros(1, 65, CV_64FC1);
	Mat fgdmod = Mat::zeros(1, 65, CV_64FC1);
	Mat mask = Mat::zeros(img.size(), CV_8UC1);
	grabCut(img, mask, rect, bgdmod, fgdmod, 5, GC_INIT_WITH_RECT);
	
	//���ָ����ǰ�����ƻ���
	Mat result;
	for (int row = 0; row < mask.rows; row++) 
	{
		for (int col = 0; col < mask.cols; col++) 
		{
			int n = mask.at<uchar>(row, col);
			//��������ǰ���Ϳ�����ǰ�������򶼱���
			if (n == 1 || n == 3) 
			{
				mask.at<uchar>(row, col) = 255;
			}
			//�������Ǳ����Ϳ����Ǳ���������ɾ��
			else 
			{
				mask.at<uchar>(row, col) = 0;
			}
		}
	}
	bitwise_and(img, img, result, mask);
	imshow("�ָ���", result);
	waitKey(0);
	return 0;
}