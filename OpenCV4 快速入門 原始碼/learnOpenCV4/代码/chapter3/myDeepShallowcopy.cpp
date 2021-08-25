#include <opencv2\opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat img = imread("lena.png");
	Mat noobcv = imread("noobcv.jpg");
	if (img.empty() || noobcv.empty())
	{
		cout << "��ȷ��ͼ���ļ������Ƿ���ȷ" << endl;		return -1;
	}
	Mat ROI1, ROI2, ROI2_copy, mask, img2, img_copy, img_copy2;
	resize(noobcv, mask, Size(200, 200));
	img2 = img;  //ǳ����
				 //��������ַ�ʽ
	img.copyTo(img_copy2);
	copyTo(img, img_copy, img);
	//������ͼ�н�ȡROI����ķ�ʽ
	Rect rect(206, 206, 200, 200);  //����ROI����
	ROI1 = img(rect);  //��ͼ
	ROI2 = img(Range(300, 500), Range(300, 500));  //�ڶ��ֽ�ͼ��ʽ
	img(Range(300, 500), Range(300, 500)).copyTo(ROI2_copy);  //���
	mask.copyTo(ROI1);  //��ͼ���м��벿��ͼ��
	imshow("����noobcv��ͼ��", img);
	imshow("ROI��ROI2��Ӱ��", ROI2);
	imshow("�����ROI2_copy", ROI2_copy);
	circle(img, Point(300, 300), 20, Scalar(0, 0, 255), -1);  //����һ��Բ��
	imshow("ǳ������img2", img2);
	imshow("�����img_copy", img_copy);
	imshow("�����img_copy2", img_copy2);
	imshow("��Բ��ROI1��Ӱ��", ROI1);
	waitKey(0);
	return 0;
}