#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
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
			closenessWeight.at<double>(r, c) = exp(-norm2 / sigma_g2);
		}
	}
	return closenessWeight;
}
//双边滤波
Mat bfltGray(const Mat & image, Size winSize, float sigma_g, float sigma_d)
{
	int winH = winSize.height;
	int winW = winSize.width;
	//平滑窗口的长宽均是奇数
	CV_Assert(winH > 0 && winW > 0);
	CV_Assert(winH % 2 == 1 && winW % 2 == 1);
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
			double pixel = image.at<double>(r, c);
			//判断边界
			int rTop = (r - half_winH) < 0 ? 0 : r - half_winH;
			int rBottom = (r + half_winH) > rows - 1 ? rows - 1 : r + half_winH;
			int cLeft = (c - half_winW) < 0 ? 0 : c - half_winW;
			int cRight = (c + half_winW) > cols - 1 ? cols - 1 : c + half_winW;
			//核作用的区域
			Mat region = image(Rect(Point(cLeft, rTop), Point(cRight + 1, rBottom + 1))).clone();
			//相似性权重模板
			Mat similarityWeight;
			pow(region - pixel, 2.0, similarityWeight);
			exp(-0.5*similarityWeight / pow(sigma_d, 2), similarityWeight);
			similarityWeight /= pow(sigma_d, 2);
			//空间距离权重
			Rect regionRect = Rect(Point(cLeft - c + half_winW, rTop - r + half_winH), Point(cRight - c + half_winW + 1, rBottom - r + half_winH + 1));
			Mat closenessWeightTemp = closenessWeight(regionRect).clone();
			//两个权重模板点乘相乘，然后归一化
			Mat weightTemp = closenessWeightTemp.mul(similarityWeight);
			weightTemp = weightTemp / sum(weightTemp)[0];
			//权重模板与当前的领域对应位置相乘，然后求和
			Mat result = weightTemp.mul(region);
			blfImage.at<float>(r, c) = sum(result)[0];
		}
	}
	return blfImage;
}
int main(int argc, char*argv[])
{
	//输入图像
	Mat I = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if (!I.data)
		return -1;
	//灰度值归一化
	Mat fI;
	I.convertTo(fI, CV_64FC1, 1.0/ 255, 0);
	//双边滤波
	Mat blfI=bfltGray(fI, Size(33, 33), 19, 0.5);
	//显示原图和双边滤波的结果
	imshow("原图", I);
	imshow("双边滤波", blfI);
	//如果要保存为 8 位图,需要乘以255，并转换为 CV_8U
	blfI.convertTo(blfI, CV_8U, 255, 0);
	imwrite("blf.jpg", blfI);
	waitKey(0);
	return 0;
}