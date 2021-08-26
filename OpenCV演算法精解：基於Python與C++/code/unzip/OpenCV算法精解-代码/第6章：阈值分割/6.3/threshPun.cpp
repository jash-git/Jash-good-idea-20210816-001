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
			int index = int(image.at<uchar>(r, c));
			histogram.at<int>(0, index) += 1;
		}
	}
	return histogram;
}
/*����ֵ����*/
//�õ���ֵ�����Ķ�ֵͼ thershPunImage�������طָ���ֵ
int threshPun(const Mat & image, Mat &thershPunImage)
{
	//����Ҷ�ֱ��ͼ
	Mat histogram = calcGrayHist(image);
	//��һ���Ҷ�ֱ��ͼ
	Mat normHist;
	histogram.convertTo(normHist, CV_32FC1, 1.0 / (image.rows*image.cols), 0.0);
	//�����ۼ�ֱ��ͼ��Ҳ��Ϊ����ۼӾ�
	Mat zeroCumuMoment = Mat::zeros(Size(256, 1), CV_32FC1);
	for (int i = 0; i < 256; i++)
	{
		if (i == 0)
			zeroCumuMoment.at<float>(0, i) = normHist.at<float>(0, i);
		else
			zeroCumuMoment.at<float>(0, i) = zeroCumuMoment.at<float>(0, i - 1) + normHist.at<float>(0, i);

	}
	//��������Ҷȼ�����
	Mat entropy = Mat::zeros(Size(256, 1), CV_32FC1);
	for (int i = 0; i < 256; i++)
	{
		float normHist_i = normHist.at<float>(0, i);
		if (i == 0)
		{
			if (normHist_i == 0)
				entropy.at<float>(0, i) = 0;
			else
				entropy.at<float>(0, i) = -normHist_i*log10f(normHist_i);
		}
		else
		{
			if (normHist_i == 0)
				entropy.at<float>(0, i) = entropy.at<float>(0, i - 1);
			else
				entropy.at<float>(0, i) = entropy.at<float>(0, i - 1) - normHist_i*log10f(normHist_i);
		}
	}
	//����ֵ
	Mat fT = Mat::zeros(Size(256, 1), CV_32FC1);
	float totalEntroy = entropy.at<float>(0, 255);
	float ft1 = 0;
	float ft2 = 0;
	for (int i = 0; i < 255; i++)
	{
		float zeroCumuMoment_i = zeroCumuMoment.at<float>(0, i);
		float entropy_i = entropy.at<float>(0, i);
		//�����ֵ
		double maxFront,maxBack;
		minMaxLoc(normHist(Rect(0, 0, i, 1)), NULL, &maxFront);
		minMaxLoc(normHist(Rect(i,0,255-i,1)), NULL, &maxBack);
		if (maxFront == 0 || zeroCumuMoment_i == 0 || maxFront == 1 || zeroCumuMoment_i == 1 || totalEntroy == 0)
			ft1 = 0;
		else
			ft1 = entropy_i / totalEntroy*(log10f(zeroCumuMoment_i) / log10f(maxFront));
		if (maxBack == 0 || 1 - zeroCumuMoment_i == 0 || maxBack == 1 || 1 - zeroCumuMoment_i == 1)
			ft2 = 0;
		else
		{
			if (totalEntroy == 0)
				ft2 = log10f(1 - zeroCumuMoment_i) / log10f(maxBack);
			else
				ft2 = (1 - entropy_i / totalEntroy)*(log10f(1 - zeroCumuMoment_i) / log10f(maxBack));
		}
		fT.at<float>(0, i) = ft1 + ft2;
	}
	//�ҵ����ֵ����������Ϊ�õ��ķָ���ֵ
	Point threshLoc;
	minMaxLoc(fT, NULL, NULL, NULL, &threshLoc);
	int punThresh = threshLoc.x;
	//��ֵ����
	threshold(image, thershPunImage, punThresh, 255, THRESH_BINARY);
	return punThresh;
}
//������
int main(int argc, char*argv[])
{
	//����Ҷ�ͼ�����
	Mat image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if (!image.data)
	{
		cout << "û������ͼƬ" << endl;
		return -1;
	}
	//����ֵ�㷨
	Mat treshPunImage;
	int thresh = threshPun(image, treshPunImage);
	cout << "�����ֵΪ��" << thresh << endl;
	//��ʾ��ֵ�����Ķ�ֵ��ͼ��
	imshow("threshPun", treshPunImage);
	imwrite("entroy.jpg", treshPunImage);
	waitKey(0);
	return 0;
}