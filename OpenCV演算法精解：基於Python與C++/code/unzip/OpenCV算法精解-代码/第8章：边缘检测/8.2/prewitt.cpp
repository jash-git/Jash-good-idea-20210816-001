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

/*�ɷ������ɢ��ά���,��ˮƽ����ľ��,Ȼ����Ž��д�ֱ����ľ��*/
void sepConv2D_X_Y(InputArray src, OutputArray src_kerX_kerY, int ddepth, InputArray kernelX, InputArray kernelY, Point anchor = Point(-1, -1), int borderType = BORDER_DEFAULT)
{
	//���������ˮƽ�������˵ľ��
	Mat src_kerX;
	conv2D(src, kernelX, src_kerX, ddepth, anchor, borderType);
	//����õ��ľ�������Ȼ����źʹ�ֱ����ľ���˾�����õ����յ����
	conv2D(src_kerX, kernelY, src_kerX_kerY, ddepth, anchor, borderType);
}
/*�ɷ������ɢ��ά���,�ȴ�ֱ����ľ����Ȼ�����ˮƽ����ľ��*/
void sepConv2D_Y_X(InputArray src, OutputArray src_kerY_kerX, int ddepth, InputArray kernelY, InputArray kernelX, Point anchor = Point(-1, -1), int borderType = BORDER_DEFAULT)
{
	//��������봹ֱ�������˵ľ��
	Mat src_kerY;
	conv2D(src, kernelY, src_kerY, ddepth, anchor, borderType);
	//����õ��ľ�������Ȼ����ź�ˮƽ����ľ���˾�����õ����յ����
	conv2D(src_kerY, kernelX, src_kerY_kerX, ddepth, anchor, borderType);
}

/*
	prewitt�������
*/
void prewitt(InputArray src,OutputArray dst, int ddepth,int x, int y = 0, int borderType = BORDER_DEFAULT)
{
	CV_Assert(!(x == 0 && y == 0));
	//��� x!=0��src �� prewitt_x����˽��о������
	if (x != 0)
	{
		//�ɷ����prewitt_x�����
		Mat prewitt_x_y = (Mat_<float>(3, 1) << 1, 1, 1);
		Mat prewitt_x_x = (Mat_<float>(1, 3) << 1, 0, -1);
		//�ɷ������ɢ�Ķ�ά���
		sepConv2D_Y_X(src, dst, ddepth, prewitt_x_y, prewitt_x_x, Point(-1, -1), borderType);
	}
	if (y != 0)
	{
		//�ɷ����prewitt_y�����
		Mat prewitt_y_x = (Mat_<float>(1, 3) << 1, 1, 1);
		Mat prewitt_y_y = (Mat_<float>(3, 1) << 1, 0, -1);
		//�ɷ������ɢ��ά���
		sepConv2D_X_Y(src, dst, ddepth, prewitt_y_x, prewitt_y_y, Point(-1, -1), borderType);
	}
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
	/*��һ��:����ͼ�����(�Ҷ�ͼ)*/
	
	Mat image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if (!image.data)
	{
		cout << "û��ͼƬ" << endl;
		return -1;
	}

	/*�ڶ���:previwitt���*/

	//ͼ������ prewitt_x����˵ľ��
	Mat img_prewitt_x;
	prewitt(image, img_prewitt_x,CV_32FC1,1, 0);
	//ͼ�������prewitt_y����˾��
	Mat img_prewitt_y;
	prewitt(image, img_prewitt_y, CV_32FC1, 0, 1);

	/*������:ˮƽ����ʹ�ֱ����ı�Եǿ��*/
	//��������ת��,��Եǿ�ȵĻҶȼ���ʾ
	Mat abs_img_prewitt_x, abs_img_prewitt_y;
	convertScaleAbs(img_prewitt_x, abs_img_prewitt_x, 1, 0);
	convertScaleAbs(img_prewitt_y, abs_img_prewitt_y, 1, 0);
	imshow("��ֱ����ı�Ե", abs_img_prewitt_x);
	//imwrite("img1_v_edge.jpg", abs_img_prewitt_x);
	imshow("ˮƽ����ı�Ե", abs_img_prewitt_y);
	//imwrite("img1_h_edge.jpg", abs_img_prewitt_y);
	/*���Ĳ���ͨ���������õ�����������ı�Եǿ��,������յı�Եǿ��*/
	//�������ƽ�����ķ�ʽ
	Mat img_prewitt_x2, image_prewitt_y2;
	pow(img_prewitt_x,2.0,img_prewitt_x2);
	pow(img_prewitt_y,2.0,image_prewitt_y2);
	sqrt(img_prewitt_x2 + image_prewitt_y2, edge);
	//��������ת��,��Ե��ǿ�ȻҶȼ���ʾ
	edge.convertTo(edge, CV_8UC1);
	imshow("��Եǿ��",edge);
	//imwrite("img1_edge.jpg", edge);
	Mat tempedge;
	threshold(edge, tempedge, 25, MAX_THRSH, cv::THRESH_BINARY);
	imwrite("img3_thresh_edge_25.jpg", tempedge);
	//��ֵ�����ı�Եǿ��
	namedWindow("��ֵ�����ı�Եǿ��", cv::WINDOW_AUTOSIZE);
	createTrackbar("��ֵ", "��ֵ�����ı�Եǿ��", &Thresh,MAX_THRSH,callback_thresh);
	callback_thresh(0, 0);
	waitKey(0);
	return 0;
}