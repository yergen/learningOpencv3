//Example 2-5. Loading and smoothing an image before it is displayed on the screen
#include<opencv2/opencv.hpp>

using namespace cv;

void example2_5(const Mat &image)
{
	//Create some windows to show the input and output images in.
	//
	namedWindow("Example2_5-in", WINDOW_AUTOSIZE);
	namedWindow("Example2_5-out", WINDOW_AUTOSIZE);

	//Create a window to show our input image.
	//
	imshow("Example2_5-in", image);
	
	//Create an image to hold the smoothed output.
	//
	Mat out;

	//Do the smoothing
	//(Note: Could use GaussianBlur(),blur(),medianBlur() or bilateralFilter().)
	//
	GaussianBlur(image, out, Size(5, 5), 3, 3);
	GaussianBlur(out, out, Size(5, 5), 3, 3);

	//show the smoothed image in the output window.
	//
	imshow("Example2_5-out", out);

	//wait for the user to hit a key,windows will self destruct.
	//
	waitKey(0);

}