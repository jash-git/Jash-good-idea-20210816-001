#include <opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

int main() 
{
	//������Ƶ�ļ������ж��Ƿ���سɹ�
	VideoCapture capture("bike.avi");
	if (!capture.isOpened()) {
		cout<<"��ȷ����Ƶ�ļ��Ƿ���ȷ"<<endl;
		return -1;
	}

	//�����Ƶ�����Ϣ
	int fps = capture.get(CAP_PROP_FPS);
	int width = capture.get(CAP_PROP_FRAME_WIDTH);
	int height = capture.get(CAP_PROP_FRAME_HEIGHT);
	int num_of_frames = capture.get(CAP_PROP_FRAME_COUNT);
	cout << "��Ƶ��ȣ�" << width << " ��Ƶ�߶ȣ�" << height << " ��Ƶ֡�ʣ�" << fps << " ��Ƶ��֡��" << num_of_frames << endl;

	//��ȡ��Ƶ�е�һ֡ͼ����Ϊǰһ֡ͼ�񣬲����лҶȻ�
	Mat preFrame, preGray;
	capture.read(preFrame);
	cvtColor(preFrame, preGray, COLOR_BGR2GRAY);
	//��ͼ����и�˹�˲���������������
	GaussianBlur(preGray, preGray, Size(0, 0), 15);

	Mat binary;
	Mat frame, gray;
	//��̬ѧ�����ľ���ģ��
	Mat k = getStructuringElement(MORPH_RECT, Size(7, 7), Point(-1, -1));

	while (true) 
	{
		//��Ƶ������ͼ��������Ƴ�ѭ��
		if (!capture.read(frame))
		{
			break;
		}

		//�Ե�ǰ֡���лҶȻ�
		cvtColor(frame, gray, COLOR_BGR2GRAY);
		GaussianBlur(gray, gray, Size(0, 0), 15);

		//���㵱ǰ֡��ǰһ֡�Ĳ�ֵ�ľ���ֵ
		absdiff(gray, preGray, binary);
		
		//�Լ�������ֵ�������п����㣬���������ĸ���
		threshold(binary, binary, 10, 255, THRESH_BINARY | THRESH_OTSU);
		morphologyEx(binary, binary, MORPH_OPEN, k);

		//��ʾ������
		imshow("input", frame);
		imshow("result", binary);
		
		//����ǰ֡���ǰһ֡��׼����һ��ѭ����ע�͵���仰Ϊ�̶�����
		//gray.copyTo(preGray);

		//5������ʱ�ж��Ƿ��Ƴ����򣬰�ESC���˳�
		char c = waitKey(5);
		if (c == 27) 
		{
			break;
		}
	}

	waitKey(0);
	return 0;
}