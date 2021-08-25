#include <opencv2\opencv.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

void orb_features(Mat &gray, vector<KeyPoint> &keypionts, Mat &descriptions)
{
	Ptr<ORB> orb = ORB::create(1000, 1.2f);
	orb->detect(gray, keypionts);
	orb->compute(gray, keypionts, descriptions);
}

int main()
{
	Mat img1, img2;
	img1 = imread("box.png");
	img2 = imread("box_in_scene.png");

	if (!(img1.data && img2.dataend))
	{
		cout << "��ȡͼ�������ȷ��ͼ���ļ��Ƿ���ȷ" << endl;
		return -1;
	}

	//��ȡORB������
	vector<KeyPoint> Keypoints1, Keypoints2;
	Mat descriptions1, descriptions2;

	//����SURF������
	orb_features(img1, Keypoints1, descriptions1);
	orb_features(img2, Keypoints2, descriptions2);

	//�ж��������������ͣ�����������Ͳ�����Ҫ��������ת������Ҫ���ORB������
	if ((descriptions1.type() != CV_32F) && (descriptions2.type() != CV_32F))
	{
		descriptions1.convertTo(descriptions1, CV_32F);
		descriptions2.convertTo(descriptions2, CV_32F);
	}

	//������ƥ��
	vector<DMatch> matches;  //������ƥ�����ı���
	FlannBasedMatcher matcher;  //ʹ��Ĭ��ֵ����
	matcher.match(descriptions1, descriptions2, matches);
	cout << "matches=" << matches.size() << endl;  //ƥ��ɹ���������Ŀ


												   //Ѱ�Ҿ������ֵ����Сֵ�������ORB������min_distȡֵ��Ҫ��һЩ
	double max_dist = 0; double min_dist = 100;
	for (int i = 0; i < descriptions1.rows; i++)
	{
		double dist = matches[i].distance;
		if (dist < min_dist) min_dist = dist;
		if (dist > max_dist) max_dist = dist;
	}
	cout << " Max dist :" << max_dist << endl;
	cout << " Min dist :" << min_dist << endl;

	//�����ֵ�����0.4����Ϊ����ƥ��������ɸѡ
	std::vector< DMatch > good_matches;
	for (int i = 0; i < descriptions1.rows; i++)
	{
		if (matches[i].distance < 0.40 * max_dist)
		{
			good_matches.push_back(matches[i]);
		}
	}
	cout << "good_matches=" << good_matches.size() << endl;  //ƥ��ɹ���������Ŀ

															 //����ƥ����
	Mat outimg, outimg1;
	drawMatches(img1, Keypoints1, img2, Keypoints2, matches, outimg);
	drawMatches(img1, Keypoints1, img2, Keypoints2, good_matches, outimg1);
	imshow("δɸѡ���", outimg);
	imshow("ɸѡ���", outimg1);

	waitKey(0);
	return 0;
}