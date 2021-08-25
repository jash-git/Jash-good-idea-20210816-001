#include <opencv2\opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	Mat img = imread("lena.png");
	if (img.empty())	{		cout << "��ȷ��ͼ���ļ������Ƿ���ȷ" << endl;		return -1;	}
	Mat img_x, img_y, img_xy;
	flip(img, img_x, 0);  //��x��Գ�
	flip(img, img_y, 1);  //��y��Գ�
	flip(img, img_xy, -1);  //��x��Գƣ���y��Գ�
	imshow("img", img);
	imshow("img_x", img_x);
	imshow("img_y", img_y);
	imshow("img_xy", img_xy);
	waitKey(0);
	return 0;
}