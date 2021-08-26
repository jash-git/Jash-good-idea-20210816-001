#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
Mat image;//����Ĳ�ɫͼ��
Mat fImage;// image ��һ����Ľ��
Mat hlsImage;// BGR2HLS
Mat lsImg;//�������ͶȺ����Ⱥ�ͼ��
//ͼ���С
int width, height;
//��ʾ����
string winName = "�������ͶȺ�����";
int L=60;
int S=60;
int MAX_VALUE = 100;//��������Ϊ 1/100
void callBack_LS(int, void*);
int main(int argc, char*argv[])
{
	//�����ɫͼ��
	image = imread(argv[1], CV_LOAD_IMAGE_COLOR);
	if (!image.data || image.channels() != 3)
		return -1;
	imshow("ԭͼ", image);
	//ͼ���С
	width = image.cols;
	height = image.rows;
	// image ��һ��
	image.convertTo(fImage, CV_32FC3, 1.0 / 255, 0);
	namedWindow(winName, WINDOW_AUTOSIZE);
	//����������
	createTrackbar("���Ͷ�(S)", winName, &S, MAX_VALUE, callBack_LS);
	//�������Ͷ�
	createTrackbar("����(L)", winName, &L, MAX_VALUE, callBack_LS);
	callBack_LS(0, 0);
	waitKey(0);
	return 0;
}
void callBack_LS(int, void*)
{
	// ��һ�� �� BGR ��ʽ ת��Ϊ HLS ��ʽ
	// 0 =< H <= 360 �� 0=< L < = 1��0=< S <= 1
	cvtColor(fImage, hlsImage, COLOR_BGR2HLS);
	//
	for (int r = 0; r < height; r++)
	{
		for (int c = 0; c < width; c++)
		{
			//�������Ⱥ�����
			Vec3f hls = hlsImage.at<Vec3f>(r, c);
			// ͨ���ӷ�
			/*
			hls = Vec3f(hls[0], 
				hls[1] +L/double(MAX_VALUE) > 1 ? 1 : hls[1] + L/double(MAX_VALUE), 
				hls[2] + S/double(MAX_VALUE) > 1 ? 1 : hls[2] + S/double(MAX_VALUE));
			*/
			//ͨ���˷�
			hls = Vec3f(hls[0],
				(1 + L / double(MAX_VALUE))*hls[1] > 1 ? 1 : (1 + L / double(MAX_VALUE))*hls[1],
				(1 + S / double(MAX_VALUE))*hls[2] > 1 ? 1 : (1 + S / double(MAX_VALUE))*hls[2]
			);
			hlsImage.at<Vec3f>(r, c) = hls;
		}
	}
	// HLS ת��Ϊ RGB
	cvtColor(hlsImage,lsImg, COLOR_HLS2BGR);
	lsImg.convertTo(lsImg, CV_8UC3, 255);
	imshow(winName, lsImg);
	imwrite("lsImg.jpg", lsImg);
}