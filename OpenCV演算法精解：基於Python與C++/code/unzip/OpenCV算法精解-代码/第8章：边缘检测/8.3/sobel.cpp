#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
#include<iostream>
using namespace std;
//计算阶乘
int factorial(int n)
{
	int fac = 1;
	// 0 的阶乘等于 1
	if (n == 0)
		return fac;
	for (int i = 1; i <= n; i++)
		fac *= i;
	return fac;
}
//计算平滑系数
Mat getPascalSmooth(int n)
{
	Mat pascalSmooth = Mat::zeros(Size(n, 1), CV_32FC1);
	for (int i = 0; i < n; i++)
		pascalSmooth.at<float>(0, i) = factorial(n - 1) / (factorial(i) * factorial(n - 1 - i));
	return pascalSmooth;
}
//计算差分
Mat getPascalDiff(int n)
{
	Mat pascalDiff = Mat::zeros(Size(n, 1), CV_32FC1);
	Mat pascalSmooth_previous = getPascalSmooth(n - 1);
	for (int i = 0; i<n; i++)
	{
		if (i == 0)
			pascalDiff.at<float>(0, i) = 1;
		else if (i == n - 1)
			pascalDiff.at<float>(0, i) = -1;
		else
			pascalDiff.at<float>(0, i) = pascalSmooth_previous.at<float>(0, i) - pascalSmooth_previous.at<float>(0, i - 1);
	}
	return pascalDiff;
}
/*离散的二维卷积运算*/
void conv2D(InputArray _src, InputArray _kernel, OutputArray _dst, int ddepth, Point anchor = Point(-1, -1), int borderType = BORDER_DEFAULT)
{
	//卷积核顺时针旋转180
	Mat kernelFlip;
	flip(_kernel, kernelFlip, -1);
	//针对每一个像素,领域对应元素相乘然后相加
	filter2D(_src, _dst, ddepth, kernelFlip, anchor, 0.0, borderType);
}
/*可分离的离散二维卷积,先垂直方向的卷积，然后进行水平方向的卷积*/
void sepConv2D_Y_X(InputArray src, OutputArray src_kerY_kerX, int ddepth, InputArray kernelY, InputArray kernelX, Point anchor = Point(-1, -1), int borderType = BORDER_DEFAULT)
{
	//输入矩阵与垂直方向卷积核的卷积
	Mat src_kerY;
	conv2D(src, kernelY, src_kerY, ddepth, anchor, borderType);
	//上面得到的卷积结果，然后接着和水平方向的卷积核卷积
	conv2D(src_kerY, kernelX, src_kerY_kerX, ddepth, anchor, borderType);
}
/*可分离的离散二维卷积，先水平方向的卷积,然后接着进行垂直方向的卷积，最后的输出类型是 CV_32FC1 或者 CV_64FC1*/
void sepConv2D_X_Y(InputArray src, OutputArray src_kerX_kerY, int ddepth, InputArray kernelX, InputArray kernelY, Point anchor = Point(-1, -1), int borderType = BORDER_DEFAULT)
{
	//输入矩阵与水平方向卷积核的卷积
	Mat src_kerX;
	conv2D(src, kernelX, src_kerX, CV_32F, anchor, borderType);
	//上面得到的卷积结果，然后接着和垂直方向的卷积核卷积
	conv2D(src_kerX, kernelY, src_kerX_kerY, ddepth, anchor, borderType);
}
// sobel 边缘检测
Mat sobel(Mat image, int x_flag, int y_flag, int winSize, int borderType)
{
	// sobel 卷积核的窗口大小为大于 3 的奇数 
	CV_Assert(winSize >= 3 && winSize % 2 == 1);
	//平滑系数
	Mat pascalSmooth = getPascalSmooth(winSize);
	//差分系数
	Mat pascalDiff = getPascalDiff(winSize);
	Mat image_con_sobel;
	/* 当 x_falg != 0 时，返回图像与水平方向的 Sobel 核的卷积*/
	if (x_flag != 0)
	{
		//根据可分离卷积核的性质
		//先进行一维垂直方向上的平滑，再进行一维水平方向的差分
		sepConv2D_Y_X(image, image_con_sobel, CV_32FC1, pascalSmooth.t(), pascalDiff, Point(-1, -1), borderType);
	}
	/* 当 x_falg == 0 且 y_flag != 0 时，返回图像与垂直 方向的 Sobel 核的卷积*/
	if (x_flag == 0 && y_flag != 0)
	{
		//根据可分离卷积核的性质
		//先进行一维水平方向上的平滑，再进行一维垂直方向的差分
		sepConv2D_X_Y(image, image_con_sobel, CV_32FC1, pascalSmooth, pascalDiff.t(), Point(-1, -1), borderType);
	}
	return image_con_sobel;
}
int main(int argc, char*argv[])
{
	//输入图片矩阵
	Mat image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if (!image.data)
		return -1;
	/* --- sobel 边缘检测 --- */
	//与水平方向的 sobel 核卷积
	Mat image_Y_X = sobel(image, 1, 0, 3, 4);
	//垂直方向的边缘强度
	Mat imageYX_abs = abs(image_Y_X);
	//垂直方向边缘强度的灰度级显示
	Mat imageYX_gray;
	imageYX_abs.convertTo(imageYX_gray, CV_8UC1, 1.0, 0);
	imshow("垂直方向的边缘强度", imageYX_gray);
	//与垂直方向的 sobel 核卷积
	Mat image_X_Y = sobel(image, 0, 1, 3, 4);
	//水平方向的边缘强度
	Mat imageXY_abs = abs(image_X_Y);
	//水平方向边缘强度的灰度级显示
	Mat imageXY_gray;
	imageXY_abs.convertTo(imageXY_gray, CV_8UC1, 1.0, 0);
	imshow("水平方向的边缘强度", imageXY_gray);
	//根据垂直方向和水平方向边缘强度的平方和，得到最终的边缘强度
	Mat edge;
	magnitude(image_Y_X, image_X_Y, edge);
	//边缘强度的灰度级显示
	edge.convertTo(edge, CV_8UC1, 1.0, 0);
	imshow("边缘", edge);
	imwrite("sobeledge.jpg", edge);
	waitKey(0);
	return 0;
}