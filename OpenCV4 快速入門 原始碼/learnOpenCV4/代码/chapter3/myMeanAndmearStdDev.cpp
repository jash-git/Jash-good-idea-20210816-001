#include <opencv2\opencv.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

int main()
{
	system("color F0");  //�������������ɫ
	float a[12] = { 1, 2, 3, 4, 5, 10, 6, 7, 8, 9, 10, 0 };
	Mat img = Mat(3, 4, CV_32FC1, a);  //��ͨ������
	Mat imgs = Mat(2, 3, CV_32FC2, a);  //��ͨ������

	cout << "/* ��meanStdDevͬʱ��ȡͼ��ľ�ֵ�ͱ�׼�� */" << endl;
	Scalar myMean;
	myMean = mean(imgs);
	cout << "imgs��ֵ=" << myMean << endl;
	cout << "imgs��һ��ͨ���ľ�ֵ=" << myMean[0] << "    "
		<< "imgs�ڶ���ͨ���ľ�ֵ=" << myMean[1] << endl << endl;

	cout << "/* ��meanStdDevͬʱ��ȡͼ��ľ�ֵ�ͱ�׼�� */" << endl;
	Mat myMeanMat, myStddevMat;

	meanStdDev(img, myMeanMat, myStddevMat);
	cout << "img��ֵ=" << myMeanMat << "    " << endl;
	cout << "img��׼��=" << myStddevMat << endl << endl;
	meanStdDev(imgs, myMeanMat, myStddevMat);
	cout << "imgs��ֵ=" << myMeanMat << "    " << endl << endl;
	cout << "imgs��׼��=" << myStddevMat << endl;
	return 0;
}