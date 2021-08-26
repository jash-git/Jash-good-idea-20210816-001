#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
#include<iostream>
using namespace std;
//�õ�һά�� ��x^2 /(2*sigma^2)-1��Gauss(x,sigma) �� һά�� Gauss(x,sigma)
void getSepLoGKernel(float sigma,int length,Mat & kernelX,Mat & kernelY)
{
	//�����ڴ�
	kernelX.create(Size(length, 1), CV_32FC1);
	kernelY.create(Size(1, length), CV_32FC1);
	int center = (length - 1) / 2;
	double sigma2 = pow(sigma, 2.0);
	double cofficient = 1.0 / (sqrt(2 * CV_PI)*sigma);
	for (int c = 0; c < length; c++)
	{
		float norm2 = pow(c - center, 2.0);
		kernelY.at<float>(c,0) = cofficient*exp(-norm2 / (2 * sigma2));
		kernelX.at<float>(0, c) = (norm2 / sigma2 - 1.0)*kernelY.at<float>(c, 0);
	}
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
// LoG ���
Mat LoG(InputArray image,float sigma,int win)
{
	Mat kernelX, kernelY;
	//�õ����������
	getSepLoGKernel(sigma, win, kernelX, kernelY);
	//��ˮƽ����ٴ�ֱ���
	Mat covXY;
	sepConv2D_X_Y(image, covXY, CV_32FC1, kernelX, kernelY);
	//�����ת��
	Mat kernelX_T = kernelX.t();
	Mat kernelY_T = kernelY.t();
	//�ȴ�ֱ�����ˮƽ���
	Mat covYX;
	sepConv2D_Y_X(image,covYX,CV_32FC1,kernelX_T,kernelY_T);
	//���������������ĺͣ��õ� LoG ���
	Mat LoGCov;
	add(covXY, covYX, LoGCov);
	return LoGCov;
}
int main(int argc, char*argv[])
{
	//����ͼ��
	Mat image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if (!image.data)
		return -1;
	// LoG ���
	float sigma = 4;
	int win = 25;
	Mat loG = LoG(image, sigma, win);
	//��������ת����ת��Ϊ CV_8U
	/*
	// ��ֵ��Ե
	Mat threshEdge=Mat::zeros(loG.size(), CV_8UC1);
	int rows = threshEdge.rows;
	int cols = threshEdge.cols;
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			if (loG.at<float>(r, c) > 0)
				threshEdge.at<uchar>(r, c) = 255;
		}
	}
	*/
	//�� 0 Ϊ��ֵ�����ɱ�Ե��ֵͼ
	Mat edge;
	threshold(loG, edge, 0, 255, THRESH_BINARY);
	imshow("��ֵ��Եͼ", edge);
	waitKey(0);
	return 0;
}