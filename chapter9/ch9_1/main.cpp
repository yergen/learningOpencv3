#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	//create a named window with the name of the file
	//
	namedWindow("image", 1);//1: users arr not able to resize the window

	//load the image from the given filename
	//
	Mat img = imread("E:/mycode/mycode_opencv/resource/fruits.jpg");

	//show the iamge in the named window
	//
	imshow("image", img);

	//idle until the user hits the ESC key
	//
	while (true)
	{
		if (waitKey(100/*milliseconds*/) == 27) break;
	}

	//clean up and don't be piggies
	//
	destroyWindow("image");

	return 0;
}