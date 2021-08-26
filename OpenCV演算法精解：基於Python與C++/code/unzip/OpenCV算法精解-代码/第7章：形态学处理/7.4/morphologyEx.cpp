#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
//����ͼ��
Mat I;
//���ͼ��
Mat d;
//�ṹԪ
Mat element;
string window = "��̬ѧ����";
//�ṹԪ�뾶
int r = 1;
int MAX_R = 20;
//��������
int i = 1;
int MAX_I = 20;
//�ص�����������r��i
void callBack(int, void*)
{
	//�����ṹԪ
	element = getStructuringElement(MORPH_RECT,Size(2*r+1,2*r+1));
	//��̬ѧ����
	morphologyEx(I, d, cv::MORPH_HITMISS, element,Point(-1,-1),i);
	//��ʾ��̬�����Ч��
	imshow(window, d);
}
int main(int argc, char*argv[])
{
	//����ͼ��
	I = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if (!I.data)
		return 0;
	//��ʾԭͼ
	imshow("ԭͼ", I);
	//������ʾ��̬ѧ�����ʾ����
	namedWindow(window, 1);
	//��������r�Ľ�����
	createTrackbar("�뾶", window, &r, MAX_R, callBack);
	//��������i�Ľ�����
	createTrackbar("��������", window, &i, MAX_I, callBack);
	callBack(0, 0);
	waitKey(0);
	return 0;
}