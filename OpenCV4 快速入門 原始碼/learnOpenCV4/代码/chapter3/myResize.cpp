#include <opencv2\opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	Mat gray = imread("lena.png", IMREAD_GRAYSCALE);
	if (gray.empty())	{		cout << "��ȷ��ͼ���ļ������Ƿ���ȷ" << endl;		return -1;	}
	Mat smallImg, bigImg0, bigImg1, bigImg2;
	resize(gray, smallImg, Size(15, 15), 0, 0, INTER_AREA);  //�Ƚ�ͼ����С
	resize(smallImg, bigImg0, Size(30, 30), 0, 0, INTER_NEAREST);  //����ڲ�ֵ
	resize(smallImg, bigImg1, Size(30, 30), 0, 0, INTER_LINEAR);  //˫���Բ�ֵ
	resize(smallImg, bigImg2, Size(30, 30), 0, 0, INTER_CUBIC);  //˫���β�ֵ
	namedWindow("smallImg", WINDOW_NORMAL);  //ͼ��ߴ�̫С��һ��Ҫ���ÿ��Ե��ڴ��ڴ�С��־
	imshow("smallImg", smallImg);
	namedWindow("bigImg0", WINDOW_NORMAL);
	imshow("bigImg0", bigImg0);
	namedWindow("bigImg1", WINDOW_NORMAL);
	imshow("bigImg1", bigImg1);
	namedWindow("bigImg2", WINDOW_NORMAL);
	imshow("bigImg2", bigImg2);
	waitKey(0);
	return 0;
}