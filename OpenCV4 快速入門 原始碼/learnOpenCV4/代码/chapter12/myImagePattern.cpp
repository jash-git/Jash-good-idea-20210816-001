#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>

using namespace cv;
using namespace cv::dnn;
using namespace std;

int main() 
{
	Mat img = imread("airplane.jpg");
	if (img.empty())
	{
		printf("could not load image...\n");
		return -1;
	}

	//��ȡ������������
	String typeListFile = "imagenet_comp_graph_label_strings.txt";
	vector<String> typeList;
	ifstream file(typeListFile);
	if (!file.is_open())
	{
		printf("��ȷ�Ϸ������������Ƿ���ȷ");
		return -1;
	}
	
	std::string type;
	while (!file.eof())
	{
		//��ȡ����
		getline(file, type);
		if (type.length())
			typeList.push_back(type);
	}
	file.close();

	// ��������
	String tf_pb_file = "tensorflow_inception_graph.pb";
	Net net = readNet(tf_pb_file);
	if (net.empty()) 
	{
		printf("��ȷ��ģ���ļ��Ƿ�Ϊ���ļ�");
		return -1;
	}

	//������ͼ�����ݽ��д���
	Mat blob = blobFromImage(img, 1.0f, Size(224, 224), Scalar(), true, false);

	//����ͼ������Ԥ��
	Mat prob;
	net.setInput(blob, "input");
	prob = net.forward("softmax2");

	// �õ�����ܷ������
	Mat probMat = prob.reshape(1, 1);
	Point classNumber;  
	double classProb;  //��������
	minMaxLoc(probMat, NULL, &classProb, NULL, &classNumber);

	string typeName = typeList.at(classNumber.x).c_str();
	cout << "ͼ�����������Ϊ��" << typeName << "  ������Ϊ��" << classProb;
		
	//�������
	string str = typeName + " possibility:" + to_string(classProb);
	putText(img, str, Point(50, 50), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(0, 0, 255), 2, 8);
	imshow("ͼ���жϽ��", img);
	waitKey(0);
	return 0;
}