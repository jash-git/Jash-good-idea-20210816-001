#include <opencv2\opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	system("color F0");  //�������������ɫ
	Mat sobel_x1, sobel_y1, sobel_x2, sobel_y2, sobel_x3, sobel_y3;  //��ŷ����Sobel����
	Mat scharr_x, scharr_y;  //��ŷ����Scharr����
	Mat sobelX1, sobelX2, sobelX3, scharrX;  //�����������

											 //һ��X����Sobel����
	getDerivKernels(sobel_x1, sobel_y1, 1, 0, 3);
	sobel_x1 = sobel_x1.reshape(CV_8U, 1);
	sobelX1 = sobel_y1*sobel_x1;  //�����˲���

								  //����X����Sobel����
	getDerivKernels(sobel_x2, sobel_y2, 2, 0, 5);
	sobel_x2 = sobel_x2.reshape(CV_8U, 1);
	sobelX2 = sobel_y2*sobel_x2;  //�����˲���

								  //����X����Sobel����
	getDerivKernels(sobel_x3, sobel_y3, 3, 0, 7);
	sobel_x3 = sobel_x3.reshape(CV_8U, 1);
	sobelX3 = sobel_y3*sobel_x3;  //�����˲���

								  //X����Scharr����
	getDerivKernels(scharr_x, scharr_y, 1, 0, FILTER_SCHARR);
	scharr_x = scharr_x.reshape(CV_8U, 1);
	scharrX = scharr_y*scharr_x;  //�����˲���

								  //������
	cout << "X����һ��Sobel����:" << endl << sobelX1 << endl;
	cout << "X�������Sobel����:" << endl << sobelX2 << endl;
	cout << "X��������Sobel����:" << endl << sobelX3 << endl;
	cout << "X����Scharr����:" << endl << scharrX << endl;
	waitKey(0);
	return 0;
}
