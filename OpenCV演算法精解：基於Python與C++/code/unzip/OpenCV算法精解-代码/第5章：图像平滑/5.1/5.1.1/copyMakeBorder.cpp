#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;

int main(int argc, char*argv[])
{
	//����ͼ��
	Mat img = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	//��ʾԭͼ
	imshow("img", img);
	Mat result;
	//�߽�����
	copyMakeBorder(img, result, 50, 50, 50, 50, BORDER_CONSTANT,Scalar(0));
	//��ʾ�߽�����Ľ��
	imshow("result", result);
	//����ͼƬ
	//imwrite("result.jpg", result);
	waitKey(0);
	return 0;
}