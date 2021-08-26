#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
//构建空间距离权重模板
Mat getClosenessWeight(double sigma_g, Size size)
{
	//权重模板的宽高
	int W = size.width;
	int H = size.height;
	//模板的中心
	int cW = (W - 1) / 2;
	int cH = (H - 1) / 2;
	//权重模板
	Mat closenessWeight = Mat::zeros(size, CV_64FC1);
	for (int r = 0; r < H; r++)
	{
		for (int c = 0; c < W; c++)
		{
			double norm2 = pow(double(r - cH), 2.0) + pow(double(c - cW), 2.0);
			double sigma_g2 = 2.0*pow(sigma_g, 2.0);
			//赋值
			closenessWeight.at<double>(r, c) = exp(-norm2/ sigma_g2);
		}
	}
	return closenessWeight;
}
//联合双边滤波
Mat jointBLF(Mat I, Size size, float sigma_g, float sigma_d, int borterType = BORDER_DEFAULT)
{
	//构建空间距离的权重模板
	Mat closeWeight = getClosenessWeight(sigma_g, size);
	//对 I 进行高斯平滑
	Mat Ig;
	GaussianBlur(I, Ig, size, sigma_g);
	//模板的中心
	int cH = (size.height - 1) / 2;
	int cW = (size.width - 1) / 2;
	//对原图和高斯平滑的结果扩充边界
	Mat Ip,Igp;
	copyMakeBorder(I, Ip, cH, cH, cW, cW, borterType);
	copyMakeBorder(Ig, Igp, cH, cH, cW, cW, borterType);
	//原图像矩阵的宽，高
	int rows = I.rows;
	int cols = I.cols;
	int i = 0, j= 0;
	//联合双边滤波
	Mat jblf = Mat::zeros(I.size(), CV_64FC1);
	for (int r = cH; r < cH + rows; r++)
	{
		for (int c = cW; c < cW + cols; c++)
		{
			//当前位置的值
			double pixel = Igp.at<double>(r, c);
			//截取当前位置的邻域
			Mat region = Igp(Rect(c-cW,r-cH,size.width,size.height));
			//当前位置的相似性权重模板
			Mat similarityWeight;
			pow(region - pixel, 2.0, similarityWeight);
			cv::exp(-0.5*similarityWeight / pow(sigma_d, 2.0), similarityWeight);
			//相似性权重模板和空间距离权重模板点乘
			Mat weight = closeWeight.mul(similarityWeight);
			//权重模板的归一化
			weight = weight / cv::sum(weight)[0];
			//权重模板和邻域对应位置相乘求和
			Mat Iregion= Ip(Rect(c - cW, r - cH, size.width, size.height));
			jblf.at<double>(i, j) = sum(Iregion.mul(weight))[0];
			j += 1;
		}
		j = 0;
		i += 1;
	}
	return jblf;
}
int main(int argc, char*argv[])
{
	//输入图像
	Mat I = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if (!I.data)
		return -1;
	//数据类型为 CV_64F
	Mat fI;
	I.convertTo(fI, CV_64F, 1.0, 0);
	//联合双边滤波
	Mat jblf = jointBLF(fI, Size(33, 33), 7, 2);
	//显示联合双边滤波
	Mat jblf8U;
	jblf.convertTo(jblf8U, CV_8U, 1, 0);
	imshow("联合双边滤波", jblf);
	imshow("原图", I);
	waitKey(0);
	return 0;
}