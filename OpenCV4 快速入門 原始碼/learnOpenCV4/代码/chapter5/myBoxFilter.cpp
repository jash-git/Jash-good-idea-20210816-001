#include <opencv2\opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat equalLena = imread("equalLena.png", IMREAD_ANYDEPTH);  //���ڷ����˲���ͼ��
	if (equalLena.empty())	{		cout << "��ȷ��ͼ���ļ������Ƿ���ȷ" << endl;		return -1;	}
	//��֤�����˲��㷨�����ݾ���
	float points[25] = { 1,2,3,4,5,
		6,7,8,9,10,
		11,12,13,14,15,
		16,17,18,19,20,
		21,22,23,24,25 };
	Mat data(5, 5, CV_32FC1, points);
	//��CV_8U����ת����CV_32F����
	Mat equalLena_32F;
	equalLena.convertTo(equalLena_32F, CV_32F, 1.0 / 255);
	Mat resultNorm, result, dataSqrNorm, dataSqr, equalLena_32FSqr;
	//�����˲�boxFilter()��sqrBoxFilter()
	boxFilter(equalLena, resultNorm, -1, Size(3, 3), Point(-1, -1), true);  //���й�һ��
	boxFilter(equalLena, result, -1, Size(3, 3), Point(-1, -1), false);  //�����й�һ��
	sqrBoxFilter(data, dataSqrNorm, -1, Size(3, 3), Point(-1, -1),
		true, BORDER_CONSTANT);  //���й�һ��
	sqrBoxFilter(data, dataSqr, -1, Size(3, 3), Point(-1, -1),
		false, BORDER_CONSTANT);  //�����й�һ��
	sqrBoxFilter(equalLena_32F, equalLena_32FSqr, -1, Size(3, 3), Point(-1, -1),
		true, BORDER_CONSTANT);
	//��ʾ������
	imshow("resultNorm", resultNorm);
	imshow("result", result);
	imshow("equalLena_32FSqr", equalLena_32FSqr);
	waitKey(0);
	return 0;
}