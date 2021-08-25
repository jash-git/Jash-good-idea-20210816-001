#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace cv::ml;
using namespace std;

int main(int argc, char** argv) 
{
	Mat img = imread("digits.png");
	Mat gray;
	cvtColor(img, gray, COLOR_BGR2GRAY);

	// �ָ�Ϊ5000��cells
	Mat images = Mat::zeros(5000, 400, CV_8UC1);
	Mat labels = Mat::zeros(5000, 1, CV_8UC1);

	int index = 0;
	Rect numberImg;
	numberImg.x = 0;
	numberImg.height = 1;
	numberImg.width = 400;
	for (int row = 0; row < 50; row++) 
	{
		//��ͼ���зָ��20��20��ͼ����Ϊ��������ͼ��
		int label = row / 5;
		int datay = row * 20;
		for (int col = 0; col < 100; col++) 
		{
			int datax = col * 20;
			Mat number = Mat::zeros(Size(20, 20), CV_8UC1);
			for (int x = 0; x < 20; x++) 
			{
				for (int y = 0; y < 20; y++)
				{
					number.at<uchar>(x, y) = gray.at<uchar>(x + datay, y + datax);
				}
			}
			//����άͼ������ת��������
			Mat row = number.reshape(1, 1);
			cout << "��ȡ��" << index + 1 << "������" << endl;
			numberImg.y = index;
			//��ӵ���������
			row.copyTo(images(numberImg));
			//��¼ÿ��ͼ���Ӧ�����ֱ�ǩ
			labels.at<uchar>(index, 0) = label;
			index++;
		}
	}
	imwrite("�������ݰ������н��.png", images);
            imwrite("��ǩ.png", labels);

	//����ѵ�����ݼ�
	images.convertTo(images, CV_32FC1);
	labels.convertTo(labels, CV_32SC1);
	Ptr<ml::TrainData> tdata = ml::TrainData::create(images, ml::ROW_SAMPLE, labels);

	//����K������
	Ptr<KNearest> knn = KNearest::create();  
	knn->setDefaultK(5);  //ÿ������ó�5������
	knn->setIsClassifier(true);  //���з���
	
	//ѵ������
	knn->train(tdata);
	//����ѵ�����
	knn->save("knn_model.yml");

	//������н����ʾ
	cout << "��ʹ��K�����������ѵ���ͱ���" << endl;

	waitKey(0);
	return true;
}