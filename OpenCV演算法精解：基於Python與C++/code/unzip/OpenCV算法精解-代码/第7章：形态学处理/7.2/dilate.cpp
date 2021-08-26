#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
using namespace cv;
int r = 1;//�ṹԪ�뾶
int MAX_R = 20;//�������뾶
Mat I;//����ͼ��
Mat D;//���ͼ��
//�ص����������� r
void callBack(int, void *)
{
	//����ֻ�д�ֱ����ľ��νṹԪ
	Mat s = getStructuringElement(MORPH_RECT, Size(1, 2 * r + 1));
	//���Ͳ���
	dilate(I, D, s);
	//��ʾ���ͽ��
	imshow("dilate", D);
}
int main(int argc, char*argv[])
{
	//����ͼ��
	I = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if (!I.data)
		return -1;
	//��ʾԭͼ
	imshow("I", I);
	//������ʾ���ͽ������ʾ����
	namedWindow("dilate", WINDOW_AUTOSIZE);
	// �������� r �Ľ�����
	createTrackbar("�뾶", "dilate", &r, MAX_R, callBack);
	callBack(0, 0);
	waitKey(0);
	return 0;
}