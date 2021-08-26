#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
int main(int argc, char* argv[])
{
	//����ͼ��
	Mat I = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if (!I.data)
		return -1;
	/*��һ�ַ�ʽ������ warpAffine ��������*/
	//���ŷ�����󣬵ȱ�����С2��
	Mat s = (Mat_<float>(2, 3) << 0.5, 0, 0, 0, 0.5, 0);
	Mat dst1;
	warpAffine(I, dst1,s,Size(I.cols/2,I.rows/2));//ͼ������
	/*�ڶ��ַ�ʽ������ resize �ȱ�����С����*/
	Mat dst2;
	resize(I, dst2, Size(I.cols / 2, I.rows / 2), 0.5, 0.5);
	imshow("I", I);
	imshow("warpAffine", dst1);
	imshow("resize", dst2);
	waitKey(0);
	return 0;
}