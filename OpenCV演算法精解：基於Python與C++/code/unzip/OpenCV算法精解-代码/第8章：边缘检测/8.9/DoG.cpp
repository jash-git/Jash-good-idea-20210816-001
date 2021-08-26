#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
/*��ɢ�Ķ�ά�������*/
void conv2D(InputArray _src, InputArray _kernel, OutputArray _dst, int ddepth, Point anchor = Point(-1, -1), int borderType = BORDER_DEFAULT)
{
	//�����˳ʱ����ת180
	Mat kernelFlip;
	flip(_kernel, kernelFlip, -1);
	//���ÿһ������,�����ӦԪ�����Ȼ�����
	filter2D(_src, _dst, ddepth, kernelFlip, anchor, 0.0, borderType);
}
/*�ɷ������ɢ��ά���,��ˮƽ����ľ��,Ȼ����Ž��д�ֱ����ľ��*/
void sepConv2D_X_Y(InputArray src, OutputArray src_kerX_kerY, int ddepth, InputArray kernelX, InputArray kernelY, Point anchor = Point(-1, -1), int borderType = BORDER_DEFAULT)
{
	//���������ˮƽ�������˵ľ��
	Mat src_kerX;
	conv2D(src, kernelX, src_kerX, ddepth, anchor, borderType);
	//����õ��ľ�������Ȼ����źʹ�ֱ����ľ���˾�����õ����յ����
	conv2D(src_kerX, kernelY, src_kerX_kerY, ddepth, anchor, borderType);
}
//��˹���
Mat gaussConv(Mat I,float sigma,int s)
{
	//����ˮƽ�����ϵķǹ�һ���ĸ�˹��
	Mat xkernel = Mat::zeros(1, s, CV_32FC1);
	//����λ��
	int cs = (s - 1) / 2;
	//����
	float sigma2 = pow(sigma, 2.0);
	for (int c = 0; c < s; c++)
	{
		float norm2 = pow(float(c - cs), 2.0);
		xkernel.at<float>(0, c) = exp(-norm2 / (2 * sigma2));
	}
	//�� xkernel ת�ã��õ���ֱ�����ϵľ����
	Mat ykernel = xkernel.t();
	//�������˵ľ������
	Mat gauConv;
	sepConv2D_X_Y(I, gauConv, CV_32F, xkernel, ykernel);
	gauConv.convertTo(gauConv, CV_32F, 1.0 / sigma2);
	return gauConv;
}
//��˹���
Mat DoG(Mat I, float sigma, int s, float k=1.1)
{
	//���׼��Ϊ sigma �ķǹ�һ���ĸ�˹�˾��
	Mat Ig = gaussConv(I, sigma, s);
	//���׼��Ϊ k*sigma �ķǹ�һ���ĸ�˹�˾��
	Mat Igk = gaussConv(I, k*sigma, s);
	//������˹����������
	Mat doG = Igk - Ig;
	return doG;
}
int main(int argc, char*argv[])
{
	//����ͼ�����
	Mat I = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if (!I.data)
		return -1;
	//��˹���
	float sigma = 6;
	int s = 37;
	float k = 1.05;
	Mat doG=DoG(I, sigma, s, k);
	//��ֵ����
	Mat edge;
	threshold(doG, edge, 0, 255, THRESH_BINARY);
	//��ʾ��ֵ��Ե
	imshow("��˹��ֱ�Ե", edge);
	imwrite("DoG.jpg", edge);
	waitKey(0);
	return 0;
}