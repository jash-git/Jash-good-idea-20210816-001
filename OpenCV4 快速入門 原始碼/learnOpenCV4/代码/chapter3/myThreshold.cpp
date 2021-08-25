#include <opencv2\opencv.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

int main()
{
	Mat img = imread("lena.png");
	if (img.empty())	{		cout << "��ȷ��ͼ���ļ������Ƿ���ȷ" << endl;		return -1;	}
	Mat gray;
	cvtColor(img, gray, COLOR_BGR2GRAY);
	Mat img_B, img_B_V, gray_B, gray_B_V, gray_T, gray_T_V, gray_TRUNC;

	//��ɫͼ���ֵ��
	threshold(img, img_B, 125, 255, THRESH_BINARY);
	threshold(img, img_B_V, 125, 255, THRESH_BINARY_INV);
	imshow("img_B", img_B);
	imshow("img_B_V", img_B_V);

	//�Ҷ�ͼBINARY��ֵ��
	threshold(gray, gray_B, 125, 255, THRESH_BINARY);
	threshold(gray, gray_B_V, 125, 255, THRESH_BINARY_INV);
	imshow("gray_B", gray_B);
	imshow("gray_B_V", gray_B_V);

	//�Ҷ�ͼ��TOZERO�任
	threshold(gray, gray_T, 125, 255, THRESH_TOZERO);
	threshold(gray, gray_T_V, 125, 255, THRESH_TOZERO_INV);
	imshow("gray_T", gray_T);
	imshow("gray_T_V", gray_T_V);

	//�Ҷ�ͼ��TRUNC�任
	threshold(gray, gray_TRUNC, 125, 255, THRESH_TRUNC);
	imshow("gray_TRUNC", gray_TRUNC);

	//�Ҷ�ͼ���򷨺������η���ֵ��
	Mat img_Thr = imread("threshold.png", IMREAD_GRAYSCALE);
	Mat img_Thr_O, img_Thr_T;
	threshold(img_Thr, img_Thr_O, 100, 255, THRESH_BINARY | THRESH_OTSU);
	threshold(img_Thr, img_Thr_T, 125, 255, THRESH_BINARY | THRESH_TRIANGLE);
	imshow("img_Thr", img_Thr);
	imshow("img_Thr_O", img_Thr_O);
	imshow("img_Thr_T", img_Thr_T);

	//�Ҷ�ͼ������Ӧ��ֵ��
	Mat adaptive_mean, adaptive_gauss;
	adaptiveThreshold(img_Thr, adaptive_mean, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 55, 0);
	adaptiveThreshold(img_Thr, adaptive_gauss, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 55, 0);

	imshow("adaptive_mean", adaptive_mean);
	imshow("adaptive_gauss", adaptive_gauss);
	waitKey(0);
	return 0;
}