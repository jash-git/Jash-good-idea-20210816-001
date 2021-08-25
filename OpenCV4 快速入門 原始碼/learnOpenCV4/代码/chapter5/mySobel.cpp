#include <opencv2\opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	//��ȡͼ�񣬺ڰ�ͼ���Ե�������Ϊ����
	Mat img = imread("equalLena.png", IMREAD_ANYCOLOR);
	if (img.empty())	{		cout << "��ȷ��ͼ���ļ������Ƿ���ȷ" << endl;		return -1;	}
	Mat resultX, resultY, resultXY;

	//X����һ�ױ�Ե
	Sobel(img, resultX, CV_16S, 2, 0, 1);
	convertScaleAbs(resultX, resultX);

	//Y����һ�ױ�Ե
	Sobel(img, resultY, CV_16S, 0, 1, 3);
	convertScaleAbs(resultY, resultY);

	//����ͼ���һ�ױ�Ե
	resultXY = resultX + resultY;

	//��ʾͼ��
	imshow("resultX", resultX);
	imshow("resultY", resultY);
	imshow("resultXY", resultXY);
	waitKey(0);
	return 0;
}