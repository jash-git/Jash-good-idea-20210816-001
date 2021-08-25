#include <iostream>
#include <opencv2\opencv.hpp>
#include <vector>
using namespace std;
using namespace cv;  

void match_min(vector<DMatch> matches, vector<DMatch> & good_matches)
{
	double min_dist = 10000, max_dist = 0;
	for (int i = 0; i < matches.size(); i++)
	{
		double dist = matches[i].distance;
		if (dist < min_dist) min_dist = dist;
		if (dist > max_dist) max_dist = dist;
	}
	cout << "min_dist=" << min_dist << endl;
	cout << "max_dist=" << max_dist << endl;

	for (int i = 0; i < matches.size(); i++)
		if (matches[i].distance <= max(2 * min_dist, 20.0))
			good_matches.push_back(matches[i]);
}

//RANSAC�㷨ʵ��
void ransac(vector<DMatch> matches, vector<KeyPoint> queryKeyPoint, vector<KeyPoint> trainKeyPoint, vector<DMatch> &matches_ransac)
{
	//���屣��ƥ��������
	vector<Point2f> srcPoints(matches.size()), dstPoints(matches.size());
	//����ӹؼ�������ȡ����ƥ���Ե�����
	for (int i = 0; i<matches.size(); i++)
	{
		srcPoints[i] = queryKeyPoint[matches[i].queryIdx].pt;
		dstPoints[i] = trainKeyPoint[matches[i].trainIdx].pt;
	}
	
	//ƥ���Խ���RANSAC����
	vector<int> inliersMask(srcPoints.size());
	//Mat homography;
	//homography = findHomography(srcPoints, dstPoints, RANSAC, 5, inliersMask);
	findHomography(srcPoints, dstPoints, RANSAC, 5, inliersMask);
	//�ֶ��ı���RANSAC���˺��ƥ����
	for (int i = 0; i<inliersMask.size(); i++)
		if (inliersMask[i])
			matches_ransac.push_back(matches[i]);
}

void orb_features(Mat &gray, vector<KeyPoint> &keypionts, Mat &descriptions)
{
	Ptr<ORB> orb = ORB::create(1000, 1.2f);
	orb->detect(gray, keypionts);
	orb->compute(gray, keypionts, descriptions);
}

int main()
{
	Mat img1 = imread("box.png");  //��ȡͼ�񣬸���ͼƬ����λ����д·������
	Mat img2 = imread("box_in_scene.png");
	if (!(img1.data && img2.data))
	{
		cout << "��ȡͼ�������ȷ��ͼ���ļ��Ƿ���ȷ" << endl;
		return -1;
	}

	//��ȡORB������
	vector<KeyPoint> Keypoints1, Keypoints2;
	Mat descriptions1, descriptions2;

	//��������ָ��ORB��������ȡ
	orb_features(img1, Keypoints1, descriptions1);
	orb_features(img2, Keypoints2, descriptions2);

	//������ƥ��
	vector<DMatch> matches, good_min,good_ransac;
	BFMatcher matcher(NORM_HAMMING);
	matcher.match(descriptions1, descriptions2, matches);
	cout << "matches=" << matches.size() << endl;

	//��С��������
	match_min(matches, good_min);
	cout << "good_min=" << good_min.size() << endl;

	//��ransac�㷨ɸѡƥ����
	ransac(good_min, Keypoints1, Keypoints2, good_ransac);
	cout << "good_matches.size=" << good_ransac.size() << endl;

	//����ƥ����
	Mat outimg, outimg1, outimg2;
	drawMatches(img1, Keypoints1, img2, Keypoints2, matches, outimg);
	drawMatches(img1, Keypoints1, img2, Keypoints2, good_min, outimg1);
	drawMatches(img1, Keypoints1, img2, Keypoints2, good_ransac, outimg2);
	imshow("δɸѡ���", outimg);
	imshow("��С��������ɸѡ", outimg1);
	imshow("ransacɸѡ", outimg2);
	waitKey(0);  //�ȴ���������
	return 0;  //�������
}