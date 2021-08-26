#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
using namespace cv;
int main(int argc, char*argv[])
{
	//����ͼ��
	Mat src = imread(argv[1], IMREAD_GRAYSCALE);
	if (!src.data)
		return -1;
	//���� CLAHE ����
	Ptr<CLAHE> clahe =  createCLAHE(2, Size(8, 8));
	Mat dst;
	//���ƶԱȶȵ�����Ӧֱ��ͼ���⻯
	clahe->apply(src, dst);
	//��ʾԭͼ�����⻯���Ч��
	imshow("ԭͼ", src);
	imshow("�Աȶ���ǿ", dst);
	imwrite("clahe.jpg", dst);
	waitKey(0);
	return 0;
}