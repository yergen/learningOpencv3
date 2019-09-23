//Example2-10. The same object can load videos form
//a camera or a file.
#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	namedWindow("Example2_10", WINDOW_AUTOSIZE);

	VideoCapture cap;
	//cap.open(0); //open the first camera
	cap.open("video.mp4");

	if (!cap.isOpened()){ //check if we succeeded
		cerr << "Couldn't open capture." << endl;
		return -1;
	}

	Mat frame;
	for (;;)
	{
		cap >> frame;
		if (frame.empty()) break;  //Ran out of film
		imshow("Example2_10", frame);
		if (waitKey(33) >= 0) break;

	}

	return 0;
}