#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <fstream>

using namespace std;
using namespace cv;

int g_slider_position = 0;
int g_run = 1, g_dontset = 0; //start out in single step mode
VideoCapture g_cap;

void onTrackbarSlide(int pos, void *)
{
	g_cap.set(CAP_PROP_POS_FRAMES, pos);
	if (!g_dontset)
		g_run = 1;
	g_dontset = 0;
}

int main(int argc, char** argv)
{
	namedWindow("Example2_4", WINDOW_AUTOSIZE);
	g_cap.open("video.mp4");
	int frames = (int)g_cap.get(CAP_PROP_FRAME_COUNT);
	int tmpw = (int)g_cap.get(CAP_PROP_FRAME_WIDTH);
	int tmph = (int)g_cap.get(CAP_PROP_FRAME_HEIGHT);
	cout << "Video has " << frames << " frames of dimensions("
		<< tmpw << "," << tmph << ")." << endl;
	createTrackbar("Postion", "Example2_4", &g_slider_position, frames, onTrackbarSlide);

	Mat frame;
	for (;;)
	{
		if (g_run != 0){

			g_cap >> frame; if (frame.empty()) break;
			int current_pos = (int)g_cap.get(CAP_PROP_POS_FRAMES);
			g_dontset = 1;

			setTrackbarPos("Position", "Example2_4", current_pos);
			imshow("Example2_4", frame);

			g_run = -1;

		}

		char c = (char)waitKey(10);
		if (c == 's') //single step
		{
			g_run = 1; cout << "Single step, run = " << g_run << endl;
		}
		if (c == 'r') //run mode
		{
			g_run = -1; cout << "Run mode, run = " << g_run << endl;
		}
		if (c == 27)
			break;
	}
	return 0;
}