#include <opencv2\opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	//��ȡ���ź���������ͼ��
	Mat img1 = imread("img1.png", IMREAD_ANYCOLOR);
	Mat img2 = imread("img2.png", IMREAD_ANYCOLOR);
	if (img1.empty() || img2.empty())
	{
		cout << "��ȷ��ͼ���ļ������Ƿ���ȷ" << endl;		return -1;
	}
	Mat result1, result2, result3, result4;
	//��֤��ͬ�˲���ֱ�����˲�Ч��
	bilateralFilter(img1, result1, 9, 50, 25 / 2);
	bilateralFilter(img1, result2, 25, 50, 25 / 2);
	//��֤��ͬ��׼��ֵ���˲�Ч��
	bilateralFilter(img2, result3, 9, 9, 9);
	bilateralFilter(img2, result4, 9, 200, 200);
	//��ʾԭͼ
	imshow("img1", img1);
	imshow("img2", img2);
	//��ֱͬ���˲����
	imshow("result1", result1);
	imshow("result2", result2);
	//��ͬ��׼��ֵ�˲����
	imshow("result3 ", result3);
	imshow("result4", result4);
	waitKey(0);
	return 0;
}