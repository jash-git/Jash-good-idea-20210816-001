#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;

int main(int argc, char*argv[])
{
	//输入图像
	Mat img = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	//显示原图
	imshow("img", img);
	Mat result;
	//边界扩充
	copyMakeBorder(img, result, 50, 50, 50, 50, BORDER_CONSTANT,Scalar(0));
	//显示边界扩充的结果
	imshow("result", result);
	//保存图片
	//imwrite("result.jpg", result);
	waitKey(0);
	return 0;
}