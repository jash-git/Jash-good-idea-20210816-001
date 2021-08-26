#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<string>
#include<iostream>
cv::Mat image;//输入图像
cv::Mat contrastImage;//输出图像
//图像的宽高
int height;
int width;
int value = 40;
float segValue = float(value);
const int MAX_VALUE = 120;
std::string contrastWindow = "对比度";
void callback_value(int, void*)
{
	//斜率 a
	float a = float(value) / segValue;
	//调整对比度
	for (int r = 0; r < height; r++)
	{
		for (int c = 0; c < width; c++)
		{
			float pixel = a*image.at<uchar>(r, c);
			pixel = round(pixel);
			//截断
			if (pixel > 255)
				pixel = 255;
			contrastImage.at<uchar>(r, c) = uchar(pixel);
		}
	}
	//显示调整对比度后的效果
	cv::imshow(contrastWindow, contrastImage);
}
int main(int argc, char*argv[])
{
	//输入图片
	image = cv::imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if (!image.data)
	{
		std::cout << "没有图片" << std::endl;
		return -1;
	}
	//显示原图
	cv::imshow("原图", image);
	//图像的宽高
	height = image.rows;
	width = image.cols;
	contrastImage = cv::Mat::zeros(image.size(), CV_8UC1);
	cv::namedWindow(contrastWindow, CV_WINDOW_AUTOSIZE);
	cv::createTrackbar("value", contrastWindow, &value, MAX_VALUE, callback_value);
	callback_value(0, 0);
	cv::waitKey(0);
	return 0;
}