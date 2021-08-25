#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	system("color F0");  //�޸����г��򱳾���������ɫ
	//string fileName = "datas.xml";  //�ļ�������
	string fileName = "datas.yaml";  //�ļ�������
	//��д���ģʽ���ļ�
	cv::FileStorage fwrite(fileName, cv::FileStorage::WRITE);
	
	//�������Mat���͵�����
	Mat mat = Mat::eye(3, 3, CV_8U);
	fwrite.write("mat", mat);  //ʹ��write()����д������
	//���븡�������ݣ��ڵ�����Ϊx
	float x = 100;
	fwrite << "x" << x;
	//�����ַ��������ݣ��ڵ�����Ϊstr
	String str = "Learn OpenCV 4";
	fwrite << "str" << str;
	//��������,�ڵ�����Ϊnumber_array
	fwrite << "number_array" << "[" <<4<<5<<6<< "]";
	//�����node�ڵ�����,������Ϊmulti_nodes
	fwrite << "multi_nodes" << "{" << "month" << 8 << "day" << 28 << "year"
		<< 2019 << "time" << "[" << 0 << 1 << 2 << 3 << "]" << "}";

	//�ر��ļ�
	fwrite.release();

	//�Զ�ȡ��ģʽ���ļ�
	cv::FileStorage fread(fileName, cv::FileStorage::READ);
	//�ж��Ƿ�ɹ����ļ�
	if (!fread.isOpened())
	{
		cout << "���ļ�ʧ�ܣ���ȷ���ļ������Ƿ���ȷ��" << endl;
		return -1;
	}

	//��ȡ�ļ��е�����
	float xRead;
	fread["x"] >> xRead;  //��ȡ����������
	cout << "x=" << xRead << endl;

	//��ȡ�ַ�������
	string strRead;
	fread["str"] >> strRead;
	cout << "str=" << strRead << endl;

	//��ȡ��������ݵ�number_array�ڵ�
	FileNode fileNode = fread["number_array"];
	cout << "number_array=[";
	//ѭ������ÿ������
	for (FileNodeIterator i = fileNode.begin(); i != fileNode.end(); i++)
	{
		float a;
		*i >> a;
		cout << a<<" ";
	}
	cout << "]" << endl;

	//��ȡMat��������
	Mat matRead;
	fread["mat="] >> matRead;
	cout << "mat=" << mat << endl;

	//��ȡ���ж���ӽڵ�Ľڵ����ݣ���ʹ��FileNode�͵��������ж�ȡ
	FileNode fileNode1 = fread["multi_nodes"];
	int month = (int)fileNode1["month"];
	int day = (int)fileNode1["day"];
	int year = (int)fileNode1["year"];
	cout << "multi_nodes:" << endl 
		<< "  month=" << month << "  day=" << day << "  year=" << year;
	cout << "  time=[";
	for (int i = 0; i < 4; i++)
	{
		int a = (int)fileNode1["time"][i];
		cout << a << " ";
	}
	cout << "]" << endl;
	
	//�ر��ļ�
	fread.release();
	return 0;
}
