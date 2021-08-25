#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) 
{
	VideoCapture capture("vtest.avi");
	Mat prevFrame, prevGray;
	if (!capture.read(prevFrame))
	{
		cout << "��ȷ����Ƶ�ļ������Ƿ���ȷ" << endl;
		return -1;
	}

	//����ɫͼ��ת���ɻҶ�ͼ��
	cvtColor(prevFrame, prevGray, COLOR_BGR2GRAY);
	
	while (true) 
	{	
		Mat nextFrame, nextGray;
		//����ͼ������ɺ��Ƴ�����
		if (!capture.read(nextFrame))
		{
			break;
		}
		imshow("��Ƶͼ��", nextFrame);

		//������ܹ���
		cvtColor(nextFrame, nextGray, COLOR_BGR2GRAY);
		Mat_<Point2f> flow;  //����������˶��ٶ�
		calcOpticalFlowFarneback(prevGray, nextGray, flow, 0.5, 3, 15, 3, 5, 1.2, 0);
	
		Mat xV = Mat::zeros(prevFrame.size(), CV_32FC1);  //x�����ƶ��ٶ�
		Mat yV = Mat::zeros(prevFrame.size(), CV_32FC1);  //y�����ƶ��ٶ�
		//��ȡ����������ٶ�
		for (int row = 0; row < flow.rows; row++)
		{
			for (int col = 0; col < flow.cols; col++)
			{
				const Point2f& flow_xy = flow.at<Point2f>(row, col);
				xV.at<float>(row, col) = flow_xy.x;
				yV.at<float>(row, col) = flow_xy.y;
			}
		}
		
		//���������ǶȺͷ�ֵ
		Mat magnitude, angle;
		cartToPolar(xV, yV, magnitude, angle);

		//���Ƕ�ת���ɽǶ���
		angle = angle * 180.0 / CV_PI / 2.0;

		//�ѷ�ֵ��һ����0-255���������ʾ���
		normalize(magnitude, magnitude, 0, 255, NORM_MINMAX);

		//����ǶȺͷ�ֵ�ľ���ֵ
		convertScaleAbs(magnitude, magnitude);
		convertScaleAbs(angle, angle);

		//���˶��ķ�ֵ�ͽǶ�����HSV��ɫ�ռ��ͼ��
		Mat HSV = Mat::zeros(prevFrame.size(), prevFrame.type());
		vector<Mat> result;
		split(HSV, result);
		result[0] = angle;  //������ɫ
		result[1] = Scalar(255);
		result[2] = magnitude;  //������̬
		//��������ͨ��ͼ��ϲ�����ͨ��ͼ��
		merge(result, HSV);
		
		//��HSV��ɫ�ռ�ͼ��ת����RGB��ɫ�ռ���
		Mat rgbImg;
		cvtColor(HSV, rgbImg, COLOR_HSV2BGR);
		
		//��ʾ�����
		imshow("�˶������", rgbImg);
		int ch = waitKey(5);
		if (ch == 27) 
		{
			break;
		}
	}
	waitKey(0);
	return 0;
}