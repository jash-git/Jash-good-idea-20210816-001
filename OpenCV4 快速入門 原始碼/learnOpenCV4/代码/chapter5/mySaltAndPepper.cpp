#include <opencv2\opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

//����������
void saltAndPepper(cv::Mat image, int n)
{
	for (int k = 0; k<n / 2; k++)
	{
		//���ȷ��ͼ����λ��
		int i, j;
		i = std::rand() % image.cols;  //ȡ�������㣬��֤��ͼ��������� 
		j = std::rand() % image.rows;  //ȡ�������㣬��֤��ͼ��������� 
		int write_black = std::rand() % 2;  //�ж�Ϊ��ɫ�������Ǻ�ɫ�����ı���
		if (write_black == 0)  //��Ӱ�ɫ����
		{
			if (image.type() == CV_8UC1)  //����Ҷ�ͼ��
			{
				image.at<uchar>(j, i) = 255;  //��ɫ����
			}
			else if (image.type() == CV_8UC3)  //�����ɫͼ��
			{
				image.at<cv::Vec3b>(j, i)[0] = 255; //cv::Vec3bΪopencv�����һ��3��ֵ����������  
				image.at<cv::Vec3b>(j, i)[1] = 255; //[]ָ��ͨ����B:0��G:1��R:2  
				image.at<cv::Vec3b>(j, i)[2] = 255;
			}
		}
		else  //��Ӻ�ɫ����
		{
			if (image.type() == CV_8UC1)
			{
				image.at<uchar>(j, i) = 0;
			}
			else if (image.type() == CV_8UC3)
			{
				image.at<cv::Vec3b>(j, i)[0] = 0; //cv::Vec3bΪopencv�����һ��3��ֵ����������  
				image.at<cv::Vec3b>(j, i)[1] = 0; //[]ָ��ͨ����B:0��G:1��R:2  
				image.at<cv::Vec3b>(j, i)[2] = 0;
			}
		}

	}
}

int main()
{
	Mat lena = imread("lena.png");
	Mat equalLena = imread("equalLena.png", IMREAD_ANYDEPTH);
	if (lena.empty() || equalLena.empty())
	{
		cout << "��ȷ��ͼ���ļ������Ƿ���ȷ" << endl;		return -1;
	}
	imshow("lenaԭͼ", lena);
	imshow("equalLenaԭͼ", equalLena);
	saltAndPepper(lena, 10000);  //��ɫͼ����ӽ�������
	saltAndPepper(equalLena, 10000);  //�Ҷ�ͼ����ӽ�������
	imshow("lena�������", lena);
	imshow("equalLena�������", equalLena);
	waitKey(0);
	return 0;
}
