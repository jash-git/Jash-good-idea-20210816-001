#include <opencv2\opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat equalLena = imread("equalLena.png", IMREAD_ANYDEPTH);
	Mat equalLena_gauss = imread("equalLena_gauss.png", IMREAD_ANYDEPTH);
	Mat equalLena_salt = imread("equalLena_salt.png", IMREAD_ANYDEPTH);
	if (equalLena.empty() || equalLena_gauss.empty() || equalLena_salt.empty())
	{
		cout << "��ȷ��ͼ���ļ������Ƿ���ȷ" << endl;		return -1;
	}
	Mat result_3, result_9;  //��Ų��������˲�������������ִ����˲����ߴ�
	Mat result_3gauss, result_9gauss;  //��ź��и�˹�����˲�������������ִ����˲����ߴ�
	Mat result_3salt, result_9salt;  //��ź��н��������˲�������������ִ����˲����ߴ�
	//���þ�ֵ�˲�����blur()�����˲�
	blur(equalLena, result_3, Size(3, 3));
	blur(equalLena, result_9, Size(9, 9));
	blur(equalLena_gauss, result_3gauss, Size(3, 3));
	blur(equalLena_gauss, result_9gauss, Size(9, 9));
	blur(equalLena_salt, result_3salt, Size(3, 3));
	blur(equalLena_salt, result_9salt, Size(9, 9));
	//��ʾ��������ͼ��
	imshow("equalLena ", equalLena);
	imshow("result_3", result_3);
	imshow("result_9", result_9);
	//��ʾ���и�˹����ͼ��
	imshow("equalLena_gauss", equalLena_gauss);
	imshow("result_3gauss", result_3gauss);
	imshow("result_9gauss", result_9gauss);
	//��ʾ���н�������ͼ��
	imshow("equalLena_salt", equalLena_salt);
	imshow("result_3salt", result_3salt);
	imshow("result_9salt", result_9salt);
	waitKey(0);
	return 0;
}