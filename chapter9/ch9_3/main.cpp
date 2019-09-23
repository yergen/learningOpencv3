//Example 9_3 using a trackbar to create a "switch" that the user can turn on and off;
//this program plays a video and uses the switch to create a pause functionality.
//
//An example program in which the user can draw boxes on the screen.
//
#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

//Using a trackbar to create a "switch" that the user can turn on and off.
//We make this value global so everyone can see it.
//
int g_switch_value = 1;
void switch_off_function(){ cout << "Pause\n"; }; //YOU COULD DO MORE
void switch_on_function(){ cout << "Run\n"; };

//This will be the callback that we give to the trackbar.
//
void switch_callback(int position, void*)
{
	if (position == 0)
		switch_off_function();
	else
		switch_on_function();
}

void help()
{
	cout << "Call:my.avi" << endl;
	cout << "Shows putting a pause button in a video." << endl;
}

int main(int argc, char** argv)
{
	Mat frame; //To hold movie images
	VideoCapture g_capture;
	help();
	if (!g_capture.open("E:/mycode/mycode_opencv/resource/test.avi"))
	{
		cout << "Failed to open " << endl;
		return -1;
	}

	//Name the main window
	//
	namedWindow("Example", 1);

	//Create the trackbar. We give it a name,
	//and tell it the name of the parent window.
	//
	createTrackbar("Switch", "Example", &g_switch_value, 1, switch_callback);

	//This will cause OpencCV to idle until
	//someone hits the Esc key.
	//
	for (;;){
		if (g_switch_value)
		{
			g_capture >> frame;
			if (frame.empty()) break;
			imshow("Example", frame);
		}
		if (waitKey(10) == 27) break;
	}
	return 0;
}