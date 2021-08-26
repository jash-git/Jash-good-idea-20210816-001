#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
#include<iostream>
using namespace std;
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
int main(int argc, char*argv[])
{
	Mat src = (Mat_<float>(5, 5) << 1, 2, 3, 10, 12,
		32, 43, 12, 4, 190,
		12, 234, 78, 0, 12,
		43, 90, 32, 8, 90,
		71, 12, 4, 98, 123);
	Mat kernel = (Mat_<float>(3, 3) << 1, 0, -1, 1, 0, -1, 1, 0, -1);
	//�������
	Mat result;
	conv2D(src, kernel, result, CV_32FC1, Point(-1, -1), BORDER_REFLECT);
	//������
	Mat kernel1 = (Mat_<float>(1, 3) << 1, 0, -1);
	Mat kernel2 = (Mat_<float>(3, 1) << 1, 1, 1);
	Mat c_same;
	sepConv2D_X_Y(src, c_same, CV_32FC1, kernel1, kernel2,Point(-1,-1),2);
	return 0;
}