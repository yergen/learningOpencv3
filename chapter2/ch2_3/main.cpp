#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

int main(int argc, char** argv)
{
	namedWindow("Example3", WINDOW_AUTOSIZE);
	VideoCapture cap;
	cap.open("video.mp4");

	Mat frame;
	for (;;)
	{
		cap >> frame;
		if (frame.empty()) break;  //Ran out of film
		imshow("Example3", frame);
		if (waitKey(33) >= 0) break;
	}

	return 0;
}