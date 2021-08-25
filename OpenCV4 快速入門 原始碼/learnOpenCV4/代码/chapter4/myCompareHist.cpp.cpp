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
	system("color F0");  //�������������ɫ
	Mat img = imread("apple.jpg");
	if (img.empty())
	{
		cout << "��ȷ��ͼ���ļ������Ƿ���ȷ" << endl;
		return -1;
	}
	Mat gray, hist, gray2, hist2, gray3, hist3;
	cvtColor(img, gray, COLOR_BGR2GRAY);
	resize(gray, gray2, Size(), 0.5, 0.5);
	gray3 = imread("lena.png", IMREAD_GRAYSCALE);
	const int channels[1] = { 0 };
	float inRanges[2] = { 0,255 };
	const float* ranges[1] = { inRanges };
	const int bins[1] = { 256 };
	calcHist(&gray, 1, channels, Mat(), hist, 1, bins, ranges);
	calcHist(&gray2, 1, channels, Mat(), hist2, 1, bins, ranges);
	calcHist(&gray3, 1, channels, Mat(), hist3, 1, bins, ranges);
	drawHist(hist, NORM_INF, "hist");
	drawHist(hist2, NORM_INF, "hist2");
	drawHist(hist3, NORM_INF, "hist3");
	//ԭͼֱ��ͼ��ԭͼֱ��ͼ�����ϵ��
	double hist_hist = compareHist(hist, hist, HISTCMP_CORREL);
	cout << "apple_apple=" << hist_hist << endl;
	//ԭͼֱ��ͼ����Сԭͼֱ��ͼ�����ϵ��
	double hist_hist2 = compareHist(hist, hist2, HISTCMP_CORREL);
	cout << "apple_apple256=" << hist_hist2 << endl;
	//���Ų�ͬͼ��ֱ��ͼ���ϵ��
	double hist_hist3 = compareHist(hist, hist3, HISTCMP_CORREL);
	cout << "apple_lena=" << hist_hist3 << endl;
	waitKey(0);
	return 0;
}