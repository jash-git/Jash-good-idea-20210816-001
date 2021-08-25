#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat img = imread("people.jpg");
	if (!img.data)
	{
		printf("��ȷ��ͼ���ļ��Ƿ�������ȷ");
		return -1;
	}
	
	Vec3b colorLut[5] = {
		Vec3b(0, 0, 255),
		Vec3b(0, 255, 0),
		Vec3b(255, 0, 0),
		Vec3b(0, 255, 255),
		Vec3b(255, 0, 255)
	};

	//ͼ��ĳߴ磬���ڼ���ͼ�������ص����Ŀ
	int width = img.cols;
	int height = img.rows;
	
	// ��ʼ������
	int sampleCount = width*height;
	

	//��ͼ���������ת����ÿ��һ�����ݵ���ʽ
	Mat sample_data = img.reshape(3, sampleCount);
	Mat data;
	sample_data.convertTo(data, CV_32F);

	//KMean����������ֵ���з���
	int number = 3;  //�ָ�����ɫ����
	Mat labels;
	TermCriteria criteria = TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 10, 0.1);
	kmeans(data, number, labels, criteria, number, KMEANS_PP_CENTERS);

	// ��ʾͼ��ָ���
	Mat result = Mat::zeros(img.size(), img.type());
	for (int row = 0; row < height; row++) 
	{
		for (int col = 0; col < width; col++) 
		{
			int index = row*width + col;
			int label = labels.at<int>(index, 0);
			result.at<Vec3b>(row, col) = colorLut[label];
		}
	}

	imshow("ԭͼ", img);
	imshow("�ָ��ͼ��", result);
	waitKey(0);
	return 0;
}