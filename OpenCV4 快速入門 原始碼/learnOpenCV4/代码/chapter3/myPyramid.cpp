#include <opencv2\opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat img = imread("lena.png");
	if (img.empty())	{		cout << "��ȷ��ͼ���ļ������Ƿ���ȷ" << endl;		return -1;	}
	vector<Mat> Gauss, Lap;  //��˹��������������˹������
	int level = 3;  //��˹�������²�������
	Gauss.push_back(img);  //��ԭͼ��Ϊ��˹�������ĵ�0��
						   //������˹������
	for (int i = 0; i < level; i++)
	{
		Mat gauss;
		pyrDown(Gauss[i], gauss);  //�²���
		Gauss.push_back(gauss);
	}
	//����������˹������
	for (int i = Gauss.size() - 1; i > 0; i--)
	{
		Mat lap, upGauss;
		if (i == Gauss.size() - 1)  //����Ǹ�˹�������е�������һ��ͼ��
		{
			Mat down;
			pyrDown(Gauss[i], down);  //�ϲ���
			pyrUp(down, upGauss);
			lap = Gauss[i] - upGauss;
			Lap.push_back(lap);
		}
		pyrUp(Gauss[i], upGauss);
		lap = Gauss[i - 1] - upGauss;
		Lap.push_back(lap);
	}
	//�鿴�����������е�ͼ��
	for (int i = 0; i < Gauss.size(); i++)
	{
		string name = to_string(i);
		imshow("G" + name, Gauss[i]);
		imshow("L" + name, Lap[i]);
	}
	waitKey(0);
	return 0;
}
