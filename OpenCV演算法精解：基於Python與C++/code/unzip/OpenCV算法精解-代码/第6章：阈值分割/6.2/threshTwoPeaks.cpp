#include<iostream>
using namespace std;
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
//计算图像的灰度直方图
Mat calcGrayHist(const Mat & image)
{
	//存储 256 个灰度级的像素数
	Mat histogram = Mat::zeros(Size(256, 1), CV_32SC1);
	int rows = image.rows;
	int cols = image.cols;
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			int index = int(image.at<uchar>(r, c));
			histogram.at<int>(0, index) += 1;
		}
	}
	return histogram;
}
//波峰-波谷法
int threshTwoPeaks(const Mat & image,  Mat & thresh_out)
{
	//计算灰度直方图
	Mat histogram = calcGrayHist(image);
	//找到灰度直方图最大峰值对应的灰度级
	Point firstPeakLoc;
	minMaxLoc(histogram, NULL, NULL, NULL, &firstPeakLoc);
	int firstPeak = firstPeakLoc.x;
	//寻找灰度直方图 第二个峰值对应的灰度级
	Mat measureDists = Mat::zeros(Size(256, 1), CV_32FC1);
	for (int k = 0; k < 256; k++)
	{
		int hist_k = histogram.at<int>(0, k);
		measureDists.at<float>(0, k) = pow(float(k - firstPeak), 2)*hist_k;
	}
	Point secondPeakLoc;
	minMaxLoc(measureDists, NULL, NULL, NULL, &secondPeakLoc);
	int secondPeak = secondPeakLoc.x;
	//找到两个峰值之间的最小值对应的灰度级，作为阈值
	Point threshLoc;
	int  thresh = 0;
	if (firstPeak < secondPeak)
	{
		minMaxLoc(histogram.colRange(firstPeak,secondPeak), NULL, NULL, &threshLoc);
		thresh = firstPeak + threshLoc.x + 1;
	}	
	else
	{
		minMaxLoc(histogram.colRange(secondPeak,firstPeak), NULL, NULL, &threshLoc);
		thresh = secondPeak + threshLoc.x + 1;
	}
	//阈值分割
	threshold(image, thresh_out, thresh, 255, cv::THRESH_BINARY);
	return thresh;
}
int main(int argc, char*argv[])
{
	//输入图像矩阵
	Mat image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if (!image.data)
	{
		cout << "没有输入图片" << endl;
		return -1;
	}
	//波峰 波谷阈值法
	Mat threshImage;
	int thresh = threshTwoPeaks(image, threshImage);
	cout << "阈值为：" << thresh << endl;
	//显示阈值后的二值图
	imshow("二值图", threshImage);
	waitKey(0);
	return 0;
}