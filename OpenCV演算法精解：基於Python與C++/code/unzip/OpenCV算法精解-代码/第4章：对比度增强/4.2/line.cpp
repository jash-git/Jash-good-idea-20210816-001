#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<string>
#include<iostream>
cv::Mat image;//����ͼ��
cv::Mat contrastImage;//���ͼ��
//ͼ��Ŀ��
int height;
int width;
int value = 40;
float segValue = float(value);
const int MAX_VALUE = 120;
std::string contrastWindow = "�Աȶ�";
void callback_value(int, void*)
{
	//б�� a
	float a = float(value) / segValue;
	//�����Աȶ�
	for (int r = 0; r < height; r++)
	{
		for (int c = 0; c < width; c++)
		{
			float pixel = a*image.at<uchar>(r, c);
			pixel = round(pixel);
			//�ض�
			if (pixel > 255)
				pixel = 255;
			contrastImage.at<uchar>(r, c) = uchar(pixel);
		}
	}
	//��ʾ�����ԱȶȺ��Ч��
	cv::imshow(contrastWindow, contrastImage);
}
int main(int argc, char*argv[])
{
	//����ͼƬ
	image = cv::imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if (!image.data)
	{
		std::cout << "û��ͼƬ" << std::endl;
		return -1;
	}
	//��ʾԭͼ
	cv::imshow("ԭͼ", image);
	//ͼ��Ŀ��
	height = image.rows;
	width = image.cols;
	contrastImage = cv::Mat::zeros(image.size(), CV_8UC1);
	cv::namedWindow(contrastWindow, CV_WINDOW_AUTOSIZE);
	cv::createTrackbar("value", contrastWindow, &value, MAX_VALUE, callback_value);
	callback_value(0, 0);
	cv::waitKey(0);
	return 0;
}