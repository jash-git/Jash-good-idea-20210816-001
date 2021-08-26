#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
//快速均值平滑：输入图像的数据类型为浮点型
Mat fastMeanBlur(Mat img, Size winSize, int borderType, Scalar value=Scalar())
{
	//判断窗口的宽高是奇数
	int hei = winSize.height;
	int wid = winSize.width;
	CV_Assert(hei % 2 == 1 && wid % 2 == 1);
	//窗口半径
	int hh = (hei-1) / 2;
	int ww = (wid - 1) / 2;
	//窗口的面积，即宽 乘以 高
	float area = float(hei*wid);
	//边界扩充
	Mat paddImg;
	cv::copyMakeBorder(img, paddImg,hh, hh, ww, ww, borderType, value);
	//图像积分
	Mat inte;
	cv::integral(paddImg, inte, CV_32FC1);
	//输入图像矩阵的宽高
	int rows = img.rows;
	int cols = img.cols;
	int r = 0, c = 0;
	Mat meanImg = Mat::zeros(img.size(),CV_32FC1);
	for (int h = hh; h < hh+rows; h++)
	{
		for (int w = ww; w < ww+cols; w++)
		{
			float bottomRight = inte.at<float>(h + hh + 1, w + ww + 1);
			float topLeft = inte.at<float>(h - hh , w - ww);
			float topRight = inte.at<float>(h+hh+1,w-ww);
			float bottomLeft = inte.at<float>(h-hh,w+ww+1);
			meanImg.at<float>(r, c) = (bottomRight + topLeft - topRight - bottomLeft) / area;
			c++;
		}
		r++;
		c = 0;
	}
	return meanImg;
}
int main(int argc, char*argv[])
{
	//输入图像矩阵
	Mat img = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if (!img.data)
		return -1;
	//图像矩阵与均值算子卷积
	Mat meanImg = fastMeanBlur(img, Size(5, 5), cv::BORDER_REFLECT101);
	//数据类型转换
	meanImg.convertTo(meanImg, CV_8UC1, 1.0, 0);
	//显示原图
	imshow("原图", img);
	imshow("均值平滑", meanImg);
	waitKey(0);
	return 0;
}