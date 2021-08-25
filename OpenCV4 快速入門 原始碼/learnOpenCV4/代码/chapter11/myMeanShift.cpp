#include <opencv2/opencv.hpp>"
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, const char** argv)
{
	//����Ƶ�ļ������ж��Ƿ�ɹ���
	VideoCapture cap("vtest.avi");
	if (!cap.isOpened())
	{
		cout << "��ȷ���������Ƶ�ļ����Ƿ���ȷ" << endl;
		return -1;
	}

	//�Ƿ��Ѿ�����Ŀ������ֱ��ͼ��־��0��ʾû�м��㣬1��ʾ�Ѿ�����
	int trackObject = 0;  
	
	//����ֱ��ͼ�ͷ���ֱ��ͼ��ز���
	int hsize = 16;
	float hranges[] = { 0,180 };
	const float* phranges = hranges;
	
	//ѡ��Ŀ������
	Mat frame, hsv, hue, hist, histimg = Mat::zeros(200, 320, CV_8UC3), backproj;
	cap.read(frame);
	Rect selection = selectROI("ѡ��Ŀ���������", frame, true, false);
	
	while (true)
	{
		//�ж��Ƿ��ȡ��ȫ��ͼ��
		if (!cap.read(frame))
		{
			break;
		}
		//��ͼ��ת����HSV��ɫ�ռ�
		cvtColor(frame, hsv, COLOR_BGR2HSV);

		//�������ֱ��ͼ�ͷ���ֱ��ͼ������ݺ�ͼ��
		int ch[] = { 0, 0 };
		hue.create(hsv.size(), hsv.depth());
		mixChannels(&hsv, 1, &hue, 1, ch, 1);

		//�Ƿ��Ѿ���ɸ���Ŀ��ֱ��ͼ�ļ���
		if (trackObject <= 0)
		{
			//Ŀ�������HSV��ɫ�ռ�
			Mat roi(hue, selection);
			//����ֱ��ͼ��ֱ��ͼ��һ��
			calcHist(&roi, 1, 0, roi, hist, 1, &hsize, &phranges);
			normalize(hist, hist, 0, 255, NORM_MINMAX);
			
			//����־����Ϊ1�����ټ���Ŀ�������ֱ��ͼ
			trackObject = 1; // Don't set up again, unless user selects new ROI

			//��ʾĿ�������ֱ��ͼ�����Խ�ע�͵�����Ӱ�����Ч��
			histimg = Scalar::all(0);
			int binW = histimg.cols / hsize;
			Mat buf(1, hsize, CV_8UC3);
			for (int i = 0; i < hsize; i++)
				buf.at<Vec3b>(i) = Vec3b(saturate_cast<uchar>(i*180. / hsize), 255, 255);
			cvtColor(buf, buf, COLOR_HSV2BGR);

			for (int i = 0; i < hsize; i++)
			{
				int val = saturate_cast<int>(hist.at<float>(i)*histimg.rows / 255);
				rectangle(histimg, Point(i*binW, histimg.rows),
					Point((i + 1)*binW, histimg.rows - val),
					Scalar(buf.at<Vec3b>(i)), -1, 8);
			}
		}

		// ����Ŀ������ķ���ֱ��ͼ
		calcBackProject(&hue, 1, 0, hist, backproj, &phranges);
		
		//��ֵǨ�Ʒ�����Ŀ��
		meanShift(backproj, selection, TermCriteria(TermCriteria::EPS | TermCriteria::COUNT, 10, 1));
		//��ͼ���л���Ѱ�ҵ��ĸ��ٴ���
		rectangle(frame, selection, Scalar(0, 0, 255), 3, LINE_AA);

		//��ʾ���
		imshow("CamShift Demo", frame);  //��ʾ���ٽ��
		imshow("Histogram", histimg);  //��ʾĿ������ֱ��ͼ

		//��ESC���˳�����
		char c = (char)waitKey(50);
		if (c == 27)
			break;
	}

	return 0;
}