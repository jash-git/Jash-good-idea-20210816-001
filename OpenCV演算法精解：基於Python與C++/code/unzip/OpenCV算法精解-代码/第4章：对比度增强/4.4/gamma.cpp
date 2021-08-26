#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<string>
#include<iostream>
cv::Mat image;//����ͼ��
cv::Mat image_0_1;//��һ������ͼ��
cv::Mat contrastImage;//���ͼ��
//ͼ��Ŀ��
int height;
int width;
int value = 16;
float segValue = 40.0;
const int MAX_VALUE = 120;
std::string contrastWindow = "�Աȶ�";
void callback_value(int, void*)
{
	//���� gamma ��ȡֵ��ΧΪ [0��3]
	float gamma = float(value) / segValue;
	//�����Աȶ�
	for (int r = 0; r < height; r++)
	{
		for (int c = 0; c < width; c++)
		{
			float pixel = powf(image_0_1.at<float>(r, c), gamma);
			contrastImage.at<float>(r, c) = pixel;
		}
	}
	//����ֱ�Ӳ��� OpenCV �ṩ�� pow����
	//cv::pow(image_0_1, gamma, contrastImage);
	//��ʾ�����ԱȶȺ��Ч��
	cv::imshow(contrastWindow, contrastImage);
	/*������*/
	contrastImage.convertTo(contrastImage, CV_8UC1, 255, 0);
	cv::imwrite("contrastImage.jpg", contrastImage);
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
	//ͼƬ��һ����ÿһ���Ҷ�ֵ������ 255
	image.convertTo(image_0_1, CV_32FC1, 1.0 / 255.0, 0);
	//��ʾԭͼ
	cv::imshow("ԭͼ", image_0_1);
	//ͼ��Ŀ��
	height = image.rows;
	width = image.cols;
	contrastImage = cv::Mat::zeros(image.size(), CV_32FC1);
	cv::namedWindow(contrastWindow, CV_WINDOW_AUTOSIZE);
	cv::createTrackbar("value", contrastWindow, &value, MAX_VALUE, callback_value);
	callback_value(0, 0);
	cv::waitKey(0);
	return 0;
}