//Example 10-2. Alternative method to combine and threshold image planes.

#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

void sum_rgv(const Mat& src, Mat& dst)
{
	//Split image onto the color planes.
	//
	vector<Mat> planes;
	split(src, planes);

	Mat b = planes[0], g = planes[1], r = planes[2];

	//Accumulate separate planes, combine and threshold.
	//s = 1/3*r + 1/3*g + 1/3*b
	Mat s = Mat::zeros(b.size(), CV_32F);
	accumulate(b, s);
	accumulate(g, s);
	accumulate(r, s);

	//Truncate values above 100 and rescale into dst.
	//
	threshold(s, s, 100, 100, THRESH_TRUNC);
	s.convertTo(dst, b.type());
}

void help()
{
	cout << "Call: ./ch10_1 faces.png" << endl;
	cout << "Shows use of alpha blending(addWeighted) and threshold" << endl;
}

int main(int argc, char** argv)
{
	help();

	//if (argc < 2) { cout << "specify input image" << endl; return -1; }

	//Load the image from the given file name.
	//
	string path = "../../../resource/faces.png";

	Mat src = imread(path), dst;
	if (src.empty()) { cout << "can not load" << path << endl; return -1; }
	sum_rgv(src, dst);

	//Create a named window with the name of the file and
	//show the image in the window.
	//
	imshow(path, dst);

	//Idle until the user hits any key.
	//
	waitKey(0);

	return 0;
}