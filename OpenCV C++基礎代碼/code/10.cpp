void QuickDemo::bitwise_demo(Mat &image)
{
    Mat m1 = Mat::zeros(Size(256,256),CV_8UC3);
    Mat m2 = Mat::zeros(Size(256,256),CV_8UC3);
	//這個函數參數1是圖片名稱，參數2是矩形的起始&末尾位置，參數3 Scalar表示將要繪製圖像的顏色，參數4表示小於0表示填充，大於0表示繪製，參數5表示四鄰域或者八鄰域的繪製，參數6表示中心坐標或者半徑坐標的小數位數。
    rectangle(m1,Rect(100,100,80,80),Scalar(255,255,0),-1,LINE_8,0);//小于0表示填充，大于0表示绘制
    rectangle(m2,Rect(150,150,80,80), Scalar(0,255,255), -1, LINE_8, 0);
    imshow("m1", m1);
    imshow("m2", m2);
    Mat dst;
    bitwise_and(m1, m2, dst);//位操作与
    bitwise_or(m1, m2, dst);//位操作或
    bitwise_not(image, dst);//取反操作
    bitwise_xor(m1, m2, dst);//异或操作
    imshow("像素位操作", dst);
}