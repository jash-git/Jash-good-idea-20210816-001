#include <opencv2\opencv.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

int main()
{
	system("color F0");  //�������������ɫ
	Vec4f lines;  //�����ͺ��ֱ��
	vector<Point2f> point;  //������Ƿ����ֱ�ߵ����е�
	const static float Points[20][2] = {
		{ 0.0f,   0.0f },{ 10.0f,  11.0f },{ 21.0f,  20.0f },{ 30.0f,  30.0f },
		{ 40.0f,  42.0f },{ 50.0f,  50.0f },{ 60.0f,  60.0f },{ 70.0f,  70.0f },
		{ 80.0f,  80.0f },{ 90.0f,  92.0f },{ 100.0f, 100.0f },{ 110.0f, 110.0f },
		{ 120.0f, 120.0f },{ 136.0f, 130.0f },{ 138.0f, 140.0f },{ 150.0f, 150.0f },
		{ 160.0f, 163.0f },{ 175.0f, 170.0f },{ 181.0f, 180.0f },{ 200.0f, 190.0f }
	};
	//�����е�����vector�У��������뺯����
	for (int i = 0; i < 20; i++)
	{
		point.push_back(Point2f(Points[i][0], Points[i][1]));
	}
	//��������
	double param = 0;  //����ģ���е���ֵ����C
	double reps = 0.01;  //����ԭ����ֱ��֮��ľ��뾫��
	double aeps = 0.01;  //�ǶȾ���
	fitLine(point, lines, DIST_L1, 0, 0.01, 0.01);
	double k = lines[1] / lines[0];  //ֱ��б��
	cout << "ֱ��б�ʣ�" << k << endl;
	cout << "ֱ����һ������x��" << lines[2] << ", y::" << lines[3] << endl;
	cout << "ֱ�߽���ʽ��y=" << k << "(x-" << lines[2] << ")+" << lines[3] << endl;
	return 0;
}