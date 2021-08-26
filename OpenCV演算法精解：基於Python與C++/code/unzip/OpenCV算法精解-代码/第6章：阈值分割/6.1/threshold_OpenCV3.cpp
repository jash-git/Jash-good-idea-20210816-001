#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
#include<iostream>
using namespace std;
int main(int argc, char*argv[])
{
	//输入矩阵 5 行 3列
	Mat src = (Mat_<uchar>(5, 3) << 123, 234, 68, 33, 51, 17,
		48, 98, 234, 129, 89, 27, 45, 167, 134);
	//第一种情况：手动设置阈值
	double the = 150;
	Mat dst;
	threshold(src, dst, the, 255, THRESH_BINARY);
	//第二种情况：Otsu 算法
	double otsuThe=0;
	Mat dst_Otsu;
	otsuThe = threshold(src, dst_Otsu, otsuThe, 255, THRESH_OTSU+ THRESH_BINARY);
	cout << "计算的Otsu阈值：" << otsuThe << endl;
	//第二种情况：TRIANGLE 算法
	double triThe=0;
	Mat dst_tri;
	triThe = threshold(src, dst_tri, 0, 255, THRESH_TRIANGLE+ THRESH_BINARY);
	cout << "计算的TRIANGLE阈值:" << triThe << endl;
	return 0;
}