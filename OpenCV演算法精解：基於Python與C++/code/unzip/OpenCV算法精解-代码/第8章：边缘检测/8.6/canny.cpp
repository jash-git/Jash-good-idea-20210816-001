#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
//�Ǽ���ֵ����
Mat non_maximum_suppression_default(Mat dx, Mat dy)
{	//ʹ��ƽ���Ϳ����ķ�ʽ�����Եǿ��
	Mat edgeMag;
	cv::magnitude(dx, dy, edgeMag);
	//���
	int rows = dx.rows;
	int cols = dy.cols;
	//��Եǿ�ȵķǼ�������
	Mat edgeMag_nonMaxSup = Mat::zeros(dx.size(), dx.type());
	for (int r = 1; r < rows-1; r++)
	{
		for (int c = 1; c < cols-1; c++)
		{
			float x = dx.at<float>(r, c);
			float y = dy.at<float>(r, c);
			//�ݶȷ���
			float angle = atan2f(y, x)/CV_PI*180;
			//��ǰλ�õı�Եǿ��
			float mag = edgeMag.at<float>(r, c);
			// �� / �ҷ���Ƚ�
			if (abs(angle) < 22.5 || abs(angle) > 157.5)
			{
				float left = edgeMag.at<float>(r, c - 1);
				float right = edgeMag.at<float>(r, c + 1);
				if (mag > left && mag > right)
					edgeMag_nonMaxSup.at<float>(r, c) = mag;
			}
			//���� / ���·���Ƚ�
			if ((angle >= 22.5 && angle < 67.5) || (angle < -112.5 && angle >= 157.5))
			{
				float leftTop = edgeMag.at<float>(r - 1, c - 1);
				float rightBottom = edgeMag.at<float>(r + 1, c + 1);
				if (mag > leftTop && mag > rightBottom)
					edgeMag_nonMaxSup.at<float>(r, c) = mag;
			}
			//�� / �·���Ƚ�
			if ((angle >= 67.5 && angle <= 112.5) || (angle >= -112.5 && angle <= -67.5))
			{
				float top = edgeMag.at<float>(r - 1, c);
				float bottom = edgeMag.at<float>(r + 1, c);
				if (mag > top && mag > bottom)
					edgeMag_nonMaxSup.at<float>(r, c) = mag;
			}
			//���� / ���·���
			if ((angle > 112.5 && angle <= 157.5) || (angle > -67.5 && angle <= -22.5))
			{
				float rightTop = edgeMag.at<float>(r - 1, c + 1);
				float leftBottom = edgeMag.at<float>(r + 1, c - 1);
				if (mag > rightTop && mag > leftBottom)
					edgeMag_nonMaxSup.at<float>(r, c) = mag;
			}
		}
	}
	return edgeMag_nonMaxSup;
}
//�Ǽ���ֵ���� �� ��ֵ�Ƚ�
Mat non_maximum_suppression_Inter(Mat dx, Mat dy)
{
	//ʹ��ƽ���Ϳ����ķ�ʽ�����Եǿ��
	Mat edgeMag;
	cv::magnitude(dx, dy, edgeMag);
	//���
	int rows = dx.rows;
	int cols = dy.cols;
	//��Եǿ�ȵķǼ�������
	Mat edgeMag_nonMaxSup = Mat::zeros(dx.size(), dx.type());
	for (int r = 1; r < rows-1; r++)
	{
		for (int c = 1; c < cols-1; c++)
		{
			float x = dx.at<float>(r, c);
			float y = dy.at<float>(r, c);
			if (x == 0 && y == 0)
				continue;
			float angle = atan2f(y, x) / CV_PI * 180;
			//�����ڰ˸������ϵı�Եǿ��
			float leftTop = edgeMag.at<float>(r - 1, c - 1);
			float top = edgeMag.at<float>(r - 1, c);
			float rightBottom = edgeMag.at<float>(r + 1, c + 1);
			float right = edgeMag.at<float>(r, c+1);
			float rightTop = edgeMag.at<float>(r - 1, c + 1);
			float leftBottom = edgeMag.at<float>(r + 1, c - 1);
			float bottom = edgeMag.at<float>(r + 1, c);
			float left = edgeMag.at<float>(r, c - 1);
			float mag = edgeMag.at<float>(r, c);
			//���Ϸ����Ϸ��Ĳ�ֵ ���·����·��Ĳ�ֵ
			if ((angle > 45 && angle <= 90) || (angle > -135 && angle <= -90))
			{
				float ratio = x / y;
				float top = edgeMag.at<float>(r - 1, c);
				//��ֵ
				float leftTop_top = ratio*leftTop + (1 - ratio)*top;
				float rightBottom_bottom = ratio*rightBottom + (1 - ratio)*bottom;
				if (mag > leftTop_top && mag > rightBottom_bottom)
					edgeMag_nonMaxSup.at<float>(r, c) = mag;
			}
			//���Ϸ����Ϸ��Ĳ�ֵ ���·����·��Ĳ�ֵ
			if ((angle > 90 && angle <= 135) || (angle > -90 && angle <= -45))
			{
				float ratio = abs(x / y);
				float rightTop_top = ratio*rightTop + (1 - ratio)*top;
				float leftBottom_bottom = ratio*leftBottom + (1 - ratio)*bottom;
				if (mag > rightTop_top && mag > leftBottom_bottom)
					edgeMag_nonMaxSup.at<float>(r, c) = mag;
			}
			//���Ϸ����󷽵Ĳ�ֵ ���·����ҷ��Ĳ�ֵ
			if ((angle >= 0 && angle <= 45) || (angle > -180 && angle <= -135))
			{
				float ratio = y / x;
				float rightBottom_right = ratio*rightBottom + (1 - ratio)*right;
				float leftTop_left = ratio*leftTop + (1 - ratio)*left;
				if (mag > rightBottom_right && mag > leftTop_left)
					edgeMag_nonMaxSup.at<float>(r, c) = mag;
			}
			//���Ϸ����ҷ��Ĳ�ֵ ���·����󷽵Ĳ�ֵ
			if ((angle > 135 && angle <= 180) || (angle > -45 && angle <= 0))
			{
				float ratio = abs(y / x);
				float rightTop_right = ratio*rightTop + (1 - ratio)*right;
				float leftBottom_left = ratio*leftBottom + (1 - ratio)*left;
				if (mag > rightTop_right && mag > leftBottom_left)
					edgeMag_nonMaxSup.at<float>(r, c) = mag;
			}
		}
	}
	return edgeMag_nonMaxSup;
}
//ȷ��һ����������Ƿ���ͼ��Χ��
bool checkInRange(int r, int c, int rows, int cols)
{
	if (r >= 0 && r < rows && c>=0 && c < cols)
		return true;
	else
		return false;
}
//��ȷ����Ե��������ӳ���Ե
void trace(Mat edgeMag_nonMaxSup, Mat &edge, float lowerThresh, int r, int c, int rows,int cols)
{
	if (edge.at<uchar>(r, c) == 0)
	{
		edge.at<uchar>(r, c) = 255;
		for (int i = -1; i <= 1; i++)
		{
			for (int j = -1; j <= 1; j++)
			{
				float mag = edgeMag_nonMaxSup.at<float>(r+i, c+j);
				if (checkInRange(r + i, c + j, rows, cols) && mag >= lowerThresh)
					trace(edgeMag_nonMaxSup, edge, lowerThresh, r+i, c+j, rows, cols);
			}
		}
	}
}
//˫��ֵ���ͺ���ֵ����
Mat hysteresisThreshold(Mat edgeMag_nonMaxSup, float lowerThresh, float upperThresh)
{	
	//���
	int rows = edgeMag_nonMaxSup.rows;
	int cols = edgeMag_nonMaxSup.cols;
	//���ı�Ե���ͼ
	Mat edge = Mat::zeros(Size(cols, rows), CV_8UC1);
	//�ͺ���ֵ����
	for (int r = 1; r < rows - 1; r++)
	{
		for (int c = 1; c < cols-1; c++)
		{
			float mag = edgeMag_nonMaxSup.at<float>(r, c);
			//���ڸ���ֵ������Ϊȷ����Ե�㱻����
			//���Ըõ�λ��ʼ���ӳ���Ե
			if(mag>=upperThresh)
				trace(edgeMag_nonMaxSup, edge, lowerThresh, r, c, rows, cols);
			//С�ڵ���ֵ��ֱ�ӱ��޳�
			if (mag < lowerThresh)
				edge.at<uchar>(r, c) = 0;
		}
	}
	return  edge;
}
int main(int argc,char*argv[])
{
	//����ͼ��
	Mat image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if (!image.data)
		return -1;
	//��һ����sobel ������������ OpenCV ��װ�� Sobel ����
	Mat dx, dy;
	cv::Sobel(image, dx, CV_32FC1, 1, 0, 3);
	cv::Sobel(image, dy, CV_32FC1, 0, 1, 3);
	//��Եǿ�ȵĻҶȼ���ʾ
	Mat edgeMag;
	cv::magnitude(dx, dy, edgeMag);
	Mat mag;
	edgeMag.convertTo(mag, CV_8UC1);
	cv::imshow("��Եǿ�ȵĻҶȼ���ʾ", mag);
	cv::imwrite("mag.jpg", mag);
	//�ڶ������Ǽ���ֵ����
	Mat edgeMag_nonMaxSup = non_maximum_suppression_default(dx, dy);
	//��ʾ�Ǽ���ֵ���ƺ�ı�Եǿ��ͼ
	Mat nonMaxSup;
	edgeMag_nonMaxSup.convertTo(nonMaxSup, CV_8UC1);
	cv::imshow("�Ǽ���ֵ����", nonMaxSup);
	cv::imwrite("nonMaxSup.jpg", nonMaxSup);
	//��������˫��ֵ���ͺ���ֵ����
	float lowerThresh = 40;
	float upperThresh = 150;
	Mat edge = hysteresisThreshold(edgeMag_nonMaxSup, lowerThresh, upperThresh);
	imshow("CannyEdge", edge);
	cv::imwrite("CannyEdge.jpg", edge);
	//�뵥��ֵ������бȽ�
	Mat lowerThreshEdge;
	cv::threshold(edgeMag_nonMaxSup, lowerThreshEdge, lowerThresh, 255, CV_THRESH_BINARY);
	cv::convertScaleAbs(lowerThreshEdge, lowerThreshEdge, 1.0, 0);
	cv::imshow("����ֵ������Ч��", lowerThreshEdge);
	cv::imwrite("lowerThreshEdge.jpg", lowerThreshEdge);
	Mat upperThreshEdge;
	cv::threshold(edgeMag_nonMaxSup, upperThreshEdge, upperThresh, 255, CV_THRESH_BINARY);
	cv::convertScaleAbs(upperThreshEdge, upperThreshEdge, 1.0, 0.0);
	cv::imshow("����ֵ������Ч��", upperThreshEdge);
	cv::imwrite("upperThreshEdge.jpg", upperThreshEdge);
	waitKey(0);
	return 0;
}