#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat img = imread("coins.png");
	if (!img.data)
	{
		cout << "��ȡͼ�������ȷ��ͼ���ļ��Ƿ���ȷ" << endl;
		return -1;
	}

	//�ָ��
	Mat result1, result2;
	TermCriteria T10 = TermCriteria(TermCriteria::COUNT | TermCriteria::EPS, 10, 0.1);
	pyrMeanShiftFiltering(img, result1, 20, 40, 2, T10);  //��һ�ηָ�
	pyrMeanShiftFiltering(result1, result2, 20, 40, 2, T10);  //��һ�ηָ�Ľ���ٴηָ�

															  //��ʾ�ָ���
	imshow("img", img);
	imshow("result1", result1);
	imshow("result2", result2);

	//��ͼ����ȡCanny��Ե
	Mat imgCanny, result1Canny, result2Canny;
	Canny(img, imgCanny, 150, 300);
	Canny(result1, result1Canny, 150, 300);
	Canny(result2, result2Canny, 150, 300);

	//��ʾ��Ե�����
	imshow("imgCanny", imgCanny);
	imshow("result1Canny", result1Canny);
	imshow("result2Canny", result2Canny);
	waitKey(0);
	return 0;
}
