#include <opencv2\opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat lena = imread("lena.png");
	Mat equalLena = imread("equalLena.png", IMREAD_ANYDEPTH);
	if (lena.empty() || equalLena.empty())
	{
		cout << "��ȷ��ͼ���ļ������Ƿ���ȷ" << endl;		return -1;
	}
	//������ԭͼ��ͬ�ߴ硢�������ͺ�ͨ�����ľ���
	Mat lena_noise = Mat::zeros(lena.rows, lena.cols, lena.type());
	Mat equalLena_noise = Mat::zeros(lena.rows, lena.cols, equalLena.type());
	imshow("lenaԭͼ", lena);
	imshow("equalLenaԭͼ", equalLena);
	RNG rng;  //����һ��RNG��
	rng.fill(lena_noise, RNG::NORMAL, 10, 20);  //������ͨ���ĸ�˹�ֲ������
	rng.fill(equalLena_noise, RNG::NORMAL, 15, 30);  //������ͨ���ĸ�˹�ֲ������
	imshow("��ͨ����˹����", lena_noise);
	imshow("��ͨ����˹����", equalLena_noise);
	lena = lena + lena_noise;  //�ڲ�ɫͼ������Ӹ�˹����
	equalLena = equalLena + equalLena_noise;  //�ڻҶ�ͼ������Ӹ�˹����
											  //��ʾ��Ӹ�˹�������ͼ��
	imshow("lena�������", lena);
	imshow("equalLena�������", equalLena);
	waitKey(0);
	return 0;
}
