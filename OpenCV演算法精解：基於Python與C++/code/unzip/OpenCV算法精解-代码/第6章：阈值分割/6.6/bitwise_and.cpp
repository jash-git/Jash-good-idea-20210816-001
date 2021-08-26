#include<opencv2/core.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>
using namespace cv;
int main(int argc, char*argv[])
{
	//2����ֵͼͼ��
	Mat src1 = Mat::zeros(Size(100, 100), CV_8UC1);
	cv::rectangle(src1, Rect(25, 25, 50, 50), Scalar(255), CV_FILLED);
	imshow("src1", src1);
	Mat src2 = Mat::zeros(Size(100, 100), CV_8UC1);
	cv::circle(src2, Point(75, 50), 25, Scalar(255), CV_FILLED);
	imshow("src2", src2);
	//������
	Mat dst_and;
	bitwise_and(src1, src2, dst_and);
	imshow("������", dst_and);
	//������
	Mat dst_or;
	bitwise_or(src1, src2, dst_or);
	imshow("������", dst_or);
	//������
	Mat dst_not;
	bitwise_not(src1, dst_not);
	imshow("������",dst_not);
	waitKey(0);
	return 0;
}