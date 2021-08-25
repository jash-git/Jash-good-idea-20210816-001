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

	//����������
	orb_features(img1, Keypoints1, descriptions1);
	orb_features(img2, Keypoints2, descriptions2);

	//������ƥ��
	vector<DMatch> matches;  //������ƥ�����ı���
	BFMatcher matcher(NORM_HAMMING);  //����������ƥ����࣬ʹ�ú�������
	matcher.match(descriptions1, descriptions2, matches);  //����������ƥ��
	cout << "matches=" << matches.size() << endl;  //ƥ��ɹ���������Ŀ
	
	//ͨ����������ɾѡƥ����
	double min_dist = 10000, max_dist = 0;
	for (int i = 0; i < matches.size(); i++)
	{
		double dist = matches[i].distance;
		if (dist < min_dist) min_dist = dist;
		if (dist > max_dist) max_dist = dist;
	}

	//�������ƥ������������������С��������
	cout << "min_dist=" << min_dist << endl;
	cout << "max_dist=" << max_dist << endl;

	//����������ϴ��ƥ����ɾ��
	vector<DMatch>  good_matches;
	for (int i = 0; i < matches.size(); i++)
	{
		if (matches[i].distance <= max(2 * min_dist, 20.0))
		{
			good_matches.push_back(matches[i]);
		}
	}
	cout << "good_min=" << good_matches.size() << endl;  //ʣ����������Ŀ

	//����ƥ����
	Mat outimg, outimg1;
	drawMatches(img1, Keypoints1, img2, Keypoints2, matches, outimg);
	drawMatches(img1, Keypoints1, img2, Keypoints2, good_matches, outimg1);
	imshow("δɸѡ���", outimg);
	imshow("��С��������ɸѡ", outimg1);

	waitKey(0);  
	return 0; 
}