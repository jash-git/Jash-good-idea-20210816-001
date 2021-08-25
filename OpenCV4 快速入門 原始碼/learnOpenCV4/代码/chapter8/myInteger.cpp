#include <opencv2\opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	//����һ��16��16ȫΪ1�ľ�����Ϊ256=16��16
	Mat img = Mat::ones(16, 16, CV_32FC1);

	//��ͼ���м����������
	RNG rng(10086);
	for (int y = 0; y < img.rows; y++)
	{
		for (int x = 0; x < img.cols; x++)
		{
			float d = rng.uniform(-0.5, 0.5);
			img.at<float>(y, x) = img.at<float>(y, x) + d;
		}
	}
	
	//�����׼��ͻ���
	Mat sum;
	integral(img, sum);
	//Ϊ�˱�����ʾ��ת��CV_8U��ʽ
	Mat sum8U = Mat_<uchar>(sum);

	//����ƽ����ͻ���
	Mat sqsum;
	integral(img, sum, sqsum);
	//Ϊ�˱�����ʾ��ת��CV_8U��ʽ
	Mat sqsum8U = Mat_<uchar>(sqsum);

	//������б��ͻ���
	Mat tilted;
	integral(img, sum, sqsum, tilted);
	//Ϊ�˱�����ʾ��ת��CV_8U��ʽ
	Mat tilted8U = Mat_<uchar>(tilted);

	//������
	namedWindow("sum8U", WINDOW_NORMAL);
	namedWindow("sqsum8U", WINDOW_NORMAL);
	namedWindow("tilted8U", WINDOW_NORMAL);
	imshow("sum8U", sum8U);
	imshow("sqsum8U", sqsum8U);
	imshow("tilted8U", tilted8U);

	waitKey();
	return 0;
}