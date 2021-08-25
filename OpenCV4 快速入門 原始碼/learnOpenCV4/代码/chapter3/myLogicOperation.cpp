#include <opencv2\opencv.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

int main()
{
	Mat img = imread("lena.png");
	if (img.empty())	{		cout << "��ȷ��ͼ���ļ������Ƿ���ȷ" << endl;		return -1;	}
	//���������ڰ�ͼ��
	Mat img0 = Mat::zeros(200, 200, CV_8UC1);
	Mat img1 = Mat::zeros(200, 200, CV_8UC1);
	Rect rect0(50, 50, 100, 100);
	img0(rect0) = Scalar(255);
	Rect rect1(100, 100, 100, 100);
	img1(rect1) = Scalar(255);
	imshow("img0", img0);
	imshow("img1", img1);

	//�����߼�����
	Mat myAnd, myOr, myXor, myNot, imgNot;
	bitwise_not(img0, myNot);
	bitwise_and(img0, img1, myAnd);
	bitwise_or(img0, img1, myOr);
	bitwise_xor(img0, img1, myXor);
	bitwise_not(img, imgNot);
	imshow("myAnd", myAnd);
	imshow("myOr", myOr);
	imshow("myXor", myXor);
	imshow("myNot", myNot);
	imshow("img", img);
	imshow("imgNot", imgNot);
	waitKey(0);
	return 0;
}

