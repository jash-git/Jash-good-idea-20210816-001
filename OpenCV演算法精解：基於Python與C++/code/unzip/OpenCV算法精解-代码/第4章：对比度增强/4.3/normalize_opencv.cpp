#include<opencv2/core.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>
using namespace cv;
#include<iostream>
using namespace std;
int main(int argc, char*argv[])
{
	/*
	//�������
	Mat src = (Mat_<float>(2, 2) << -55, 80, 100, 255);
	// MINMAX
	Mat dst;
	normalize(src, dst, 1, 0,NORM_MINMAX, CV_32FC1);
	cout << dst << endl;
	*/
	//����ͼ��
	Mat src = imread(argv[1], CV_LOAD_IMAGE_ANYCOLOR);
	if (!src.data)
		return -1;
	//ֱ��ͼ���滯
	Mat dst;
	normalize(src, dst, 255, 0, NORM_MINMAX, CV_8U);
	//��ʾ
	imshow("ԭͼ", src);
	imshow("ֱ��ͼ���滯", dst);
	waitKey(0);
	return 0;
}