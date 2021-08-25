#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace cv::ml;
using namespace std;

int main()
{
	system("color F0");
	//���ز�������
	Mat data = imread("�������ݰ������н��.png", IMREAD_ANYDEPTH);
	Mat labels = imread("��ǩ.png", IMREAD_ANYDEPTH);
	data.convertTo(data, CV_32FC1);
	labels.convertTo(labels, CV_32SC1);

	//�������ɭ��RTrees���ͱ���
	Ptr<RTrees> RTmodel = RTrees::create();
	//���õ���ֹͣ����
	RTmodel->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER + TermCriteria::EPS, 100, 0.01));

	//���в�������ȱʡ�Լӿ������ٶȣ����ǻ�Ӱ��׼ȷ��
	//RTmodel->setMaxDepth(10);  //������
	//RTmodel->setMinSampleCount(10);  //������С������
	//RTmodel->setRegressionAccuracy(0);  //�ع��㷨����
	//RTmodel->setUseSurrogates(false);  //�Ƿ�ʹ�ô���
	//RTmodel->setMaxCategories(15);  //��������
	//RTmodel->setPriors(Mat());  //��������
	//RTmodel->setCalculateVarImportance(true);  //�Ƿ���Ҫ����Var
	//RTmodel->setActiveVarCount(4);  //����Var����Ŀ
	
	Ptr<TrainData> trainData = TrainData::create(data, ROW_SAMPLE, labels);
	RTmodel->train(trainData);
	RTmodel->save("RTrees_model.yml");

	//����ԭ���ݽ��в���
	Mat result;
	RTmodel->predict(data, result);
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
	cout << "�������ȷ�ԣ�" << rate << endl;

	Mat testImg1 = imread("handWrite01.png", IMREAD_GRAYSCALE);
	Mat testImg2 = imread("handWrite02.png", IMREAD_GRAYSCALE);
	imshow("testImg1", testImg1);
	imshow("testImg2", testImg2);

	//���ŵ�20��20�ĳߴ�
	resize(testImg1, testImg1, Size(20, 20));
	resize(testImg2, testImg2, Size(20, 20));

	//���������ݰ�Ҫ��洢
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
	RTmodel->predict(testdata, result2);

	//�鿴Ԥ��Ľ��
	for (int i = 0; i< result2.rows; i++)
	{
		int predict = result2.at<float>(i, 0);
		cout << "��" << i + 1 << "ͼ��Ԥ������" << predict
			<< "  ��ʵ�����" << i + 1 << endl;
	}

	waitKey(0);
	return true;
}