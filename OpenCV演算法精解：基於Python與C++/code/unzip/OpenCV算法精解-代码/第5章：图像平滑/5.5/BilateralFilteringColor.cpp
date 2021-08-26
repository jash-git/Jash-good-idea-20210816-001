#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
#include<iostream>
//���ڿռ�����Ȩ�����ӣ��ͼ����˹����˵Ĺ��̲�ࣩ
Mat getClosenessWeight(float sigma_g, Size winSize)
{
	//���ڵĿ��
	int H = winSize.height;
	int W = winSize.width;
	CV_Assert(H % 2 == 1 && W % 2 == 1);
	//��һ��:����H��W�еľ���
	Mat closenessWeight(winSize, CV_32FC1);
	int cH = (H - 1) / 2;
	int cW = (W - 1) / 2;
	for (int r = 0; r < H; r++)
	{
		for (int c = 0; c < W; c++)
		{
			float norm2 = pow(r - cH, 2.0) + pow(c - cW, 2.0);
			closenessWeight.at<float>(r, c) = exp(-norm2 / (2*pow(sigma_g, 2.0)));
		}
	}
	return closenessWeight;
}
//˫���˲�
// image Ϊ����ĵ�ͨ��ͼ�����
//����ֵΪ������ͼ�����
Mat BilaterFilter(Mat image, Size winSize, float sigma_g, float sigma_d)
{
	CV_Assert(image.channels() == 1);
	int winH = winSize.height;
	int winW = winSize.width;
	//ƽ�����ڵĳ����������
	CV_Assert(winH > 0 && winW > 0);
	CV_Assert(winH % 2 == 1 && winW % 2 == 1);
	//ͼ�����������Ϊ������
	image.convertTo(image, CV_32FC1);
	if (winH == 1 && winW == 1)
		return image;
	int half_winW = (winW - 1) / 2;
	int half_winH = (winH - 1) / 2;
	//�ռ�����Ȩ������
	Mat closenessWeight = getClosenessWeight(sigma_g, winSize);
	//ͼ��ĳ���
	int rows = image.rows;
	int cols = image.cols;
	//˫���˲�������ͼ��
	Mat blfImage = Mat::ones(image.size(), CV_32FC1);
	//��ÿһ�����ص�������к˾��
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			float pixel = image.at<float>(r, c);
			//�жϱ߽�
			int rTop = (r - half_winH) < 0 ? 0 : r - half_winH;
			int rBottom = (r + half_winH) > rows - 1 ? rows - 1 : r + half_winH;
			int cLeft = (c - half_winW) < 0 ? 0 : c - half_winW;
			int cRight = (c + half_winW) > cols - 1 ? cols - 1 : c + half_winW;
			//�����õ�����
			Mat region = image(Rect(Point(cLeft, rTop), Point(cRight + 1, rBottom + 1))).clone();
			//�Ҷ�ֵ�� ֵ�� ����������Ȩ������
			Mat similarityWeight;
			pow(region - pixel, 2.0, similarityWeight);
			exp(-similarityWeight/ (2 * pow(sigma_d, 2.0)), similarityWeight);
			//�ռ�����������Ȩ������
			Rect regionRect = Rect(Point(cLeft - c + half_winW, rTop - r + half_winH), Point(cRight - c + half_winW + 1, rBottom - r + half_winH + 1));
			Mat closenessWeightTemp = closenessWeight(regionRect).clone();
			//����Ȩ�����Ӷ�Ӧλ�����
			Mat weightTemp = closenessWeightTemp.mul(similarityWeight);
			weightTemp = weightTemp / sum(weightTemp)[0];
			//Ȩ�������뵱ǰ�������Ӧλ����ˣ�Ȼ�����
			Mat result = weightTemp.mul(region);
			blfImage.at<float>(r, c) = sum(result)[0];
		}
	}
	return blfImage;
}
//��ɫ˫���˲�
Mat BilaterFilterColor(Mat image, Size winSize, float sigma_g, float sigma_d)
{
	CV_Assert(image.channels() == 3);
	//��������ͨ�������ÿһ��ͨ������˫���˲�
	vector<Mat> img;
	split(image, img);
	//�洢ÿ��ͨ��˫���˲���Ľ��
	vector<Mat> bImg;
	bImg.clear();
	for (int c = 0; c < 3; c++)
	{
		Mat b_img = BilaterFilter(img[c], winSize, sigma_g, sigma_d);
		bImg.push_back(b_img);
	}
	//����ͨ���ϲ�
	Mat bColorImage;
	merge(bImg, bColorImage);
	return bColorImage;
}
int main(int argc, char*argv[])
{
	//����ͼ�����
	Mat image = imread(argv[1], CV_LOAD_IMAGE_COLOR);
	if (!image.data)
	{
		std::cout << "û��ͼƬ" << std::endl;
		return -1;
	}
	imshow("ԭͼ", image);
	//��ɫ˫���˲�
	Mat result = BilaterFilterColor(image, Size(19, 19),25,15);
	result.convertTo(result, CV_8UC3);
	imshow("˫���˲�", result);
	imwrite("bfltResult.jpg", result);
	waitKey(0);
	return 0;
}