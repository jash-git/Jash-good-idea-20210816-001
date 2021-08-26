#include<iostream>
using namespace std;
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
//������˹�������
Mat createGaussKernel(float sigma, int H, int W)
{
	CV_Assert(H % 2 == 1 && W % 2 == 1);
	if (sigma <= 0)
		sigma = sqrt(float(W + H));
	//��һ��:���� H �� W �еľ���
	Mat gaussMatrix(Size(W, H), CV_32FC1);
	int cH = (H - 1) / 2;
	int cW = (W - 1) / 2;
	float coefficient = 1.0 / (sqrt(2 * CV_PI)*sigma);
	for (int r = 0; r < H; r++)
	{
		for (int c = 0; c < W; c++)
		{
			float norm2 = pow(r - cH, 2.0) + pow(c - cW, 2.0);
			gaussMatrix.at<float>(r, c) = coefficient*exp(-norm2 / (2 * pow(sigma, 2)));
		}
	}
	//�ڶ������������ĺ�
	float sumGM = sum(gaussMatrix)[0];
	//������: gaussMatrix ���Ժ� sumGM
	Mat gaussKernel = gaussMatrix / sumGM;
	return gaussKernel;
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
//��˹ƽ�������ص����������Ǹ�����
Mat  gaussBlur(const Mat & image, Size winSize, float sigma, Point anchor = Point(-1, -1), int borderType = BORDER_DEFAULT)
{
	//����˵Ŀ�߾�Ϊ����
	CV_Assert(winSize.width % 2 == 1 && winSize.height % 2 == 1);
	//������ֱ����ĸ�˹�������
	Mat gKernel_y = getGaussianKernel(sigma, winSize.height, CV_64F);
	//����ˮƽ����ĸ�˹�������
	Mat gKernel_x = getGaussianKernel(sigma, winSize.width, CV_64F);
	gKernel_x = gKernel_x.t();//ת��
	//����ĸ�˹���
	Mat blurImage;
	sepConv2D_Y_X(image, blurImage, CV_32FC1, gKernel_y, gKernel_x, Point(-1, -1));
	return blurImage;
}
int main(int argc, char*argv[])
{
	//����ͼ�����
	Mat image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if (!image.data)
	{
		cout << "û��ͼƬ" << endl;
		return 0;
	}
	imshow("ԭͼ", image);
	/*��������ͼ����� 8 λͼ*/
	Mat blurImage = gaussBlur(image, Size(21,21), 3);
	//��������ת��
	for (int r = 0; r < image.rows; r++)
	{
		for (int c = 0; c < image.cols; c++)
		{
			float pixel = blurImage.at<float>(r, c);
			blurImage.at<float>(r, c) = roundf(pixel);
		}
	}
	blurImage.convertTo(blurImage, CV_8UC1);
	imshow("��˹ƽ��-8λͼ", blurImage);
	/*��������ͼ���ǹ�һ����*/
	Mat image_0_1;
	image.convertTo(image_0_1, CV_32FC1, 1.0 / 255);
	Mat blurImage_0_1 = gaussBlur(image_0_1, Size(21, 21), 3);
	imshow("��˹ƽ��-0-1", blurImage_0_1);
	waitKey(0);
	return 0;
}