#include <opencv2\opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat img = imread("lena.png");
	Mat temp = imread("lena_face.png");
	if (img.empty() || temp.empty())
	{
		cout << "��ȷ��ͼ���ļ������Ƿ���ȷ" << endl;		return -1;
	}
	Mat result;
	matchTemplate(img, temp, result, TM_CCOEFF_NORMED);//ģ��ƥ��
	double maxVal, minVal;
	Point minLoc, maxLoc;
	//Ѱ��ƥ�����е����ֵ����Сֵ�Լ�����λ��
	minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);
	//�������ƥ������
	rectangle(img, cv::Rect(maxLoc.x, maxLoc.y, temp.cols, temp.rows), Scalar(0, 0, 255), 2);
	imshow("ԭͼ", img);
	imshow("ģ��ͼ��", temp);
	imshow("result", result);
	waitKey(0);
	return 0;
}