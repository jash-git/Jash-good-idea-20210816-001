#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
#include<iostream>
//基于空间距离的权重因子（和计算高斯卷积核的过程差不多）
Mat getClosenessWeight(float sigma_g, Size winSize)
{
	//窗口的宽高
	int H = winSize.height;
	int W = winSize.width;
	CV_Assert(H % 2 == 1 && W % 2 == 1);
	//第一步:构建H行W列的矩阵
	Mat closenessWeight(winSize, CV_32FC1);
	int cH = (H - 1) / 2;
	int cW = (W - 1) / 2;
	for (int r = 0; r < H; r++)
	{
		for (int c = 0; c < W; c++)
		{
			float norm2 = pow(r - cH, 2.0) + pow(c - cW, 2.0);
			closenessWeight.at<float>(r, c) = exp(-norm2 / (2*pow(sigma_g, 2.0)));
		}
	}
	return closenessWeight;
}
//双边滤波
// image 为输入的单通道图像矩阵
//返回值为浮点型图像矩阵
Mat BilaterFilter(Mat image, Size winSize, float sigma_g, float sigma_d)
{
	CV_Assert(image.channels() == 1);
	int winH = winSize.height;
	int winW = winSize.width;
	//平滑窗口的长宽均是奇数
	CV_Assert(winH > 0 && winW > 0);
	CV_Assert(winH % 2 == 1 && winW % 2 == 1);
	//图像的数据类型为浮点型
	image.convertTo(image, CV_32FC1);
	if (winH == 1 && winW == 1)
		return image;
	int half_winW = (winW - 1) / 2;
	int half_winH = (winH - 1) / 2;
	//空间距离的权重因子
	Mat closenessWeight = getClosenessWeight(sigma_g, winSize);
	//图像的长宽
	int rows = image.rows;
	int cols = image.cols;
	//双边滤波后的输出图像
	Mat blfImage = Mat::ones(image.size(), CV_32FC1);
	//对每一个像素的领域进行核卷积
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			float pixel = image.at<float>(r, c);
			//判断边界
			int rTop = (r - half_winH) < 0 ? 0 : r - half_winH;
			int rBottom = (r + half_winH) > rows - 1 ? rows - 1 : r + half_winH;
			int cLeft = (c - half_winW) < 0 ? 0 : c - half_winW;
			int cRight = (c + half_winW) > cols - 1 ? cols - 1 : c + half_winW;
			//核作用的区域
			Mat region = image(Rect(Point(cLeft, rTop), Point(cRight + 1, rBottom + 1))).clone();
			//灰度值（ 值域 ）的相似性权重因子
			Mat similarityWeight;
			pow(region - pixel, 2.0, similarityWeight);
			exp(-similarityWeight/ (2 * pow(sigma_d, 2.0)), similarityWeight);
			//空间距离的相似性权重因子
			Rect regionRect = Rect(Point(cLeft - c + half_winW, rTop - r + half_winH), Point(cRight - c + half_winW + 1, rBottom - r + half_winH + 1));
			Mat closenessWeightTemp = closenessWeight(regionRect).clone();
			//两个权重因子对应位置相乘
			Mat weightTemp = closenessWeightTemp.mul(similarityWeight);
			weightTemp = weightTemp / sum(weightTemp)[0];
			//权重因子与当前的领域对应位置相乘，然后求和
			Mat result = weightTemp.mul(region);
			blfImage.at<float>(r, c) = sum(result)[0];
		}
	}
	return blfImage;
}
//彩色双边滤波
Mat BilaterFilterColor(Mat image, Size winSize, float sigma_g, float sigma_d)
{
	CV_Assert(image.channels() == 3);
	//分离三个通道，针对每一个通道进行双边滤波
	vector<Mat> img;
	split(image, img);
	//存储每个通道双边滤波后的结果
	vector<Mat> bImg;
	bImg.clear();
	for (int c = 0; c < 3; c++)
	{
		Mat b_img = BilaterFilter(img[c], winSize, sigma_g, sigma_d);
		bImg.push_back(b_img);
	}
	//三个通道合并
	Mat bColorImage;
	merge(bImg, bColorImage);
	return bColorImage;
}
int main(int argc, char*argv[])
{
	//输入图像矩阵
	Mat image = imread(argv[1], CV_LOAD_IMAGE_COLOR);
	if (!image.data)
	{
		std::cout << "没有图片" << std::endl;
		return -1;
	}
	imshow("原图", image);
	//彩色双边滤波
	Mat result = BilaterFilterColor(image, Size(19, 19),25,15);
	result.convertTo(result, CV_8UC3);
	imshow("双边滤波", result);
	imwrite("bfltResult.jpg", result);
	waitKey(0);
	return 0;
}