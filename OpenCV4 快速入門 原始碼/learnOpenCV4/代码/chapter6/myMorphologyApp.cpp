#include <opencv2\opencv.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

int main()
{
	//������֤��̬ѧӦ�õĶ�ֵ������
	Mat src = (Mat_<uchar>(9, 12) << 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 255, 255, 255, 255, 255, 255, 255, 0, 0, 255, 0,
		0, 255, 255, 255, 255, 255, 255, 255, 0, 0, 0, 0,
		0, 255, 255, 255, 255, 255, 255, 255, 0, 0, 0, 0,
		0, 255, 255, 255, 0, 255, 255, 255, 0, 0, 0, 0,
		0, 255, 255, 255, 255, 255, 255, 255, 0, 0, 0, 0,
		0, 255, 255, 255, 255, 255, 255, 255, 0, 0, 255, 0,
		0, 255, 255, 255, 255, 255, 255, 255, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	namedWindow("src", WINDOW_NORMAL);  //�������ɵ�����ʾͼ��ĳߴ�
	imshow("src", src);
	//3��3���νṹԪ��
	Mat kernel = getStructuringElement(0, Size(3, 3));

	//�Զ�ֵ�����������̬ѧ����
	Mat open, close, gradient, tophat, blackhat, hitmiss;

	//�Զ�ֵ��������п�����
	morphologyEx(src, open, MORPH_OPEN, kernel);
	namedWindow("open", WINDOW_NORMAL);  //�������ɵ�����ʾͼ��ĳߴ�
	imshow("open", open);

	//�Զ�ֵ��������б�����
	morphologyEx(src, close, MORPH_CLOSE, kernel);
	namedWindow("close", WINDOW_NORMAL);  //�������ɵ�����ʾͼ��ĳߴ�
	imshow("close", close);

	//�Զ�ֵ����������ݶ�����
	morphologyEx(src, gradient, MORPH_GRADIENT, kernel);
	namedWindow("gradient", WINDOW_NORMAL);  //�������ɵ�����ʾͼ��ĳߴ�
	imshow("gradient", gradient);

	//�Զ�ֵ��������ж�ñ����
	morphologyEx(src, tophat, MORPH_TOPHAT, kernel);
	namedWindow("tophat", WINDOW_NORMAL);  //�������ɵ�����ʾͼ��ĳߴ�
	imshow("tophat", tophat);

	//�Զ�ֵ��������к�ñ����
	morphologyEx(src, blackhat, MORPH_BLACKHAT, kernel);
	namedWindow("blackhat", WINDOW_NORMAL);   //�������ɵ�����ʾͼ��ĳߴ�
	imshow("blackhat", blackhat);

	//�Զ�ֵ��������л��л����б任
	morphologyEx(src, hitmiss, MORPH_HITMISS, kernel);
	namedWindow("hitmiss", WINDOW_NORMAL);  //�������ɵ�����ʾͼ��ĳߴ�
	imshow("hitmiss", hitmiss);

	//��ͼ����֤��̬ѧ����Ч��
	Mat keys = imread("keys.jpg",IMREAD_GRAYSCALE);
	imshow("ԭͼ��", keys);
	threshold(keys, keys, 80, 255, THRESH_BINARY);
	imshow("��ֵ�����keys", keys);

	//5��5���νṹԪ��
	Mat kernel_keys = getStructuringElement(0, Size(5, 5));
	Mat open_keys, close_keys, gradient_keys, tophat_keys, blackhat_keys, hitmiss_keys;

	//��ͼ����п�����
	morphologyEx(keys, open_keys, MORPH_OPEN, kernel_keys);
	imshow("open_keys", open_keys);

	//��ͼ����б�����
	morphologyEx(keys, close_keys, MORPH_CLOSE, kernel_keys);
	imshow("close_keys", close_keys);

	//��ͼ������ݶ�����
	morphologyEx(keys, gradient_keys, MORPH_GRADIENT, kernel_keys);
	imshow("gradient_keys", gradient_keys);

	//��ͼ����ж�ñ����
	morphologyEx(keys, tophat_keys, MORPH_TOPHAT, kernel_keys);
	imshow("tophat_keys", tophat_keys);

	//��ͼ����к�ñ����
	morphologyEx(keys, blackhat_keys, MORPH_BLACKHAT, kernel_keys);
	imshow("blackhat_keys", blackhat_keys);

	//��ͼ����л��л����б任
	morphologyEx(keys, hitmiss_keys, MORPH_HITMISS, kernel_keys);
	imshow("hitmiss_keys", hitmiss_keys);

	waitKey(0);
	return 0;
}