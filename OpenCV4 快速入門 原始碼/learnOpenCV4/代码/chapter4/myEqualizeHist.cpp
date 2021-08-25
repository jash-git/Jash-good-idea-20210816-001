#include <opencv2\opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void drawHist(Mat &hist, int type, string name)  //��һ��������ֱ��ͼ����
{
	int hist_w = 512;
	int hist_h = 400;
	int width = 2;
	Mat histImage = Mat::zeros(hist_h, hist_w, CV_8UC3);
	normalize(hist, hist, 1, 0, type, -1, Mat());
	for (int i = 1; i <= hist.rows; i++)
	{
		rectangle(histImage, Point(width*(i - 1), hist_h - 1),
			Point(width*i - 1, hist_h - cvRound(hist_h*hist.at<float>(i - 1)) - 1),
			Scalar(255, 255, 255), -1);
	}
	imshow(name, histImage);
}
//������
int main()
{
	Mat img = imread("gearwheel.jpg");
	if (img.empty())	{		cout << "��ȷ��ͼ���ļ������Ƿ���ȷ" << endl;		return -1;	}
	Mat gray, hist, hist2;
	cvtColor(img, gray, COLOR_BGR2GRAY);
	Mat equalImg;
	equalizeHist(gray, equalImg);  //��ͼ��ֱ��ͼ���⻯
	const int channels[1] = { 0 };
	float inRanges[2] = { 0,255 };
	const float* ranges[1] = { inRanges };
	const int bins[1] = { 256 };
	calcHist(&gray, 1, channels, Mat(), hist, 1, bins, ranges);
	calcHist(&equalImg, 1, channels, Mat(), hist2, 1, bins, ranges);
	drawHist(hist, NORM_INF, "hist");
	drawHist(hist2, NORM_INF, "hist2");
	imshow("ԭͼ", gray);
	imshow("���⻯���ͼ��", equalImg);
	waitKey(0);
	return 0;
}

