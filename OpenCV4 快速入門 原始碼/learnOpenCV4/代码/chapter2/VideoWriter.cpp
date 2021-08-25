#include <opencv2\opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat img;
	VideoCapture video(0);  //ʹ��ĳ������ͷ

	//��ȡ��Ƶ
	//VideoCapture video;
	//video.open("cup.mp4");  

	if (!video.isOpened())  // �ж��Ƿ���óɹ�
	{
		cout << "������ͷʧ�ܣ���ȷʵ����ͷ�Ƿ�װ�ɹ�";
		return -1;
	}

	video >> img;  //��ȡͼ��
	//����Ƿ�ɹ���ȡͼ��
	if (img.empty())   //�ж���û�ж�ȡͼ��ɹ�
	{
		cout << "û�л�ȡ��ͼ��" << endl;
		return -1;
	}
	bool isColor = (img.type() == CV_8UC3);  //�ж��������Ƶ�������Ƿ�Ϊ��ɫ

	VideoWriter writer;
	int codec = VideoWriter::fourcc('M', 'J', 'P', 'G');  // ѡ������ʽ
	//OpenCV 4.0�汾���ñ����ʽ
	//int codec = CV_FOURCC('M', 'J', 'P', 'G'); 

	double fps = 25.0;  //������Ƶ֡�� 
	string filename = "live.avi";  //�������Ƶ�ļ�����
	writer.open(filename, codec, fps, img.size(), isColor);  //����������Ƶ�ļ�����Ƶ��

	if (!writer.isOpened())   //�ж���Ƶ���Ƿ񴴽��ɹ�
	{
		cout << "����Ƶ�ļ�ʧ�ܣ���ȷʵ�Ƿ�Ϊ�Ϸ�����" << endl;
		return -1;
	}

	while (1)
	{
		//����Ƿ�ִ�����
		if (!video.read(img))   //�ж��ܶ�����������ͷ������Ƶ�ļ��ж���һ֡ͼ��
		{
			cout << "����ͷ�Ͽ����ӻ�����Ƶ��ȡ���" << endl;
			break;
		}
		writer.write(img);  //��ͼ��д����Ƶ��
		//writer << img;
		imshow("Live", img);  //��ʾͼ��
		char c = waitKey(50);
		if (c == 27)  //��ESC�����˳���Ƶ����
		{
			break;
		}
	}
	// �˳�����ʱ���Զ��ر���Ƶ��
	//video.release();
	//writer.release();	
	return 0;
}