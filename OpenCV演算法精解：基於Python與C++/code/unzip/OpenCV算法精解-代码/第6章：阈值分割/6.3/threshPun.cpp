#include<iostream>
using namespace std;
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
//计算灰度直方图
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
/*熵阈值处理*/
//得到阈值处理后的二值图 thershPunImage，并返回分割阈值
int threshPun(const Mat & image, Mat &thershPunImage)
{
	//计算灰度直方图
	Mat histogram = calcGrayHist(image);
	//归一化灰度直方图
	Mat normHist;
	histogram.convertTo(normHist, CV_32FC1, 1.0 / (image.rows*image.cols), 0.0);
	//计算累加直方图，也称为零阶累加矩
	Mat zeroCumuMoment = Mat::zeros(Size(256, 1), CV_32FC1);
	for (int i = 0; i < 256; i++)
	{
		if (i == 0)
			zeroCumuMoment.at<float>(0, i) = normHist.at<float>(0, i);
		else
			zeroCumuMoment.at<float>(0, i) = zeroCumuMoment.at<float>(0, i - 1) + normHist.at<float>(0, i);

	}
	//计算各个灰度级的熵
	Mat entropy = Mat::zeros(Size(256, 1), CV_32FC1);
	for (int i = 0; i < 256; i++)
	{
		float normHist_i = normHist.at<float>(0, i);
		if (i == 0)
		{
			if (normHist_i == 0)
				entropy.at<float>(0, i) = 0;
			else
				entropy.at<float>(0, i) = -normHist_i*log10f(normHist_i);
		}
		else
		{
			if (normHist_i == 0)
				entropy.at<float>(0, i) = entropy.at<float>(0, i - 1);
			else
				entropy.at<float>(0, i) = entropy.at<float>(0, i - 1) - normHist_i*log10f(normHist_i);
		}
	}
	//找阈值
	Mat fT = Mat::zeros(Size(256, 1), CV_32FC1);
	float totalEntroy = entropy.at<float>(0, 255);
	float ft1 = 0;
	float ft2 = 0;
	for (int i = 0; i < 255; i++)
	{
		float zeroCumuMoment_i = zeroCumuMoment.at<float>(0, i);
		float entropy_i = entropy.at<float>(0, i);
		//找最大值
		double maxFront,maxBack;
		minMaxLoc(normHist(Rect(0, 0, i, 1)), NULL, &maxFront);
		minMaxLoc(normHist(Rect(i,0,255-i,1)), NULL, &maxBack);
		if (maxFront == 0 || zeroCumuMoment_i == 0 || maxFront == 1 || zeroCumuMoment_i == 1 || totalEntroy == 0)
			ft1 = 0;
		else
			ft1 = entropy_i / totalEntroy*(log10f(zeroCumuMoment_i) / log10f(maxFront));
		if (maxBack == 0 || 1 - zeroCumuMoment_i == 0 || maxBack == 1 || 1 - zeroCumuMoment_i == 1)
			ft2 = 0;
		else
		{
			if (totalEntroy == 0)
				ft2 = log10f(1 - zeroCumuMoment_i) / log10f(maxBack);
			else
				ft2 = (1 - entropy_i / totalEntroy)*(log10f(1 - zeroCumuMoment_i) / log10f(maxBack));
		}
		fT.at<float>(0, i) = ft1 + ft2;
	}
	//找到最大值的索引，作为得到的分割阈值
	Point threshLoc;
	minMaxLoc(fT, NULL, NULL, NULL, &threshLoc);
	int punThresh = threshLoc.x;
	//阈值处理
	threshold(image, thershPunImage, punThresh, 255, THRESH_BINARY);
	return punThresh;
}
//主函数
int main(int argc, char*argv[])
{
	//输入灰度图像矩阵
	Mat image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if (!image.data)
	{
		cout << "没有输入图片" << endl;
		return -1;
	}
	//熵阈值算法
	Mat treshPunImage;
	int thresh = threshPun(image, treshPunImage);
	cout << "求得阈值为：" << thresh << endl;
	//显示阈值处理后的二值化图像
	imshow("threshPun", treshPunImage);
	imwrite("entroy.jpg", treshPunImage);
	waitKey(0);
	return 0;
}