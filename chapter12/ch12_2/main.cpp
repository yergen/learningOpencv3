//Example 12-2.Using HoughCircles() to return a sequence of circles
//found in a grayscale image
//
#include<opencv2/opencv.hpp>
#include<iostream>
#include<math.h>

using namespace::cv;
using namespace::std;

int main(int argc, char** argv)
{
	/*if (argc != 2){
		cout << "Hough Circle detect\nUsage: " << argv[0] << " <iamgename>\n" << endl;
		return -1;
	}*/

	Mat src, image;

	src = imread("E:/mycode/mycode_opencv/resource/stuff.jpg", 1);
	//if (src.empty()) { cout << "Can not load " << argv[1] << endl; return - 1; }

	cvtColor(src, image, CV_BGR2GRAY);
	GaussianBlur(image, image, Size(5, 5), 0, 0);

	vector<Vec3f> circles;
	HoughCircles(image, circles, HOUGH_GRADIENT, 2, image.cols / 10);

	for (size_t i = 0; i < circles.size(); ++i){
		circle(
			src,
			Point(cvRound(circles[i][0]),cvRound(circles[i][1])),
			cvRound(circles[i][2]),
			Scalar(0, 0, 255),
			2,
			LINE_AA
			);
	}

	imshow("Hough Circles", src);
	waitKey(0);

	return 0;
}