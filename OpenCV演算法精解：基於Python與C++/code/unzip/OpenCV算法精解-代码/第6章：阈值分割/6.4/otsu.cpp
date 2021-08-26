#include<iostream>
using namespace std;
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
//����Ҷ�ֱ��ͼ
Mat calcGrayHist(const Mat & image)
{
	//�洢 256 ���Ҷȼ���������
	Mat histogram = Mat::zeros(Size(256, 1), CV_32SC1);
	int rows = image.rows;
	int cols = image.cols;
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			int index = int( image.at<uchar>(r, c));
			histogram.at<int>(0, index) += 1;
		}
	}
	return histogram;
}
//Otsu ��ֵ�����õ���ֵ�����Ķ�ֵͼ OtsuThreshImage�������طָ���ֵ
int otsu(const Mat & image, Mat &OtsuThreshImage)
{
	//����Ҷ�ֱ��ͼ
	Mat histogram = calcGrayHist(image);
	//��һ���Ҷ�ֱ��ͼ
	Mat normHist;
	histogram.convertTo(normHist, CV_32FC1, 1.0 / (image.rows*image.cols), 0.0);
	//�����ۼ�ֱ��ͼ(����ۼӾ�)��һ���ۼӾ�
	Mat zeroCumuMoment = Mat::zeros(Size(256, 1), CV_32FC1);
	Mat oneCumuMoment = Mat::zeros(Size(256, 1), CV_32FC1);
	for (int i = 0; i < 256; i++)
	{
		if (i == 0)
		{
			zeroCumuMoment.at<float>(0, i) = normHist.at<float>(0, i);
			oneCumuMoment.at<float>(0, i) = i*normHist.at<float>(0, i);
		}
		else
		{
			zeroCumuMoment.at<float>(0, i) = zeroCumuMoment.at<float>(0, i-1)+ normHist.at<float>(0, i);
			oneCumuMoment.at<float>(0, i) = oneCumuMoment.at<float>(0,i-1) + i*normHist.at<float>(0, i);
		}
	}
	//������䷽��
	Mat variance = Mat::zeros(Size(256, 1), CV_32FC1);
	//��ƽ��ֵ
	float mean = oneCumuMoment.at<float>(0, 255);
	for (int i = 0; i < 255; i++)
	{
		if (zeroCumuMoment.at<float>(0, i) == 0 || zeroCumuMoment.at<float>(0, i) == 1)
			variance.at<float>(0, i) = 0;
		else
		{
			float cofficient = zeroCumuMoment.at<float>(0, i)*(1.0 - zeroCumuMoment.at<float>(0, i));
			variance.at<float>(0, i) = pow(mean*zeroCumuMoment.at<float>(0, i) - oneCumuMoment.at<float>(0, i), 2.0) / cofficient;
		}
	}
	//�ҵ���ֵ
	Point maxLoc;
	minMaxLoc(variance, NULL, NULL, NULL, &maxLoc);
	int otsuThresh = maxLoc.x;
	//��ֵ����
	threshold(image, OtsuThreshImage, otsuThresh, 255, THRESH_BINARY);
	return otsuThresh;
}
//������
int main(int argc, char*argv[])
{
	//����Ҷ�ͼ����
	Mat image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if (!image.data)
	{
		cout << "û��ͼƬ" << endl;
		return -1;
	}
	//Otsu ��ֵ�ָ�
	Mat otsuThreshImage;
	int thresh=0;
	thresh = otsu(image, otsuThreshImage);
	cout << "otsu�Զ��ָ����ֵΪ��" << thresh << endl;
	//��ʾ��ֵ�ָ�Ľ��
	imshow("Otsu��ֵ�ָ�", otsuThreshImage);
	imwrite("otsu.jpg", otsuThreshImage);
	waitKey(0);
	return 0;
}