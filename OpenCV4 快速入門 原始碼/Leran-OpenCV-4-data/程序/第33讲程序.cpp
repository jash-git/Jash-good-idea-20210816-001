#include <opencv2\opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	//��ȡͼ�񣬺ڰ�ͼ���Ե�������Ϊ����
	Mat img = imread("equalLena.png", IMREAD_ANYCOLOR);
	if (img.empty())
	{
		cout << "��ȷ��ͼ���ļ������Ƿ���ȷ" << endl;
		return -1;
	}
	Mat resultX, resultY, resultXY;

	//X����һ�ױ�Ե
	Sobel(img, resultX, CV_16S, 1, 0, 1);
	convertScaleAbs(resultX, resultX);

	//Y����һ�ױ�Ե
	Sobel(img, resultY, CV_16S, 0, 1, 3);
	convertScaleAbs(resultY, resultY);

	//����ͼ���һ�ױ�Ե
	resultXY = resultX + resultY;

	//��ʾͼ��
	imshow("resultX", resultX);
	imshow("resultY", resultY);
	imshow("resultXY", resultXY);

	cout << "����������Scharr��Ե�ļ��" << endl;
	waitKey(0);

	//X����һ�ױ�Ե
	Scharr(img, resultX, CV_16S, 1, 0);
	convertScaleAbs(resultX, resultX);

	//Y����һ�ױ�Ե
	Scharr(img, resultY, CV_16S, 0, 1);
	convertScaleAbs(resultY, resultY);

	//����ͼ���һ�ױ�Ե
	resultXY = resultX + resultY;

	//��ʾͼ��
	imshow("resultX", resultX);
	imshow("resultY", resultY);
	imshow("resultXY", resultXY);

	cout << "���������ɱ�Ե�����" << endl;
	waitKey(0);


	Mat sobel_x1, sobel_y1; //��ŷ����Sobel����
	Mat scharr_x, scharr_y;  //��ŷ����Scharr����
	Mat sobelX1, scharrX;  //�����������

						   //һ��X����Sobel����
	getDerivKernels(sobel_x1, sobel_y1, 1, 0, 3);
	sobel_x1 = sobel_x1.reshape(CV_8U, 1);
	sobelX1 = sobel_y1*sobel_x1;  //�����˲���

								  //X����Scharr����
	getDerivKernels(scharr_x, scharr_y, 1, 0, FILTER_SCHARR);
	scharr_x = scharr_x.reshape(CV_8U, 1);
	scharrX = scharr_y*scharr_x;  //�����˲���

								  //������
	cout << "X����һ��Sobel����:" << endl << sobelX1 << endl;

	cout << "X����Scharr����:" << endl << scharrX << endl;

	waitKey(0);
	return 0;
}


