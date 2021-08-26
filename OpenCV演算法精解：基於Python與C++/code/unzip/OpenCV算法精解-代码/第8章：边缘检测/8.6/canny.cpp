#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
//非极大值抑制
Mat non_maximum_suppression_default(Mat dx, Mat dy)
{	//使用平方和开方的方式计算边缘强度
	Mat edgeMag;
	cv::magnitude(dx, dy, edgeMag);
	//宽高
	int rows = dx.rows;
	int cols = dy.cols;
	//边缘强度的非极大抑制
	Mat edgeMag_nonMaxSup = Mat::zeros(dx.size(), dx.type());
	for (int r = 1; r < rows-1; r++)
	{
		for (int c = 1; c < cols-1; c++)
		{
			float x = dx.at<float>(r, c);
			float y = dy.at<float>(r, c);
			//梯度方向
			float angle = atan2f(y, x)/CV_PI*180;
			//当前位置的边缘强度
			float mag = edgeMag.at<float>(r, c);
			// 左 / 右方向比较
			if (abs(angle) < 22.5 || abs(angle) > 157.5)
			{
				float left = edgeMag.at<float>(r, c - 1);
				float right = edgeMag.at<float>(r, c + 1);
				if (mag > left && mag > right)
					edgeMag_nonMaxSup.at<float>(r, c) = mag;
			}
			//左上 / 右下方向比较
			if ((angle >= 22.5 && angle < 67.5) || (angle < -112.5 && angle >= 157.5))
			{
				float leftTop = edgeMag.at<float>(r - 1, c - 1);
				float rightBottom = edgeMag.at<float>(r + 1, c + 1);
				if (mag > leftTop && mag > rightBottom)
					edgeMag_nonMaxSup.at<float>(r, c) = mag;
			}
			//上 / 下方向比较
			if ((angle >= 67.5 && angle <= 112.5) || (angle >= -112.5 && angle <= -67.5))
			{
				float top = edgeMag.at<float>(r - 1, c);
				float bottom = edgeMag.at<float>(r + 1, c);
				if (mag > top && mag > bottom)
					edgeMag_nonMaxSup.at<float>(r, c) = mag;
			}
			//右上 / 左下方向
			if ((angle > 112.5 && angle <= 157.5) || (angle > -67.5 && angle <= -22.5))
			{
				float rightTop = edgeMag.at<float>(r - 1, c + 1);
				float leftBottom = edgeMag.at<float>(r + 1, c - 1);
				if (mag > rightTop && mag > leftBottom)
					edgeMag_nonMaxSup.at<float>(r, c) = mag;
			}
		}
	}
	return edgeMag_nonMaxSup;
}
//非极大值抑制 ： 插值比较
Mat non_maximum_suppression_Inter(Mat dx, Mat dy)
{
	//使用平方和开方的方式计算边缘强度
	Mat edgeMag;
	cv::magnitude(dx, dy, edgeMag);
	//宽高
	int rows = dx.rows;
	int cols = dy.cols;
	//边缘强度的非极大抑制
	Mat edgeMag_nonMaxSup = Mat::zeros(dx.size(), dx.type());
	for (int r = 1; r < rows-1; r++)
	{
		for (int c = 1; c < cols-1; c++)
		{
			float x = dx.at<float>(r, c);
			float y = dy.at<float>(r, c);
			if (x == 0 && y == 0)
				continue;
			float angle = atan2f(y, x) / CV_PI * 180;
			//领域内八个方向上的边缘强度
			float leftTop = edgeMag.at<float>(r - 1, c - 1);
			float top = edgeMag.at<float>(r - 1, c);
			float rightBottom = edgeMag.at<float>(r + 1, c + 1);
			float right = edgeMag.at<float>(r, c+1);
			float rightTop = edgeMag.at<float>(r - 1, c + 1);
			float leftBottom = edgeMag.at<float>(r + 1, c - 1);
			float bottom = edgeMag.at<float>(r + 1, c);
			float left = edgeMag.at<float>(r, c - 1);
			float mag = edgeMag.at<float>(r, c);
			//左上方与上方的插值 右下方和下方的插值
			if ((angle > 45 && angle <= 90) || (angle > -135 && angle <= -90))
			{
				float ratio = x / y;
				float top = edgeMag.at<float>(r - 1, c);
				//插值
				float leftTop_top = ratio*leftTop + (1 - ratio)*top;
				float rightBottom_bottom = ratio*rightBottom + (1 - ratio)*bottom;
				if (mag > leftTop_top && mag > rightBottom_bottom)
					edgeMag_nonMaxSup.at<float>(r, c) = mag;
			}
			//右上方和上方的插值 左下方和下方的插值
			if ((angle > 90 && angle <= 135) || (angle > -90 && angle <= -45))
			{
				float ratio = abs(x / y);
				float rightTop_top = ratio*rightTop + (1 - ratio)*top;
				float leftBottom_bottom = ratio*leftBottom + (1 - ratio)*bottom;
				if (mag > rightTop_top && mag > leftBottom_bottom)
					edgeMag_nonMaxSup.at<float>(r, c) = mag;
			}
			//左上方和左方的插值 右下方和右方的插值
			if ((angle >= 0 && angle <= 45) || (angle > -180 && angle <= -135))
			{
				float ratio = y / x;
				float rightBottom_right = ratio*rightBottom + (1 - ratio)*right;
				float leftTop_left = ratio*leftTop + (1 - ratio)*left;
				if (mag > rightBottom_right && mag > leftTop_left)
					edgeMag_nonMaxSup.at<float>(r, c) = mag;
			}
			//右上方和右方的插值 左下方和左方的插值
			if ((angle > 135 && angle <= 180) || (angle > -45 && angle <= 0))
			{
				float ratio = abs(y / x);
				float rightTop_right = ratio*rightTop + (1 - ratio)*right;
				float leftBottom_left = ratio*leftBottom + (1 - ratio)*left;
				if (mag > rightTop_right && mag > leftBottom_left)
					edgeMag_nonMaxSup.at<float>(r, c) = mag;
			}
		}
	}
	return edgeMag_nonMaxSup;
}
//确定一个点的坐标是否在图像范围内
bool checkInRange(int r, int c, int rows, int cols)
{
	if (r >= 0 && r < rows && c>=0 && c < cols)
		return true;
	else
		return false;
}
//从确定边缘点出发，延长边缘
void trace(Mat edgeMag_nonMaxSup, Mat &edge, float lowerThresh, int r, int c, int rows,int cols)
{
	if (edge.at<uchar>(r, c) == 0)
	{
		edge.at<uchar>(r, c) = 255;
		for (int i = -1; i <= 1; i++)
		{
			for (int j = -1; j <= 1; j++)
			{
				float mag = edgeMag_nonMaxSup.at<float>(r+i, c+j);
				if (checkInRange(r + i, c + j, rows, cols) && mag >= lowerThresh)
					trace(edgeMag_nonMaxSup, edge, lowerThresh, r+i, c+j, rows, cols);
			}
		}
	}
}
//双阈值的滞后阈值处理
Mat hysteresisThreshold(Mat edgeMag_nonMaxSup, float lowerThresh, float upperThresh)
{	
	//宽高
	int rows = edgeMag_nonMaxSup.rows;
	int cols = edgeMag_nonMaxSup.cols;
	//最后的边缘输出图
	Mat edge = Mat::zeros(Size(cols, rows), CV_8UC1);
	//滞后阈值处理
	for (int r = 1; r < rows - 1; r++)
	{
		for (int c = 1; c < cols-1; c++)
		{
			float mag = edgeMag_nonMaxSup.at<float>(r, c);
			//大于高阈值，可作为确定边缘点被接受
			//并以该点位起始点延长边缘
			if(mag>=upperThresh)
				trace(edgeMag_nonMaxSup, edge, lowerThresh, r, c, rows, cols);
			//小于低阈值的直接被剔除
			if (mag < lowerThresh)
				edge.at<uchar>(r, c) = 0;
		}
	}
	return  edge;
}
int main(int argc,char*argv[])
{
	//输入图像
	Mat image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if (!image.data)
		return -1;
	//第一步：sobel 卷积，这里采用 OpenCV 封装的 Sobel 函数
	Mat dx, dy;
	cv::Sobel(image, dx, CV_32FC1, 1, 0, 3);
	cv::Sobel(image, dy, CV_32FC1, 0, 1, 3);
	//边缘强度的灰度级显示
	Mat edgeMag;
	cv::magnitude(dx, dy, edgeMag);
	Mat mag;
	edgeMag.convertTo(mag, CV_8UC1);
	cv::imshow("边缘强度的灰度级显示", mag);
	cv::imwrite("mag.jpg", mag);
	//第二步：非极大值抑制
	Mat edgeMag_nonMaxSup = non_maximum_suppression_default(dx, dy);
	//显示非极大值抑制后的边缘强度图
	Mat nonMaxSup;
	edgeMag_nonMaxSup.convertTo(nonMaxSup, CV_8UC1);
	cv::imshow("非极大值抑制", nonMaxSup);
	cv::imwrite("nonMaxSup.jpg", nonMaxSup);
	//第三步：双阈值的滞后阈值处理
	float lowerThresh = 40;
	float upperThresh = 150;
	Mat edge = hysteresisThreshold(edgeMag_nonMaxSup, lowerThresh, upperThresh);
	imshow("CannyEdge", edge);
	cv::imwrite("CannyEdge.jpg", edge);
	//与单阈值处理进行比较
	Mat lowerThreshEdge;
	cv::threshold(edgeMag_nonMaxSup, lowerThreshEdge, lowerThresh, 255, CV_THRESH_BINARY);
	cv::convertScaleAbs(lowerThreshEdge, lowerThreshEdge, 1.0, 0);
	cv::imshow("低阈值处理后的效果", lowerThreshEdge);
	cv::imwrite("lowerThreshEdge.jpg", lowerThreshEdge);
	Mat upperThreshEdge;
	cv::threshold(edgeMag_nonMaxSup, upperThreshEdge, upperThresh, 255, CV_THRESH_BINARY);
	cv::convertScaleAbs(upperThreshEdge, upperThreshEdge, 1.0, 0.0);
	cv::imshow("高阈值处理后的效果", upperThreshEdge);
	cv::imwrite("upperThreshEdge.jpg", upperThreshEdge);
	waitKey(0);
	return 0;
}