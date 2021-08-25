#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace cv::dnn;
using namespace std;

int main()
{
	system("color F0");
	string model = "bvlc_googlenet.caffemodel";
	string config = "bvlc_googlenet.prototxt";

	//����ģ��
	Net net = dnn::readNet(model, config);
	if (net.empty())
	{
		cout << "��ȷ���Ƿ�����յ�ģ���ļ�" << endl;
		return -1;
	}

	// ��ȡ������Ϣ
	vector<String> layerNames = net.getLayerNames();
	for (int i = 0; i < layerNames.size(); i++)
	{
		//��ȡÿ�������ID
		int ID = net.getLayerId(layerNames[i]);
		//��ȡÿ���������Ϣ
		Ptr<Layer> layer = net.getLayer(ID);
		//���������Ϣ
		cout << "���������" << ID << "  ��������ƣ�" << layerNames[i] << endl
			<< "��������ͣ�" << layer->type.c_str() << endl;
	}
	return 0;
}
