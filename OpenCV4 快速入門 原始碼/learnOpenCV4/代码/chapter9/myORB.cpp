#include <opencv2\opencv.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

int main()
{
	Mat img = imread("lena.png");
	if (!img.data)
	{
		cout << "��ȷ��ͼ���ļ������Ƿ���ȷ" << endl;
		return -1;
	}

	//���� ORB �����������
	Ptr<ORB> orb = ORB::create(500, //��������Ŀ
		1.2f, //�������㼶֮������ű���
		8, //������ͼ�����ϵ��
		31, //��Ե��ֵ
		0, //ԭͼ�ڽ������еĲ���
		2, //����������ʱ��Ҫ�õ����ص���Ŀ
		ORB::HARRIS_SCORE, //ʹ�� Harris ��������������
		31, //����������ʱ�ؼ�����Χ����ĳߴ�
		20 //���� FAST �ǵ�ʱ����ֵ��ֵ����ֵ
	);

	//���� ORB �ؼ���
	vector<KeyPoint> Keypoints;
	orb->detect(img, Keypoints); //ȷ���ؼ���

								 //���� ORB ������
	Mat descriptions;
	orb->compute(img, Keypoints, descriptions); //����������

												//����������
	Mat imgAngel;
	img.copyTo(imgAngel);
	//���Ʋ����ǶȺʹ�С�Ľ��
	drawKeypoints(img, Keypoints, img, Scalar(255, 255, 255));
	//���ƺ��нǶȺʹ�С�Ľ��
	drawKeypoints(img, Keypoints, imgAngel, Scalar(255, 255, 255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	//��ʾ���

	imshow("�����ǶȺʹ�С�Ľ��", img);
	imshow("���нǶȺʹ�С�Ľ��", imgAngel);
	waitKey(0);
	return 0;
}