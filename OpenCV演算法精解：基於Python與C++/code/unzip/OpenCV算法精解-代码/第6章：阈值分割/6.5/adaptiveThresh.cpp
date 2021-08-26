#include<iostream>
using namespace std;
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
Mat adaptiveThreshold_S(const Mat & image,Size blockSize,float ratio)
{
	//图像的宽高
	int rows = image.rows;
	int cols = image.cols;
	//阈值处理后的二值图
	Mat threshImage = Mat::zeros(image.size(), CV_8UC1);
	//
	int h = (blockSize.height - 1) / 2;
	int w = (blockSize.width - 1) / 2;
	//图像的积分
	Mat imageIntegral;
	integral(image, imageIntegral, CV_32FC1);
	imageIntegral = imageIntegral(Rect(1, 1, cols, rows)).clone();

	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			int tl_r = r - h > 0 ? r - h : 0;
			int tl_c = c - w > 0 ? c - w : 0;
			int br_r = r + h < rows ? r + h : rows - 1;
			int br_c = c + w < cols ? c + w : cols - 1;
			//计算区域和
			float regionSum = imageIntegral.at<float>(br_r, br_c) +
				imageIntegral.at<float>(tl_r, tl_c) -
				imageIntegral.at<float>(tl_r, br_c) -
				imageIntegral.at<float>(br_r, tl_c);
			int count = (br_r - tl_r + 1)*(br_c - tl_c + 1);
			int pixel = int(image.at<uchar>(r, c));
			if (pixel*count < (1 - ratio)*regionSum)
				threshImage.at<uchar>(r, c) = 0;
			else
				threshImage.at<uchar>(r, c) = 255;
		}
	}
	return threshImage;
}
//自适应阈值分割
enum METHOD {MEAN,GAUSS,MEDIAN};
Mat adaptiveThresh(Mat I, int radius, float ratio, METHOD method= MEAN)
{
	//第一步：图像矩阵的平滑处理
	Mat I_smooth;
	switch (method)
	{
	case MEAN:
		boxFilter(I,I_smooth,CV_32FC1,Size(2*radius+1,2*radius+1));//均值平滑
		break;
	case GAUSS:
		GaussianBlur(I, I_smooth, Size(2*radius+1,2*radius+1),0,0);//高斯平滑
		I_smooth.convertTo(I_smooth, CV_32FC1);
		break;
	case MEDIAN:
		medianBlur(I, I_smooth, 2 * radius + 1);//中值平滑
		I_smooth.convertTo(I_smooth, CV_32FC1);
		break;
	default:
		break;
	}
	//第二步：平滑结果乘以比例系数，然后图像与其做差
	I.convertTo(I, CV_32FC1);
	Mat diff = I - (1.0 - ratio)*I_smooth;
	//第三步：阈值处理：大于等于 0 的，输出 255 ，反之输出 0
	Mat out = Mat::zeros(diff.size(), CV_8UC1);
	for (int r = 0; r < out.rows; r++)
	{
		for (int c = 0; c < out.cols; c++)
		{
			if (diff.at<float>(r, c) >= 0)
				out.at<uchar>(r, c) = 255;
		}
	}
	return out;
}
int main(int argc, char*argv[])
{
	//输入图像
	Mat image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if (!image.data)
	{
		cout << "没有输入图片" << endl;
		return -1;
	}
	//自适应阈值处理
	Mat threshImage = adaptiveThresh(image,21,0.15, MEDIAN);
	imshow("image", threshImage);
	imwrite("adThmean43.jpg", threshImage);
	waitKey(0);
	return 0;
}
