#include <opencv2\opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	system("color F0");  //��DOS������ɰ׵׺���
	Mat img = imread("lena.png");
	if (!(img.data))
	{
		cout << "��ȡͼ�������ȷ��ͼ���ļ��Ƿ���ȷ" << endl;
		return -1;
	}

	
	RNG rng(10086);//����������������������
	
	//���ò�����־flags
	int connectivity = 4;  //��ͨ����ʽ
	int maskVal = 255;  //����ͼ�����ֵ
	int flags = connectivity|(maskVal<<8)| FLOODFILL_FIXED_RANGE;  //��ˮ��������ʽ��־

	//������ѡ�����ص�Ĳ�ֵ
	Scalar loDiff = Scalar(20, 20, 20);
	Scalar upDiff = Scalar(20, 20, 20);

	//������ģ�������
	Mat mask = Mat::zeros(img.rows + 2, img.cols + 2, CV_8UC1);

	while (true)
	{
		//�������ͼ����ĳһ���ص�
		int py = rng.uniform(0,img.rows-1);
		int px = rng.uniform(0, img.cols - 1);
		Point point = Point(px, py);
		
		//��ɫͼ������������ֵ
		Scalar newVal = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));

		//��ˮ��亯��
		int area = floodFill(img, mask, point, newVal, &Rect(),loDiff,upDiff,flags);
	
		//������ص������������Ŀ
		cout << "���ص�x��" << point.x << "  y:" << point.y
			<< "     ���������Ŀ��" << area << endl;

		//�������ͼ����
		imshow("���Ĳ�ɫͼ��", img);
		imshow("��ģͼ��", mask);

		//�ж��Ƿ��������
		int c = waitKey(0);
		if ((c&255)==27)
		{
			break;
		}
	}
	return 0;
}