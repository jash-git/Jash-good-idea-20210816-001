#include <opencv2\opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	//�����������������ȡ����֮��ľ���
	Mat a = (Mat_<uchar>(5, 5) << 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1,
		1, 1, 0, 1, 1,
		1, 1, 1, 1, 1,
		1, 1, 1, 1, 1);
	Mat dist_L1, dist_L2, dist_C, dist_L12;

	//�����������
	distanceTransform(a, dist_L1, 1, 3, CV_8U);
	cout << "�������룺" << endl << dist_L1 << endl;

	//����ŷʽ����
	distanceTransform(a, dist_L2, 2, 5, CV_8U);
	cout << "ŷʽ���룺" << endl << dist_L2 << endl;

	//�������̾���
	distanceTransform(a, dist_C, 3, 5, CV_8U);
	cout << "���̾��룺" << endl << dist_C << endl;

	//��ͼ����о���任
	Mat rice = imread("rice.png", IMREAD_GRAYSCALE);
	if (rice.empty())	{		cout << "��ȷ��ͼ���ļ������Ƿ���ȷ" << endl;		return -1;	}
	Mat riceBW, riceBW_INV;

	//��ͼ��ת�ɶ�ֵͼ��ͬʱ�Ѻڰ�������ɫ����
	threshold(rice, riceBW, 50, 255, THRESH_BINARY);
	threshold(rice, riceBW_INV, 50, 255, THRESH_BINARY_INV);

	//����任
	Mat dist, dist_INV;
	distanceTransform(riceBW, dist, 1, 3, CV_32F);  //Ϊ����ʾ���������������ͱ��CV_32F
	distanceTransform(riceBW_INV, dist_INV, 1, 3, CV_8U);

	//��ʾ�任���
	imshow("riceBW", riceBW);
	imshow("dist", dist);
	imshow("riceBW_INV", riceBW_INV);
	imshow("dist_INV", dist_INV);

	waitKey(0);
	return 0;
}