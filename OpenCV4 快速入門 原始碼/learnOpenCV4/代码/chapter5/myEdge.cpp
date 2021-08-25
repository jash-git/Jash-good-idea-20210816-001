#include <opencv2\opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	//������Ե����˲���
	Mat kernel1 = (Mat_<float>(1, 2) << 1, -1);  //X�����Ե����˲���
	Mat kernel2 = (Mat_<float>(1, 3) << 1, 0, -1);  //X�����Ե����˲���
	Mat kernel3 = (Mat_<float>(3, 1) << 1, 0, -1);  //X�����Ե����˲���
	Mat kernelXY = (Mat_<float>(2, 2) << 1, 0, 0, -1);  //�����ϵ����·����Ե����˲���
	Mat kernelYX = (Mat_<float>(2, 2) << 0, -1, 1, 0);  //�����ϵ����·����Ե����˲���

														//��ȡͼ�񣬺ڰ�ͼ���Ե�������Ϊ����
	Mat img = imread("equalLena.png", IMREAD_ANYCOLOR);
	if (img.empty())	{		cout << "��ȷ��ͼ���ļ������Ƿ���ȷ" << endl;		return -1;	}
	Mat result1, result2, result3, result4, result5, result6;

	//���ͼ���Ե
	//��[1 -1]���ˮƽ�����Ե
	filter2D(img, result1, CV_16S, kernel1);
	convertScaleAbs(result1, result1);

	//��[1 0 -1]���ˮƽ�����Ե
	filter2D(img, result2, CV_16S, kernel2);
	convertScaleAbs(result2, result2);

	//��[1 0 -1]'����ɴ�ֱ�����Ե
	filter2D(img, result3, CV_16S, kernel3);
	convertScaleAbs(result3, result3);

	//����ͼ��ı�Ե
	result6 = result2 + result3;
	//��������ϵ����·����Ե
	filter2D(img, result4, CV_16S, kernelXY);
	convertScaleAbs(result4, result4);

	//��������ϵ����·����Ե
	filter2D(img, result5, CV_16S, kernelYX);
	convertScaleAbs(result5, result5);

	//��ʾ��Ե�����
	imshow("result1", result1);
	imshow("result2", result2);
	imshow("result3", result3);
	imshow("result4", result4);
	imshow("result5", result5);
	imshow("result6", result6);
	waitKey(0);
	return 0;
}