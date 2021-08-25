#include <opencv2/opencv.hpp>
#include <iostream>  

using namespace std;
using namespace cv;
using namespace cv::ml;

int main()
{
	//ѵ������
	Mat samples, labls;
	FileStorage fread("point.yml", FileStorage::READ);
	fread["data"] >> samples;
	fread["labls"] >> labls;
	fread.release();

	//��ͬ���������ӵ�в�ͬ����ɫ
	vector<Vec3b> colors;
	colors.push_back(Vec3b(0, 255, 0));
	colors.push_back(Vec3b(0, 0, 255));

	//�����հ�ͼ��������ʾ�����
	Mat img(480, 640, CV_8UC3, Scalar(255, 255, 255));
	Mat img2;
	img.copyTo(img2);

	//�ڿհ�ͼ���л��������
	for (int i = 0; i < samples.rows; i++)
	{
		Point2f point;
		point.x = samples.at<float>(i, 0);
		point.y = samples.at<float>(i, 1);
		Scalar color = colors[labls.at<int>(i, 0)];
		circle(img, point, 3, color, -1);
		circle(img2, point, 3, color, -1);
	}
	imshow("�������ص�ͼ��", img);

	//����ģ��
	Ptr<SVM> model = SVM::create();
	
	//��������
	model->setKernel(SVM::INTER);  //�ں˵�ģ��
	model->setType(SVM::C_SVC);  //SVM������
	model->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER + TermCriteria::EPS, 100, 0.01));
	//model->setGamma(5.383);
	//model->setC(0.01);
	//model->setDegree(3);
	
	//ѵ��ģ��
	model->train(TrainData::create(samples, ROW_SAMPLE, labls));

	//��ģ�Ͷ�ͼ����ȫ�����ص���з���
	Mat imagePoint(1, 2, CV_32FC1);
	for (int y = 0; y < img2.rows; y = y + 2)
	{
		for (int x = 0; x < img2.cols; x = x + 2)
		{
			imagePoint.at<float>(0) = (float)x;
			imagePoint.at<float>(1) = (float)y;
			int color = (int)model->predict(imagePoint);
			img2.at<Vec3b>(y, x) = colors[color];
		}
	}

	imshow("ͼ���������ص������", img2);
	waitKey();
	return 0;
}