#include <opencv2\opencv.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

int main()
{
	//�������ڸ�ʴ��ԭͼ��
	Mat src = (Mat_<uchar>(6, 6) << 0, 0, 0, 0, 255, 0,
		0, 255, 255, 255, 255, 255,
		0, 255, 255, 255, 255, 0,
		0, 255, 255, 255, 255, 0,
		0, 255, 255, 255, 255, 0,
		0, 0, 0, 0, 0, 0);
	Mat struct1, struct2;
	struct1 = getStructuringElement(0, Size(3, 3));  //���νṹԪ��
	struct2 = getStructuringElement(1, Size(3, 3));  //ʮ�ֽṹԪ��

	Mat erodeSrc;  //������ͺ��ͼ��
	dilate(src, erodeSrc, struct2);
	namedWindow("src", WINDOW_GUI_NORMAL);
	namedWindow("dilateSrc", WINDOW_GUI_NORMAL);
	imshow("src", src);
	imshow("dilateSrc", erodeSrc);

	Mat LearnCV_black = imread("LearnCV_black.png", IMREAD_ANYCOLOR);
	Mat LearnCV_write = imread("LearnCV_write.png", IMREAD_ANYCOLOR);
	if (LearnCV_black.empty() || LearnCV_write.empty())
	{
		cout << "��ȷ��ͼ���ļ������Ƿ���ȷ" << endl;		return -1;
	}

	Mat dilate_black1, dilate_black2, dilate_write1, dilate_write2;
	//�ڱ���ͼ������
	dilate(LearnCV_black, dilate_black1, struct1);
	dilate(LearnCV_black, dilate_black2, struct2);
	imshow("LearnCV_black", LearnCV_black);
	imshow("dilate_black1", dilate_black1);
	imshow("dilate_black2", dilate_black2);

	//�ױ���ͼ������
	dilate(LearnCV_write, dilate_write1, struct1);
	dilate(LearnCV_write, dilate_write2, struct2);
	imshow("LearnCV_write", LearnCV_write);
	imshow("dilate_write1", dilate_write1);
	imshow("dilate_write2", dilate_write2);

	//�Ƚ����ͺ͸�ʴ�Ľ��
	Mat erode_black1, resultXor, resultAnd;
	erode(LearnCV_black, erode_black1, struct1);
	bitwise_xor(erode_black1, dilate_write1, resultXor);
	bitwise_and(erode_black1, dilate_write1, resultAnd);
	imshow("resultXor", resultXor);
	imshow("resultAnd", resultAnd);
	waitKey(0);
	return 0;
}
