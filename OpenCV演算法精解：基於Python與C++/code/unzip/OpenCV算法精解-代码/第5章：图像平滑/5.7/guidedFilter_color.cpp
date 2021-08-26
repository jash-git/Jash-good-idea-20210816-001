#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
#include<iostream>
using namespace std;
//导向滤波 返回值类型为 64FC1 
Mat guidedFilter(Mat I, Mat p, int r, float eps, float s)
{
	//输入图像的宽高
	int rows = I.rows;
	int cols = I.cols;
	//缩小图像
	Mat small_I, small_p;
	Size smallSize(int(round(s*cols)), int(round(s*rows)));
	resize(I, small_I, smallSize,0,0,CV_INTER_CUBIC);
	resize(p, small_p, smallSize, 0, 0, CV_INTER_CUBIC);
	//缩放均值平滑的窗口半径
	int small_r = int(round(r*s));//确保是整型
	Size winSize(2 * small_r + 1, 2 * small_r + 1);
	//均值平滑
	Mat mean_small_I, mean_small_p;
	boxFilter(small_I, mean_small_I, CV_64FC1, winSize);
	boxFilter(small_p, mean_small_p, CV_64FC1, winSize);
	// small_I .* small_p 的均值平滑
	Mat small_Ip = small_I.mul(small_p);
	Mat mean_small_Ip;
	boxFilter(small_Ip, mean_small_Ip, CV_64FC1,winSize);
	//协方差
	Mat cov_small_Ip = mean_small_Ip - mean_small_I.mul(mean_small_p);
	//均值平滑
	Mat mean_small_II;
	boxFilter(small_I.mul(small_I), mean_small_II, CV_64FC1,winSize);
	//方差
	Mat var_small_I = mean_small_II - mean_small_I.mul(mean_small_I);
	Mat small_a = cov_small_Ip/(var_small_I + eps);
	Mat small_b = mean_small_p - small_a.mul(mean_small_I);
	//对 small_a 和 small_b 进行均值平滑
	Mat mean_small_a, mean_small_b;
	boxFilter(small_a, mean_small_a, CV_64FC1, winSize);
	boxFilter(small_b, mean_small_b, CV_64FC1, winSize);
	//放大
	Mat mean_a, mean_b;
	resize(mean_small_a, mean_a, I.size(), 0, 0, CV_INTER_LINEAR);
	resize(mean_small_b, mean_b, I.size(), 0, 0, CV_INTER_LINEAR);
	Mat q = mean_a.mul(I) + mean_b;
	return q;
}
//彩色导向滤波
Mat guidedFilterColor(Mat I, int r, float eps, float s)
{
	//分离通道
	vector<Mat> Is;
	split(I, Is);
	//每一个通道进行导向滤波
	vector<Mat> qs;
	qs.clear();
	for (int i = 0; i < 3; i++)
	{
		Mat q = guidedFilter(Is[i], Is[i], r, eps, s);
		qs.push_back(q);
	}
	//各个通道整合
	Mat q_color;
	merge(qs, q_color);
	return q_color;
}
//细节增强
Mat guidedEnchance(Mat I, int r, float eps, float s)
{
	//导向滤波（平滑）
	Mat q = guidedFilterColor(I, r, eps, s);
	Mat I_enhanced = (I - q) * 5 + q;
	//归一化
	normalize(I_enhanced, I_enhanced, 1.0, 0,NORM_MINMAX);
	return I_enhanced;
}
int main(int argc, char*argv[])
{
	//输入彩色图像
	Mat image = imread(argv[1],CV_LOAD_IMAGE_COLOR);
	if (!image.data || image.channels()!=3)
		return -1;
	//图像归一化
	image.convertTo(image, CV_64FC1, 1.0 / 255);
	imshow("原图", image);
	//彩色导向滤波(平滑)
	Mat result = guidedFilterColor(image,7,0.04,0.3);
	imshow("导向滤波", result);
	//细节增强
	Mat I_enhanced = guidedEnchance(image, 16, 0.01,0.4);
	imshow("细节增强", I_enhanced);
	waitKey(0);
	return 0;
}