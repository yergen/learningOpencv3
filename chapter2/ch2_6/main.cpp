//Example2_6 Using pyrDown() to create a new image 
//that is half the width and height of the input image.
#include<opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv)
{
	Mat img1, img2;

	namedWindow("Example1", WINDOW_AUTOSIZE);
	namedWindow("Example2", WINDOW_AUTOSIZE);

	img1 = imread("girl.jpg");
	imshow("Example1", img1);

	pyrDown(img1, img2);
	imshow("Example2", img2);

	waitKey(0);

	return 0;
}