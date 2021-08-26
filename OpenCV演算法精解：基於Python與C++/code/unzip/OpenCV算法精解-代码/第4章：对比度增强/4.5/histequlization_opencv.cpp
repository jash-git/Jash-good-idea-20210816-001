#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
#include<iostream>
using namespace std;
int main(int argc, char*argv[])
{
	//����ͼƬ
	Mat image = imread(argv[1],CV_LOAD_IMAGE_COLOR);
	if (!image.data)
	{
		cout << "û��ͼƬ" << endl;
		return -1;
	}
	//��ʾԭͼ
	imshow("image", image);
	//ֱ��ͼ���⻯���ͼƬ
	Mat eqHistImage;
	equalizeHist(image, eqHistImage);
	imshow("ֱ��ͼ���⻯", eqHistImage);
	waitKey(0);
	return 0;
}