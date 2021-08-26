#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
#include<vector>
#include<iostream>
using namespace std;
int main(int argc, char*argv[])
{
	//第一步：输入图像
	Mat img = imread(argv[1], IMREAD_GRAYSCALE);
	if (!img.data)
		return -1;
	//第二步：边缘检测，得到边缘二值图
	GaussianBlur(img, img, Size(3, 3), 0.5);
	Mat binaryImg;
	Canny(img, binaryImg, 50, 200);
	imshow("显示边缘", binaryImg);
	imwrite("cannyEdge.jpg", binaryImg);
	//第三步：边缘的轮廓
	vector<vector<Point>> contours;
	vector<Vec4i> hei;
	findContours(binaryImg, contours, hei, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE,Point(0,0));
	
	//第四步：对每一个轮廓作拟合，这里用旋转矩形
	int num = contours.size();//轮廓的数量
	for (int i = 0; i < num; i++)
	{
		//最小外包直立矩形
		Rect rect = boundingRect(Mat(contours[i]));
		if (rect.area()>2000)//筛选出面积大于 10000 的矩形
		{
			//在原图中画出外包矩形
			rectangle(img, rect, Scalar(255),2);
			cout << rect.area() << endl;
		}
	}
	imshow("img", img);
	imwrite("img0.jpg", img);
	waitKey(0);
	return 0;
 }