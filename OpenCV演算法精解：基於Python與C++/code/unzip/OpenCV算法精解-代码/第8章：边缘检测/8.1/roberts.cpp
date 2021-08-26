#include<iostream>
using namespace std;
#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
using namespace cv;
Mat edge;//��Եͼ
int Thresh = 25;//��ֵ
const int MAX_THRESH = 255;
/*��ɢ�Ķ�ά�������*/
void conv2D(InputArray _src, InputArray _kernel, OutputArray _dst, int ddepth, Point anchor = Point(-1, -1), int borderType = BORDER_DEFAULT)
{
	//�����˳ʱ����ת180
	Mat kernelFlip;
	flip(_kernel, kernelFlip, -1);
	//���ÿһ������,�����ӦԪ�����Ȼ�����
	filter2D(_src, _dst, CV_32FC1, kernelFlip, anchor, 0.0, borderType);
}
/*roberts ���*/
void roberts(InputArray src, OutputArray dst, int ddepth, int x, int y = 0, int borderType = BORDER_DEFAULT)
{
	CV_Assert(!(x == 0 && y == 0));
	Mat roberts_1 = (Mat_<float>(2, 2) << 1, 0, 0, -1);
	Mat roberts_2 = (Mat_<float>(2, 2) << 0, 1, -1, 0);
	//�� x ��������ʱ��src �� roberts_1 ���
	if (x != 0)
	{
		conv2D(src, roberts_1, dst, ddepth, Point(0, 0), borderType);
	}
	//�� y ��������ʱ��src �� roberts_2 ���
	if (y != 0)
	{
		conv2D(src, roberts_2, dst, ddepth, Point(0, 0), borderType);
	}
}
void callback_thresh(int, void*)
{
	Mat copyEdge = edge.clone();
	Mat thresh_edge;//��ֵ��������ֵ
	threshold(copyEdge, thresh_edge, Thresh, MAX_THRESH, cv::THRESH_BINARY);
	imshow("��ֵ�����ı�Եǿ��", thresh_edge);
	imwrite("thresh_edge.jpg", thresh_edge);
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
	/*�ڶ����� roberts ���*/
	//ͼ������ roberts_1 ����˾��
	Mat img_roberts_1;
	roberts(image, img_roberts_1, CV_32FC1, 1, 0);
	//ͼ������ roberts_2 ����˾��
	Mat img_roberts_2;
	roberts(image, img_roberts_2, CV_32FC1, 0, 1);
	//�����������ĻҶȼ���ʾ
	Mat abs_img_roberts_1, abs_img_roberts_2;
	convertScaleAbs(img_roberts_1, abs_img_roberts_1, 1, 0);
	convertScaleAbs(img_roberts_2, abs_img_roberts_2, 1, 0);
	imshow("135�㷽���ϵı�Ե", abs_img_roberts_1);
	imwrite("img_robert_135_edge.jpg", abs_img_roberts_1);
	imshow("45�㷽���ϵı�Ե", abs_img_roberts_2);
	imwrite("img_robert_45_edge.jpg", abs_img_roberts_2);
	/*��������ͨ���ڶ����õ���������������������յı�Եǿ��*/
	//�������ƽ�����ķ�ʽ
	Mat img_roberts_1_2, img_roberts_2_2;
	pow(img_roberts_1, 2.0, img_roberts_1_2);
	pow(img_roberts_2, 2.0, img_roberts_2_2);
	sqrt(img_roberts_1_2 + img_roberts_2_2, edge);
	//��������ת������Եǿ�ȵĻҶȼ���ʾ
	edge.convertTo(edge, CV_8UC1);
	imshow("��Եǿ��", edge);
	imwrite("img_robert_edge.jpg", edge);
	//��ֵ�����ı�Եǿ��
	namedWindow("��ֵ�����ı�Եǿ��", cv::WINDOW_AUTOSIZE);
	createTrackbar("��ֵ", "��ֵ�����ı�Եǿ��", &Thresh, MAX_THRESH, callback_thresh);
	callback_thresh(0, 0);
	//��ʾ����Ч��
	Mat reliefFigure = img_roberts_1 + 128;
	Mat reliefImage;
	reliefFigure.convertTo(reliefImage, CV_8UC1);
	imshow("����ͼЧ��", reliefImage);
	imwrite("reliefImage.jpg", reliefImage);
	waitKey(0);
	return 0;
}