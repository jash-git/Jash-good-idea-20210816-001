    Mat src = imread("D:/vcprojects/images/rotate_text.png");

    Mat gray, binary;

    cvtColor(src, gray, COLOR_BGR2GRAY);

    threshold(gray, binary, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);

    imshow("binary", binary);

    imwrite("D:/binary_text.png", binary);


    vector<Point> points;

    findNonZero(binary, points);

    RotatedRect box = minAreaRect(points);


    double angle = box.angle;

    if (angle < -45.)

        angle += 90.;

    printf("angle : %.2f\n", angle);


    Point2f vertices[4];

    box.points(vertices);

    for (int i = 0; i < 4; ++i)

        line(src, vertices[i], vertices[(i + 1) % 4], Scalar(0, 0, 255), 2);

    imshow("box", src);

    imwrite("D:/box_text.png", src);


    Mat rot_mat = getRotationMatrix2D(box.center, angle, 1);

    Mat rotated;

    warpAffine(src, rotated, rot_mat, src.size(), cv::INTER_CUBIC, 0, Scalar(255, 255, 255));

    //bitwise_not(rotated, rotated);

    imshow("deskew-demo", rotated);