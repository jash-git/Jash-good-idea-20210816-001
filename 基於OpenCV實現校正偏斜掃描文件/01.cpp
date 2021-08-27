    Mat src = imread("D:/vcprojects/images/rotate_text.png");

    Mat gray, binary;

    cvtColor(src, gray, COLOR_BGR2GRAY);


    //expand input image to optimal size

    Mat padded;                            

    int m = getOptimalDFTSize(gray.rows);

    int n = getOptimalDFTSize(gray.cols);

    // on the border add zero values

    copyMakeBorder(gray, padded, 0, m - gray.rows, 0, n - gray.cols, BORDER_CONSTANT, Scalar::all(0));

    Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };

    Mat complexI;

    // Add to the expanded another plane with zeros

    merge(planes, 2, complexI);

    // 离散傅立叶变换

    dft(complexI, complexI);          


    // 实部与虚部得到梯度图像

    // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))

    split(complexI, planes);                  

    magnitude(planes[0], planes[1], planes[0]);

    Mat magI = planes[0];

    magI += Scalar::all(1);

    log(magI, magI);

    // crop the spectrum, if it has an odd number of rows or columns

    magI = magI(Rect(0, 0, magI.cols & -2, magI.rows & -2));

    // rearrange the quadrants of Fourier image  so that the origin is at the image center

    int cx = magI.cols / 2;

    int cy = magI.rows / 2;

    Mat q0(magI, Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant

    Mat q1(magI, Rect(cx, 0, cx, cy));  // Top-Right

    Mat q2(magI, Rect(0, cy, cx, cy));  // Bottom-Left

    Mat q3(magI, Rect(cx, cy, cx, cy)); // Bottom-Right

    Mat tmp;                          

    // swap quadrants (Top-Left with Bottom-Right)

    q0.copyTo(tmp);

    q3.copyTo(q0);

    tmp.copyTo(q3);

    q1.copyTo(tmp);                  

    q2.copyTo(q1);

    tmp.copyTo(q2);


    // 归一化与阈值化显示

    normalize(magI, magI, 0, 1.0, NORM_MINMAX);

    Mat dst;

    magI.convertTo(dst, CV_8UC1, 255, 0);

    threshold(dst, binary, 160, 255, THRESH_BINARY);


    // 霍夫直线

    vector<Vec2f> lines;

    Mat linImg = Mat::zeros(binary.size(), CV_8UC3);

    HoughLines(binary, lines, 1, (float)CV_PI / 180, 30, 0, 0);

    int numLines = lines.size();

    float degree = 0.0;

    for (int l = 0; l<numLines; l++)

    {

        float rho = lines[l][0], theta = lines[l][1];

        float offset = CV_PI / 12.0;

        if (abs(theta) >  offset && abs(theta)< (CV_PI / 2.0- offset)) {

            printf("theta : %.2f\n", theta);

            degree = (theta)*180-90;

        }

        Point pt1, pt2;

        double a = cos(theta), b = sin(theta);

        double x0 = a*rho, y0 = b*rho;

        pt1.x = cvRound(x0 + 1000 * (-b));

        pt1.y = cvRound(y0 + 1000 * (a));

        pt2.x = cvRound(x0 - 1000 * (-b));

        pt2.y = cvRound(y0 - 1000 * (a));

        line(linImg, pt1, pt2, Scalar(0, 255, 0), 3, 8, 0);

    }

    imshow("lines", linImg);


    // 旋转调整

    Mat rot_mat = getRotationMatrix2D(Point(binary.cols/2, binary.rows/2), degree, 1);

    Mat rotated;

    warpAffine(src, rotated, rot_mat, src.size(), cv::INTER_CUBIC, 0, Scalar(255, 255, 255));

    imshow("input", src);

    imshow("deskew-demo", rotated);

    imwrite("D:/deskew_text.png", rotated);