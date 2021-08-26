#include<iostream>
#include<math.h>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
//ֱ��ͼ���滯
cv::Mat histNormalized(cv::Mat &image, float o_min = 0, float o_max = 255)
{
	//ͼ���е������С�Ҷ�ֵ
	double min_value, max_value;
	cv::minMaxLoc(image, &min_value, &max_value);
	//ͼ��Ŀ��
	int rows = image.rows;
	int cols = image.cols;
	//���ͼ��
	cv::Mat outPutImage = cv::Mat::zeros(image.size(), CV_32FC1);
	float cofficient = (o_max - o_min) / (max_value - min_value);
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			float pixel = float(image.at<uchar>(r, c));
			outPutImage.at<float>(r, c) = round(cofficient*(pixel-min_value) + o_min);
		}
	}
	//��������ת��
	outPutImage.convertTo(outPutImage, CV_8UC1, 1.0, 0);
	return outPutImage;
}
int main(int argc, char*argv[])
{
	//����ͼ��
	cv::Mat image = cv::imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if (!image.data)
	{
		std::cout << "û�� ͼƬ" << std::endl;
		return -1;
	}
	//��ʾԭͼ
	cv::imshow("ԭͼ", image);
	//ͼ�����滯
	cv::Mat outPutImage = histNormalized(image, 0, 255);
	cv::imshow("ͼ�����滯", outPutImage);
	cv::waitKey(0);
	return 0;
}