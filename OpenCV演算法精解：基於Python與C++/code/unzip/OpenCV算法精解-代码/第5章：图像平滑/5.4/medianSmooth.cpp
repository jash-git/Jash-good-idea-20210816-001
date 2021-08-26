#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
#include<iostream>
//中值平滑
Mat medianSmooth(const Mat & I, Size size, int borderType = BORDER_DEFAULT)
{
	CV_Assert(I.type() == CV_8UC1);
	int H = size.height;
	int W = size.width;
	//窗口的长宽均为奇数，一般设置两者是相等的
	CV_Assert(H > 0 && W > 0);
	CV_Assert(H % 2 == 1 && W % 2 == 1);
	//对原图像矩阵进行边缘扩充
	int h = (H - 1) / 2;
	int w = (W - 1) / 2;
	Mat Ip;
	copyMakeBorder(I, Ip, h, h, w, w, borderType);
	//输入图像的宽高
	int rows = I.rows;
	int cols = I.cols;
	//中值平滑后的输出图像
	Mat medianI(I.size(), CV_8UC1);
	int i = 0, j = 0;
	//中数的位置
	int index = (H*W - 1) / 2;
	for (int r = h; r < h + rows; r++)
	{
		for (int c = w; c < w + cols; c++)
		{
			//取以当前位置为中心,大小为 size 的邻域
			Mat region = Ip(Rect(c-w, r-h, W,H)).clone();
			//对该邻域转换成行矩阵
			region = region.reshape(1, 1);
			//排序
			cv::sort(region, region, CV_SORT_EVERY_ROW);
			//取中数
			uchar mValue = region.at<uchar>(0, index);
			medianI.at<uchar>(i, j) = mValue;
			j++;
		}
		i++;
		j = 0;
	}
	return medianI;
}
int main(int argc, char*argv[])
{
	//输入图像
	Mat image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if (!image.data)
		return -1;
	//中值平滑
	Mat medianImage = medianSmooth(image, Size(7, 7));
	imshow("原图", image);
	imshow("中值平滑", medianImage);
	waitKey(0);
	return 0;
}