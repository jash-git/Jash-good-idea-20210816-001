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
//直方图均衡化：输入图像为 8 位灰度图
Mat equalHist(Mat image)
{
	CV_Assert(image.type() == CV_8UC1);
	//灰度图像的宽高
	int rows = image.rows;
	int cols = image.cols;
	//计算图像的灰度直方图
	Mat grayHist = calcGrayHist(image);
	//计算累积灰度直方图
	Mat zeroCumuMoment = Mat::zeros(Size(256, 1), CV_32SC1);
	for (int p = 0; p < 256; p++)
	{
		if (p == 0)
			zeroCumuMoment.at<int>(0, p) = grayHist.at<int>(0, 0);
		else
			zeroCumuMoment.at<int>(0, p) = zeroCumuMoment.at<int>(0, p - 1) + grayHist.at<int>(0, p);
	}
	//输入灰度级和输出灰度级的映射关系
	Mat outPut_q = Mat::zeros(Size(256, 1), CV_8UC1);
	float cofficient = 256.0 / (rows*cols);
	for (int p = 0; p < 256; p++)
	{
		float q = cofficient*zeroCumuMoment.at<int>(0, p) - 1;
		if (q >= 0)
			outPut_q.at<uchar>(0, p) = uchar(floor(q));
		else
			outPut_q.at<uchar>(0, p) = 0;
	}
	//得到直方图均衡化后的图像
	Mat euqalHistImage = Mat::zeros(image.size(), CV_8UC1);
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			int p = image.at<uchar>(r, c);
			euqalHistImage.at<uchar>(r, c) = outPut_q.at<uchar>(0, p);
		}
	}
	return euqalHistImage;
}
int main(int argc, char*argv[])
{
	//输入灰度图
	Mat image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if (!image.data)
		return -1;
	imshow("原图", image);
	//直方图均衡化
	Mat result = equalHist(image);
	imshow("直方图均衡化", result);
	waitKey(0);
	return 0;
}