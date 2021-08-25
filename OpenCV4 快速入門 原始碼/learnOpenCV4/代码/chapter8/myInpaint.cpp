#include <opencv2\opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat img1 = imread("inpaint1.png");
	Mat img2 = imread("inpaint2.png");
	if (img1.empty() || img2.empty())
	{
		cout << "��ȷ��ͼ���ļ������Ƿ���ȷ" << endl;
		return -1;
	}
	imshow("img1", img1);
	imshow("img2", img2);

	//ת��Ϊ�Ҷ�ͼ
	Mat img1Gray, img2Gray;
	cvtColor(img1, img1Gray, COLOR_RGB2GRAY, 0);
	cvtColor(img2, img2Gray, COLOR_RGB2GRAY, 0);

	//ͨ����ֵ��������Mask��ģ
	Mat img1Mask, img2Mask;
	threshold(img1Gray, img1Mask, 245, 255, THRESH_BINARY);
	threshold(img2Gray, img2Mask, 245, 255, THRESH_BINARY);

	//��Mask���ʹ�������Mask���
	Mat Kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(img1Mask, img1Mask, Kernel);
	dilate(img2Mask, img2Mask, Kernel);

	//ͼ���޸�
	Mat img1Inpaint, img2Inpaint;
	inpaint(img1, img1Mask, img1Inpaint, 5, INPAINT_NS);
	inpaint(img2, img2Mask, img2Inpaint, 5, INPAINT_NS);

	//��ʾ������
	imshow("img1Mask", img1Mask);
	imshow("img1�޸���", img1Inpaint);
	imshow("img2Mask", img2Mask);
	imshow("img2�޸���", img2Inpaint);
	waitKey();
	return 0;
}
