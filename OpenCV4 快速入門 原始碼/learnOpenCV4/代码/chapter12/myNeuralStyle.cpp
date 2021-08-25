#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace cv::dnn;
using namespace std;

int main()
{
	Mat image = imread("lena.png");
	String models[5] = { "the_wave.t7",	"mosaic.t7", "feathers.t7", "candy.t7", "udnie.t7" };
	for (int i = 0; i < size(models); i++)
	{
		Net net = readNet(models[i]);
		imshow("ԭʼͼ��", image);
		//����ͼ��ÿ��ͨ���ľ�ֵ
		Scalar imgaeMean = mean(image);
		//����ͼ��ߴ�͸�ʽ
		Mat blobImage = blobFromImage(image, 1.0, Size(256, 256), imgaeMean, false, false);

		//���������ԭͼ������
		net.setInput(blobImage);
		Mat output = net.forward();

		//�������ĳߴ��ͨ����
		int outputChannels = output.size[1];
		int outputRows = output.size[2];
		int outputCols = output.size[3];

		//����������ŵ�ͼ����
		Mat result = Mat::zeros(Size(outputCols, outputRows), CV_32FC3);
		float* data = output.ptr<float>();
		for (int channel = 0; channel < outputChannels; channel++)
		{
			for (int row = 0; row < outputRows; row++)
			{
				for (int col = 0; col < outputCols; col++)
				{
					result.at<Vec3f>(row, col)[channel] = *data++;
				}
			}
		}

		//��Ǩ�ƽ�����н�һ����������
		//�ָ�ͼ������ľ�ֵ
		result = result + imgaeMean;
		//��ͼ����й�һ��������ͼ����ʾ
		result = result / 255.0;
		//����ͼ��ߴ磬ʹ����ԭͼ��ߴ���ͬ
		resize(result, result, image.size());
		//��ʾ���
		imshow("��"+to_string(i)+"�ַ��Ǩ�ƽ��", result);
	}

	waitKey(0);
	return 0;
}