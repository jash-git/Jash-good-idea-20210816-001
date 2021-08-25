#include <opencv2\opencv.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

int main()
{
	//��ͼ����о���任
	Mat img = imread("rice.png");
	if (img.empty())	{		cout << "��ȷ��ͼ���ļ������Ƿ���ȷ" << endl;		return -1;	}
	Mat rice, riceBW;

	//��ͼ��ת�ɶ�ֵͼ������ͳ����ͨ��
	cvtColor(img, rice, COLOR_BGR2GRAY);
	threshold(rice, riceBW, 50, 255, THRESH_BINARY);

	//���������ɫ���������ֲ�ͬ��ͨ��
	RNG rng(10086);
	Mat out;
	int number = connectedComponents(riceBW, out, 8, CV_16U);  //ͳ��ͼ������ͨ��ĸ���
	vector<Vec3b> colors;
	for (int i = 0; i < number; i++)
	{
		//ʹ�þ��ȷֲ��������ȷ����ɫ
		Vec3b vec3 = Vec3b(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
		colors.push_back(vec3);
	}

	//�Բ�ͬ��ɫ��ǳ���ͬ����ͨ��
	Mat result = Mat::zeros(rice.size(), img.type());
	int w = result.cols;
	int h = result.rows;
	for (int row = 0; row < h; row++)
	{
		for (int col = 0; col < w; col++)
		{
			int label = out.at<uint16_t>(row, col);
			if (label == 0)  //�����ĺ�ɫ���ı�
			{
				continue;
			}
			result.at<Vec3b>(row, col) = colors[label];
		}
	}

	//��ʾ���
	imshow("ԭͼ", img);
	imshow("��Ǻ��ͼ��", result);

	waitKey(0);
	return 0;
}
