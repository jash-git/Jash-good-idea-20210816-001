#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace cv::ml;
using namespace std;

int main()
{
	system("color F0");
	// ����KNN������
	Mat data = imread("�������ݰ������н��.png", IMREAD_ANYDEPTH);
	Mat labels = imread("��ǩ.png", IMREAD_ANYDEPTH);
	data.convertTo(data, CV_32FC1);
	labels.convertTo(labels, CV_32SC1);
	Ptr<KNearest> knn = Algorithm::load<KNearest>("knn_model.yml");
	
	//�鿴������
	Mat result;
	knn->findNearest(data, 5, result);

	//ͳ�Ʒ���������ʵ�����ͬ����Ŀ
	int count = 0;
	for (int row = 0; row < result.rows; row++)
	{

		int predict = result.at<float>(row, 0);
		if (labels.at<int>(row, 0) == predict)
		{
			count = count + 1;
		}
	}
	float rate = 1.0*count / result.rows;
	cout << "�������ȷ�ԣ�" <<rate<< endl;

	//������ͼ���Ƿ��ܹ�ʶ������
	Mat testImg1 = imread("handWrite01.png", IMREAD_GRAYSCALE);
	Mat testImg2 = imread("handWrite02.png", IMREAD_GRAYSCALE);
	imshow("testImg1", testImg1);
	imshow("testImg2", testImg2);

	//���ŵ�20��20�ĳߴ�
	resize(testImg1, testImg1, Size(20, 20));
	resize(testImg2, testImg2, Size(20, 20));
	Mat testdata = Mat::zeros(2, 400, CV_8UC1);
	Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.height = 1;
	rect.width = 400;
	Mat oneDate = testImg1.reshape(1, 1);
	Mat twoData = testImg2.reshape(1, 1);
	oneDate.copyTo(testdata(rect));
	rect.y = 1;
	twoData.copyTo(testdata(rect));
	//��������ת��
	testdata.convertTo(testdata, CV_32F);

	//���й���ʶ��
	Mat result2;
	knn->findNearest(testdata, 5, result2);

	//�鿴Ԥ��Ľ��
	for (int i = 0; i< result2.rows; i++)
	{
		int predict = result2.at<float>(i, 0);
		cout << "��" << i + 1 << "ͼ��Ԥ������" << predict 
			<< "  ��ʵ�����" << i + 1 << endl;
	}
	waitKey(0);
	return 0;
}