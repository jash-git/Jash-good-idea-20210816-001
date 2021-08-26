#include<iostream>
using namespace std;
#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
using namespace cv;
Mat edge;//��Եͼ
int Thresh = 255;//��ֵ
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
void scharr(InputArray src, OutputArray dst, int ddepth, int x, int y = 0, int borderType = BORDER_DEFAULT)
{
	CV_Assert(!(x == 0 && y == 0));
	Mat scharr_x = (Mat_<float>(3, 3) << 3, 0, -3, 10, 0, -10, 3, 0, -3);
	Mat scharr_y = (Mat_<float>(3, 3) << 3, 10, 3, 0, 0, 0, -3, -10, -3);
	//�� x ��������ʱ��src �� scharr_x ���
	if (x != 0)
	{
		conv2D(src, scharr_x, dst, ddepth, Point(-1, -1),borderType);
	}
	//�� y ��������ʱ��src �� scharr_y ���
	if (y != 0)
	{
		conv2D(src, scharr_y, dst, ddepth, Point(-1, -1), borderType);
	}
}
void callback_thresh(int, void*)
{
	Mat copyEdge = edge.clone();
	Mat thresh_edge;//��ֵ��������ֵ
	threshold(copyEdge, thresh_edge, Thresh, MAX_THRESH, cv::THRESH_BINARY);
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
	/*�ڶ����� scharr ���*/
	//ͼ������ scharr_x ����˾��
	Mat img_scharr_x;
	scharr(image, img_scharr_x, CV_32FC1, 1, 0);
	//ͼ������ scharr_y ����˾��
	Mat img_scharr_y;
	scharr(image, img_scharr_y, CV_32FC1, 0, 1);
	//�����������ĻҶȼ���ʾ
	Mat abs_img_scharr_x, abs_img_scharr_y;
	convertScaleAbs(img_scharr_x, abs_img_scharr_x, 1, 0);
	convertScaleAbs(img_scharr_y, abs_img_scharr_y, 1, 0);
	imshow("��ֱ����ı�Ե", abs_img_scharr_x);
	imwrite("img1_sch_v_edge.jpg", abs_img_scharr_x);
	imshow("ˮƽ����ı�Ե", abs_img_scharr_y);
	imwrite("img1_sch_h_edge.jpg", abs_img_scharr_y);
	/*��������ͨ���ڶ����õ���������������������յı�Եǿ��*/
	//�������ƽ�����ķ�ʽ
	Mat img_scharr_x2, img_scharr_y2;
	pow(img_scharr_x, 2.0, img_scharr_x2);
	pow(img_scharr_y, 2.0, img_scharr_y2);
	sqrt(img_scharr_x2 + img_scharr_y2, edge);
	//��������ת������Եǿ�ȵĻҶȼ���ʾ
	edge.convertTo(edge, CV_8UC1);
	imshow("��Եǿ��", edge);
	imwrite("img1_sch_edge.jpg", edge);
	//��ֵ�����ı�Եǿ��
	namedWindow("��ֵ�����ı�Եǿ��", cv::WINDOW_AUTOSIZE);
	createTrackbar("��ֵ", "��ֵ�����ı�Եǿ��", &Thresh, MAX_THRESH, callback_thresh);
	callback_thresh(0, 0);
	waitKey(0);
	return 0;
}