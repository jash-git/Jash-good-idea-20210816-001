#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
#include<iostream>
using namespace std;
//����׳�
int factorial(int n)
{
	int fac = 1;
	// 0 �Ľ׳˵��� 1
	if (n == 0)
		return fac;
	for (int i = 1; i <= n; i++)
		fac *= i;
	return fac;
}
//����ƽ��ϵ��
Mat getPascalSmooth(int n)
{
	Mat pascalSmooth = Mat::zeros(Size(n, 1), CV_32FC1);
	for (int i = 0; i < n; i++)
		pascalSmooth.at<float>(0, i) = factorial(n - 1) / (factorial(i) * factorial(n - 1 - i));
	return pascalSmooth;
}
//������
Mat getPascalDiff(int n)
{
	Mat pascalDiff = Mat::zeros(Size(n, 1), CV_32FC1);
	Mat pascalSmooth_previous = getPascalSmooth(n - 1);
	for (int i = 0; i<n; i++)
	{
		if (i == 0)
			pascalDiff.at<float>(0, i) = 1;
		else if (i == n - 1)
			pascalDiff.at<float>(0, i) = -1;
		else
			pascalDiff.at<float>(0, i) = pascalSmooth_previous.at<float>(0, i) - pascalSmooth_previous.at<float>(0, i - 1);
	}
	return pascalDiff;
}
/*��ɢ�Ķ�ά�������*/
void conv2D(InputArray _src, InputArray _kernel, OutputArray _dst, int ddepth, Point anchor = Point(-1, -1), int borderType = BORDER_DEFAULT)
{
	//�����˳ʱ����ת180
	Mat kernelFlip;
	flip(_kernel, kernelFlip, -1);
	//���ÿһ������,�����ӦԪ�����Ȼ�����
	filter2D(_src, _dst, ddepth, kernelFlip, anchor, 0.0, borderType);
}
/*�ɷ������ɢ��ά���,�ȴ�ֱ����ľ����Ȼ�����ˮƽ����ľ��*/
void sepConv2D_Y_X(InputArray src, OutputArray src_kerY_kerX, int ddepth, InputArray kernelY, InputArray kernelX, Point anchor = Point(-1, -1), int borderType = BORDER_DEFAULT)
{
	//��������봹ֱ�������˵ľ��
	Mat src_kerY;
	conv2D(src, kernelY, src_kerY, ddepth, anchor, borderType);
	//����õ��ľ�������Ȼ����ź�ˮƽ����ľ���˾��
	conv2D(src_kerY, kernelX, src_kerY_kerX, ddepth, anchor, borderType);
}
/*�ɷ������ɢ��ά�������ˮƽ����ľ��,Ȼ����Ž��д�ֱ����ľ����������������� CV_32FC1 ���� CV_64FC1*/
void sepConv2D_X_Y(InputArray src, OutputArray src_kerX_kerY, int ddepth, InputArray kernelX, InputArray kernelY, Point anchor = Point(-1, -1), int borderType = BORDER_DEFAULT)
{
	//���������ˮƽ�������˵ľ��
	Mat src_kerX;
	conv2D(src, kernelX, src_kerX, CV_32F, anchor, borderType);
	//����õ��ľ�������Ȼ����źʹ�ֱ����ľ���˾��
	conv2D(src_kerX, kernelY, src_kerX_kerY, ddepth, anchor, borderType);
}
// sobel ��Ե���
Mat sobel(Mat image, int x_flag, int y_flag, int winSize, int borderType)
{
	// sobel ����˵Ĵ��ڴ�СΪ���� 3 ������ 
	CV_Assert(winSize >= 3 && winSize % 2 == 1);
	//ƽ��ϵ��
	Mat pascalSmooth = getPascalSmooth(winSize);
	//���ϵ��
	Mat pascalDiff = getPascalDiff(winSize);
	Mat image_con_sobel;
	/* �� x_falg != 0 ʱ������ͼ����ˮƽ����� Sobel �˵ľ��*/
	if (x_flag != 0)
	{
		//���ݿɷ������˵�����
		//�Ƚ���һά��ֱ�����ϵ�ƽ�����ٽ���һάˮƽ����Ĳ��
		sepConv2D_Y_X(image, image_con_sobel, CV_32FC1, pascalSmooth.t(), pascalDiff, Point(-1, -1), borderType);
	}
	/* �� x_falg == 0 �� y_flag != 0 ʱ������ͼ���봹ֱ ����� Sobel �˵ľ��*/
	if (x_flag == 0 && y_flag != 0)
	{
		//���ݿɷ������˵�����
		//�Ƚ���һάˮƽ�����ϵ�ƽ�����ٽ���һά��ֱ����Ĳ��
		sepConv2D_X_Y(image, image_con_sobel, CV_32FC1, pascalSmooth, pascalDiff.t(), Point(-1, -1), borderType);
	}
	return image_con_sobel;
}
int main(int argc, char*argv[])
{
	//����ͼƬ����
	Mat image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if (!image.data)
		return -1;
	/* --- sobel ��Ե��� --- */
	//��ˮƽ����� sobel �˾��
	Mat image_Y_X = sobel(image, 1, 0, 3, 4);
	//��ֱ����ı�Եǿ��
	Mat imageYX_abs = abs(image_Y_X);
	//��ֱ�����Եǿ�ȵĻҶȼ���ʾ
	Mat imageYX_gray;
	imageYX_abs.convertTo(imageYX_gray, CV_8UC1, 1.0, 0);
	imshow("��ֱ����ı�Եǿ��", imageYX_gray);
	//�봹ֱ����� sobel �˾��
	Mat image_X_Y = sobel(image, 0, 1, 3, 4);
	//ˮƽ����ı�Եǿ��
	Mat imageXY_abs = abs(image_X_Y);
	//ˮƽ�����Եǿ�ȵĻҶȼ���ʾ
	Mat imageXY_gray;
	imageXY_abs.convertTo(imageXY_gray, CV_8UC1, 1.0, 0);
	imshow("ˮƽ����ı�Եǿ��", imageXY_gray);
	//���ݴ�ֱ�����ˮƽ�����Եǿ�ȵ�ƽ���ͣ��õ����յı�Եǿ��
	Mat edge;
	magnitude(image_Y_X, image_X_Y, edge);
	//��Եǿ�ȵĻҶȼ���ʾ
	edge.convertTo(edge, CV_8UC1, 1.0, 0);
	imshow("��Ե", edge);
	imwrite("sobeledge.jpg", edge);
	waitKey(0);
	return 0;
}