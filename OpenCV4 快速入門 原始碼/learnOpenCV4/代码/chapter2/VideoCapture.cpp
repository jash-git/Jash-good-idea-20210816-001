#include <opencv2\opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	system("color F0");  //�������������ɫ
	VideoCapture video("cup.mp4");
	if (video.isOpened())
	{
		cout << "��Ƶ��ͼ��Ŀ��=" << video.get(CAP_PROP_FRAME_WIDTH) << endl;
		cout << "��Ƶ��ͼ��ĸ߶�=" << video.get(CAP_PROP_FRAME_HEIGHT) << endl;
		cout << "��Ƶ֡��=" << video.get(CAP_PROP_FPS) << endl;
		cout << "��Ƶ����֡��=" << video.get(CAP_PROP_FRAME_COUNT);
	}
	else
	{
		cout << "��ȷ����Ƶ�ļ������Ƿ���ȷ" << endl;
		return -1;
	}
	while (1)
	{
		Mat frame;
		video >> frame;
		if (frame.empty())
		{
			break;
		}
		imshow("video", frame);
		waitKey(1000 / video.get(CAP_PROP_FPS));
	}
	waitKey();
	return 0;
}