#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
using namespace cv;
#include<iostream>
using namespace std;
int main(int argc, char*argv[])
{
	//����ͼ��
	Mat src = imread(argv[1], IMREAD_ANYCOLOR);
	if (!src.data)
		return -1;
	//������任
	Mat dst;
	linearPolar(src, dst, Point2f(508, 503), 550, CV_INTER_LINEAR);
	cout << src.size() << endl;
	cout << float(360)/dst.size().height << endl;
	cout << float(550) / dst.size().width << endl;
	//��ʾԭͼ�ͼ�����任ͼ
	imshow("ԭͼ", src);
	imshow("������任ͼ", dst);
	//imwrite("dst.jpg", dst);
	waitKey(0);
	return 0;
}