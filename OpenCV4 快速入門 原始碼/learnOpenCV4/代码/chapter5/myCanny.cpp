#include <opencv2\opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	//��ȡͼ�񣬺ڰ�ͼ���Ե�������Ϊ����
	Mat img = imread("equalLena.png", IMREAD_ANYDEPTH);
	if (img.empty())	{		cout << "��ȷ��ͼ���ļ������Ƿ���ȷ" << endl;		return -1;	}
	Mat resultHigh, resultLow, resultG;

	//����ֵ���ͼ���Ե
	Canny(img, resultHigh, 100, 200, 3);

	//С��ֵ���ͼ���Ե
	Canny(img, resultLow, 20, 40, 3);

	//��˹ģ������ͼ���Ե
	GaussianBlur(img, resultG, Size(3, 3), 5);
	Canny(resultG, resultG, 100, 200, 3);

	//��ʾͼ��
	imshow("resultHigh", resultHigh);
	imshow("resultLow", resultLow);
	imshow("resultG", resultG);
	waitKey(0);
	return 0;
}
