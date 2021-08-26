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
/* Krisch ��Ե����㷨*/
Mat krisch(InputArray src,int borderType = BORDER_DEFAULT)
{
	//�洢�˸�������
	vector<Mat> eightEdge;
	eightEdge.clear();
	/*��1����ͼ�������8 �� ����˾��*/
	/*Krisch �� 8 ������˾����ǿɷ����*/
	//ͼ������� k1 ���
	Mat k1 = (Mat_<float>(3, 3) << 5, 5, 5, -3, 0, -3, -3, -3, -3);
	Mat src_k1;
	conv2D(src, k1, src_k1, CV_32FC1);
	convertScaleAbs(src_k1, src_k1);
	eightEdge.push_back(src_k1);
	//ͼ������� k2 ���
	Mat k2 = (Mat_<float>(3, 3) << -3, -3, -3, -3, 0, -3, 5, 5, 5);
	Mat src_k2;
	conv2D(src, k2, src_k2, CV_32FC1);
	convertScaleAbs(src_k2, src_k2);
	eightEdge.push_back(src_k2);
	//ͼ������� k3 ���
	Mat k3 = (Mat_<float>(3, 3) << -3, 5, 5, -3, 0, 5, -3, -3, -3);
	Mat src_k3;
	conv2D(src, k3, src_k3, CV_32FC1);
	convertScaleAbs(src_k3, src_k3);
	eightEdge.push_back(src_k3);
	//ͼ������� k4 ���
	Mat k4 = (Mat_<float>(3, 3) << -3, -3, -3, 5, 0, -3, 5, 5, -3);
	Mat src_k4;
	conv2D(src, k4, src_k4, CV_32FC1);
	convertScaleAbs(src_k4, src_k4);
	eightEdge.push_back(src_k4);
	//ͼ������� k5 ���
	Mat k5 = (Mat_<float>(3, 3) << -3, -3, 5, -3, 0, 5, -3, -3, 5);
	Mat src_k5;
	conv2D(src, k5, src_k5, CV_32FC1);
	convertScaleAbs(src_k5, src_k5);
	eightEdge.push_back(src_k5);
	//ͼ������� k6 ���
	Mat k6 = (Mat_<float>(3, 3) << 5, -3, -3, 5, 0, -3, 5, -3, -3);
	Mat src_k6;
	conv2D(src, k6, src_k6, CV_32FC1);
	convertScaleAbs(src_k6, src_k6);
	eightEdge.push_back(src_k6);
	//ͼ������� k7 ���
	Mat k7 = (Mat_<float>(3, 3) << -3, -3, -3, -3, 0, 5, -3, 5, 5);
	Mat src_k7;
	conv2D(src, k7, src_k7, CV_32FC1);
	convertScaleAbs(src_k7, src_k7);
	eightEdge.push_back(src_k7);
	//ͼ������� k8 ���
	Mat k8 = (Mat_<float>(3, 3) << 5, 5, -3, 5, 0, -3, -3, -3, -3);
	Mat src_k8;
	conv2D(src, k8, src_k8, CV_32FC1);
	convertScaleAbs(src_k8, src_k8);
	eightEdge.push_back(src_k8);
	/*�ڶ���������õİ˸�������,ȡ��Ӧλ�õ����ֵ����Ϊ���ı�Ե���*/
	Mat krischEdge = eightEdge[0].clone();
	for (int i = 0; i < 8; i++)
	{
		max(krischEdge, eightEdge[i], krischEdge);
	}
	return krischEdge;
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
	/*�ڶ��������Եͼ*/
	edge = krisch(image);
	//��ʾ��Եͼ
	imshow("krischEdge", edge);
	imwrite("img_kri_edge.jpg", edge);
	//��ֵ�����ı�Եǿ��
	namedWindow("��ֵ�����ı�Եǿ��", cv::WINDOW_AUTOSIZE);
	createTrackbar("��ֵ", "��ֵ�����ı�Եǿ��", &Thresh, MAX_THRSH, callback_thresh);
	callback_thresh(0, 0);
	waitKey(0);
	return 0;
}