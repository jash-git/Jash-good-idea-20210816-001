#include <opencv2\opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	Mat img, imgGray, imgMask;
	Mat maskWaterShed;  // watershed()�����Ĳ���
	img = imread("HoughLines.jpg");  //ԭͼ��
	if (img.empty())	{		cout << "��ȷ��ͼ���ļ������Ƿ���ȷ" << endl;		return -1;	}
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	//GaussianBlur(imgGray, imgGray, Size(5, 5), 10, 20);  //ģ�����ڼ��ٱ�Ե��Ŀ

	//��ȡ��Ե�����б�����
	Canny(imgGray, imgMask, 150, 300);
	//Mat k = getStructuringElement(0, Size(3, 3));
	//morphologyEx(imgMask, imgMask, MORPH_CLOSE, k);

	imshow("��Եͼ��", imgMask);
	imshow("ԭͼ��", img);

	//������ͨ����Ŀ
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(imgMask, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);

	//��maskWaterShed�ϻ�������,���������ˮ���㷨
	maskWaterShed = Mat::zeros(imgMask.size(), CV_32S);
	for (int index = 0; index < contours.size(); index++)
	{
		drawContours(maskWaterShed, contours, index, Scalar::all(index + 1),
			-1, 8, hierarchy, INT_MAX);
	}
	//��ˮ���㷨   ��Ҫ��ԭͼ����д���
	watershed(img, maskWaterShed);

	vector<Vec3b> colors;  // ������ɼ�����ɫ
	for (int i = 0; i < contours.size(); i++)
	{
		int b = theRNG().uniform(0, 255);
		int g = theRNG().uniform(0, 255);
		int r = theRNG().uniform(0, 255);
		colors.push_back(Vec3b((uchar)b, (uchar)g, (uchar)r));
	}

	Mat resultImg = Mat(img.size(), CV_8UC3);  //��ʾͼ��
	for (int i = 0; i < imgMask.rows; i++)
	{
		for (int j = 0; j < imgMask.cols; j++)
		{
			// ����ÿ���������ɫ
			int index = maskWaterShed.at<int>(i, j);
			if (index == -1)  // ������ֵ����Ϊ-1���߽磩
			{
				resultImg.at<Vec3b>(i, j) = Vec3b(255, 255, 255);
			}
			else if (index <= 0 || index > contours.size())  // û�б�������������Ϊ0 
			{
				resultImg.at<Vec3b>(i, j) = Vec3b(0, 0, 0);
			}
			else  // ����ÿ�������ֵ���ֲ��䣺1��2������contours.size()
			{
				resultImg.at<Vec3b>(i, j) = colors[index - 1];  // ��Щ������Ƴɲ�ͬ��ɫ
			}
		}
	}

	resultImg = resultImg * 0.6 + img * 0.4;
	imshow("��ˮ����", resultImg);

	//����ÿ�������ͼ��
	for (int n = 1; n <= contours.size(); n++)
	{
		Mat resImage1 = Mat(img.size(), CV_8UC3);  // ����һ�����Ҫ��ʾ��ͼ��
		for (int i = 0; i < imgMask.rows; i++)
		{
			for (int j = 0; j < imgMask.cols; j++)
			{
				int index = maskWaterShed.at<int>(i, j);
				if (index == n)
					resImage1.at<Vec3b>(i, j) = img.at<Vec3b>(i, j);
				else
					resImage1.at<Vec3b>(i, j) = Vec3b(0, 0, 0);
			}
		}
		//��ʾͼ��
		imshow(to_string(n), resImage1);
	}

	waitKey(0);
	return 0;
}