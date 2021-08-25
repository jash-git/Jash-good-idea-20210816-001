#include <opencv2\opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	Mat img = imread("dial.png");
	if (!img.data)
	{
		cout << "����ͼ���ļ������Ƿ�������ȷ" << endl;
		return -1;
	}

	Mat img1, img2;
	Point2f center = Point2f(img.cols / 2, img.rows/2);  //��������ͼ���е�ԭ��
	//��������任
	warpPolar(img, img1, Size(300,600), center, center.x, INTER_LINEAR + WARP_POLAR_LINEAR);
	//�漫����任
	warpPolar(img1, img2, Size(img.rows,img.cols), center, center.x, INTER_LINEAR + WARP_POLAR_LINEAR + WARP_INVERSE_MAP);

	imshow("ԭ����ͼ", img);
	imshow("���̼�����任���", img1); 
	imshow("��任���", img2);
	waitKey(0);
	return 0;
}