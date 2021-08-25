#include <opencv2\opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat gray = imread("equalLena_salt.png", IMREAD_ANYCOLOR);
	Mat img = imread("lena_salt.png", IMREAD_ANYCOLOR);
	if (gray.empty() || img.empty())
	{
		cout << "��ȷ��ͼ���ļ������Ƿ���ȷ" << endl;		return -1;
	}
	Mat imgResult3, grayResult3, imgResult9, grayResult9;
	//�ֱ�Ժ��н��������Ĳ�ɫ�ͻҶ�ͼ������˲����˲�ģ��Ϊ3��3
	medianBlur(img, imgResult3, 3);
	medianBlur(gray, grayResult3, 3);
	//�Ӵ��˲�ģ�壬ͼ���˲�������ģ��
	medianBlur(img, imgResult9, 9);
	medianBlur(gray, grayResult9, 9);
	//��ʾ�˲�������
	imshow("img", img);
	imshow("gray", gray);
	imshow("imgResult3", imgResult3);
	imshow("grayResult3", grayResult3);
	imshow("imgResult9", imgResult9);
	imshow("grayResult9", grayResult9);
	waitKey(0);
	return 0;
}
