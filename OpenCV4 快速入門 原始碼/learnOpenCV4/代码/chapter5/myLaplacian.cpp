#include <opencv2\opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	//��ȡͼ�񣬺ڰ�ͼ���Ե�������Ϊ����
	Mat img = imread("equalLena.png", IMREAD_ANYDEPTH);
	if (img.empty())	{		cout << "��ȷ��ͼ���ļ������Ƿ���ȷ" << endl;		return -1;	}	Mat result, result_g, result_G;

	//δ�˲���ȡ��Ե
	Laplacian(img, result, CV_16S, 3, 1, 0);
	convertScaleAbs(result, result);

	//�˲�����ȡLaplacian��Ե
	GaussianBlur(img, result_g, Size(3, 3), 5, 0);  //��˹�˲�
	Laplacian(result_g, result_G, CV_16S, 3, 1, 0);
	convertScaleAbs(result_G, result_G);

	//��ʾͼ��
	imshow("result", result);
	imshow("result_G", result_G);
	waitKey(0);
	return 0;
}
