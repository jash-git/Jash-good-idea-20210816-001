#include <opencv2\opencv.hpp>
#include <opencv2\ximgproc.hpp>  //ϸ������thining���ڵ�ͷ�ļ�
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	//�����ֽ���ϸ��
	Mat img = imread("LearnCV_black.png", IMREAD_ANYCOLOR);
	if (img.empty())	{		cout << "��ȷ��ͼ���ļ������Ƿ���ȷ" << endl;		return -1;	}	//Ӣ����+ʵ��Բ��Բ��ϸ��
	Mat words = Mat::zeros(100, 200, CV_8UC1);  //����һ����ɫ�ı���ͼƬ
	putText(words, "Learn", Point(30, 30), 2, 1, Scalar(255), 2);  //���Ӣ��
	putText(words, "OpenCV 4", Point(30, 60), 2, 1, Scalar(255), 2);
	circle(words, Point(80, 75), 10, Scalar(255), -1);  //���ʵ��Բ
	circle(words, Point(130, 75), 10, Scalar(255), 3);  //���Բ��

	//����ϸ��
	Mat thin1, thin2;
	ximgproc::thinning(img, thin1, 0);  //ע������
	ximgproc::thinning(words, thin2, 0);

	//��ʾ������
	imshow("thin1", thin1);
	imshow("img", img);
	namedWindow("thin2", WINDOW_NORMAL);
	imshow("thin2", thin2);
	namedWindow("words", WINDOW_NORMAL);
	imshow("words", words);
	waitKey(0);
	return 0;
}