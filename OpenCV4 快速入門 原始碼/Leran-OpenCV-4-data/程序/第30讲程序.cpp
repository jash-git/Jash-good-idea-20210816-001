#include <opencv2\opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat equalLena = imread("equalLena.png", IMREAD_ANYDEPTH);
	Mat equalLena_gauss = imread("equalLena_gauss.png", IMREAD_ANYDEPTH);
	Mat equalLena_salt = imread("equalLena_salt.png", IMREAD_ANYDEPTH);

	if (equalLena.empty() || equalLena_gauss.empty() || equalLena_salt.empty())
	{
		cout << "请确认图像文件名称是否正确" << endl;
		return -1;
	}

	Mat result_3, result_9;  //存放不含噪声滤波结果，后面数字代表滤波器尺寸
	Mat result_3gauss, result_9gauss;  //存放含有高斯噪声滤波结果，后面数字代表滤波器尺寸
	Mat result_3salt, result_9salt;  //存放含有椒盐噪声滤波结果，后面数字代表滤波器尺寸
	
    //调用均值滤波函数blur()进行滤波
	blur(equalLena, result_3, Size(3, 3));
	blur(equalLena, result_9, Size(9, 9));
	blur(equalLena_gauss, result_3gauss, Size(3, 3));
	blur(equalLena_gauss, result_9gauss, Size(9, 9));
	blur(equalLena_salt, result_3salt, Size(3, 3));
	blur(equalLena_salt, result_9salt, Size(9, 9));


	//显示不含噪声图像
	imshow("equalLena ", equalLena);
	imshow("result_3", result_3);
	imshow("result_9", result_9);
	//显示含有高斯噪声图像
	imshow("equalLena_gauss", equalLena_gauss);
	imshow("result_3gauss", result_3gauss);
	imshow("result_9gauss", result_9gauss);
	//显示含有椒盐噪声图像
	imshow("equalLena_salt", equalLena_salt);
	imshow("result_3salt", result_3salt);
	imshow("result_9salt", result_9salt);

	cout << "接下来是方框滤波" << endl;
	waitKey(0);

	Mat resultNorm, result;
	//方框滤波boxFilter()和sqrBoxFilter()
	boxFilter(equalLena, resultNorm, -1, Size(3, 3), Point(-1, -1), true);  //进行归一化
	boxFilter(equalLena, result, -1, Size(3, 3), Point(-1, -1), false);  //不进行归一化

	//显示处理结果
	imshow("resultNorm", resultNorm);
	imshow("result", result);

	cout << "接下来是高斯滤波" << endl;
	waitKey(0);

	Mat result_5_G, result_9_G;  //存放不含噪声滤波结果，后面数字代表滤波器尺寸
	Mat result_5gauss_G, result_9gauss_G;  //存放含有高斯噪声滤波结果，后面数字代表滤波器尺寸
	Mat result_5salt_G, result_9salt_G;  ////存放含有椒盐噪声滤波结果，后面数字代表滤波器尺寸


	//调用高斯滤波函数GaussianBlur()进行滤波
	GaussianBlur(equalLena, result_5_G, Size(5, 5), 10, 20);
	GaussianBlur(equalLena, result_9_G, Size(9, 9), 10, 20);
	GaussianBlur(equalLena_gauss, result_5gauss_G, Size(5, 5), 10, 20);
	GaussianBlur(equalLena_gauss, result_9gauss_G, Size(9, 9), 10, 20);
	GaussianBlur(equalLena_salt, result_5salt_G, Size(5, 5), 10, 20);
	GaussianBlur(equalLena_salt, result_9salt_G, Size(9, 9), 10, 20);

	//显示不含噪声图像
	imshow("equalLena ", equalLena);
	imshow("result_5", result_5_G);
	imshow("result_9", result_9_G);
	//显示含有高斯噪声图像
	imshow("equalLena_gauss", equalLena_gauss);
	imshow("result_5gauss", result_5gauss_G);
	imshow("result_9gauss", result_9gauss_G);
	//显示含有椒盐噪声图像
	imshow("equalLena_salt", equalLena_salt);
	imshow("result_5salt", result_5salt_G);
	imshow("result_9salt", result_9salt_G);


	waitKey(0);
	return 0;
}

