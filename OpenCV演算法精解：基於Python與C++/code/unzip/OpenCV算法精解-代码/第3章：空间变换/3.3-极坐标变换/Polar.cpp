#include<iostream>
using namespace std;
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;

Mat polar(Mat I, Point2f center, Size size, float minr = 0, float mintheta = 0, float thetaStep = 1.0 / 4, float rStep = 1.0)
{
	Mat ri = Mat::zeros(Size(1, size.height), CV_32FC1);
	for (int i = 0; i < size.height; i++)
	{
		ri.at<float>(i, 0) = minr + i*rStep;
	}
	Mat r = repeat(ri, 1, size.width);

	Mat thetaj = Mat::zeros(Size(size.width, 1), CV_32FC1);
	for (int j = 0; j < size.width; j++)
	{
		thetaj.at<float>(0, j) = mintheta + j*thetaStep;
	}
	Mat theta = repeat(thetaj, size.height, 1);
	//������ת��Ϊ�ѿ�������
	Mat x, y;
	polarToCart(r, theta, x, y, true);
	//������ԭ���ƶ������ĵ�
	x += center.x;
	y += center.y;
	//����ڲ�ֵ
	Mat dst = 125 * Mat::ones(size, CV_8UC1);
	for (int i = 0; i < size.height; i++)
	{
		for (int j = 0; j < size.width; j++)
		{
			float xij = x.at<float>(i, j);
			float yij = y.at<float>(i, j);
			int nearestx = int(round(xij));
			int nearesty = int(round(yij));
			if ((0 <= nearestx&& nearestx < I.cols) &&
				(0 <= nearesty&& nearesty < I.rows))
				dst.at<uchar>(i, j) = I.at<uchar>(nearesty, nearestx);
		}
	}
	return dst;
}

int main(int argc, char*argv[])
{
	//����ͼ��
	Mat I = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if (!I.data)
		return -1;
	//ͼ��ļ�����任
	float thetaStep = 1.0 / 4;
	float minr = 270;
	Size size(int(360 / thetaStep), 70);
	Mat dst = polar(I, Point2f(508, 503), size, minr);
	//��ˮƽ�����Ͼ�����
	flip(dst, dst, 0);
	//��ʾԭͼ�ͱ任��Ľ��
	imshow("I", I);
	imshow("������任", dst);
	waitKey(0);
	return 0;
}
