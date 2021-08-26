#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
#include<iostream>
using namespace std;
/*离散的二维卷积运算*/
void conv2D(InputArray _src, InputArray _kernel, OutputArray _dst, int ddepth, Point anchor = Point(-1, -1), int borderType = BORDER_DEFAULT)
{
	//卷积核顺时针旋转180
	Mat kernelFlip;
	flip(_kernel, kernelFlip, -1);
	//针对每一个像素,领域对应元素相乘然后相加
	filter2D(_src, _dst, ddepth, kernelFlip, anchor, 0.0, borderType);
}
int main(int argc, char*argv[])
{
	//输入矩阵
	Mat src = (Mat_<float>(2, 2) << 1,2,3,4);
	//卷积核
	Mat kernel = (Mat_<int>(2, 2) << -1, -2, 2, 1);
	Mat result;
	//二维离散的same卷积
	conv2D(src, kernel, result, CV_32FC1, Point(0, 0),BORDER_CONSTANT);
	//打印结果
	for (int r = 0; r < result.rows; r++)
	{
		for (int c = 0; c < result.cols; c++)
		{
			cout << result.at<float>(r, c) << ",";
		}
		cout << endl;
	}
	return 0;
}