#include<iostream>
using namespace std;
#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
using namespace cv;
Mat edge;//��Եͼ
int Thresh = 255;//��ֵ
const int MAX_THRSH = 255;
/*��ɢ�Ķ�ά�������*/
void conv2D(InputArray _src, InputArray _kernel, OutputArray _dst, int ddepth, Point anchor = Point(-1, -1), int borderType = BORDER_DEFAULT)
{
	//�����˳ʱ����ת180
	Mat kernelFlip;
	flip(_kernel, kernelFlip, -1);
	//���ÿһ������,�����ӦԪ�����Ȼ�����
	filter2D(_src, _dst, CV_32FC1, kernelFlip, anchor, 0.0, borderType);
}
/*laplacian ���*/
void laplacian(InputArray src, OutputArray dst, int ddepth,int borderType = BORDER_DEFAULT)
{
	Mat lapKernel = (Mat_<float>(3, 3) << 0, -1, 0, -1, 4, -1, 0, -1, 0);
	conv2D(src, lapKernel, dst, ddepth, Point(-1, -1), borderType);
}
void callback_thresh(int, void*)
{
	Mat copyEdge = edge.clone();
	Mat thresh_edge;//��ֵ��������ֵ
	threshold(copyEdge, thresh_edge, Thresh, MAX_THRSH, cv::THRESH_BINARY);
	imshow("��ֵ�����ı�Եǿ��", thresh_edge);
}
//������
int main(int argc, char*argv[])
{
	/*��һ��������Ҷ�ͼ�����*/
	Mat image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if (!image.data)
	{
		cout << "û��ͼƬ" << endl;
		return -1;
	}
	/*�ڶ����� laplacian ���*/
	Mat img_lap;
	laplacian(image, img_lap, CV_32FC1);
	//�������͵�ת�����������ĻҶȼ���ʾ
	convertScaleAbs(img_lap, edge, 1, 0);
	imshow("��Եǿ��", edge);
	imwrite("img3_lap.jpg", edge);
	//��ֵ�����ı�Եǿ��
	namedWindow("��ֵ�����ı�Եǿ��", cv::WINDOW_AUTOSIZE);
	createTrackbar("��ֵ", "��ֵ�����ı�Եǿ��", &Thresh, MAX_THRSH, callback_thresh);
	callback_thresh(0, 0);
	waitKey(0);
	return 0;
}