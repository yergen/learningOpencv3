#include "opencv2/highgui/highgui.hpp"
using namespace cv;
int main(int argc, char**argv)
{
	Mat img = imread("girl.jpg", -1);
	if (img.empty()) return -1;

	namedWindow("Example1", WINDOW_AUTOSIZE);
	imshow("Example1", img);
	waitKey(0);

	destroyWindow("Example1");
	return 0;
}