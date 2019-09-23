//Example 14-1.Finding contours based on a trackbar's location;
//the contours are updated whenever the trackbar is moved.

#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

Mat g_gray, g_binary;
int g_thresh = 100;

void on_trackbar(int, void*){
	
	threshold(g_gray, g_binary, g_thresh, 255, THRESH_BINARY);
	vector<vector<Point>> contours;
	findContours(g_binary, contours, noArray(), RETR_LIST, CHAIN_APPROX_SIMPLE);
	g_binary = Scalar::all(0);

	drawContours(g_binary, contours, -1, Scalar::all(255));
	imshow("Contours", g_binary);

}

int main(int argc, char** argv)
{

	g_gray = imread("E:/mycode/mycode_opencv/resource/fruits.jpg", 0);
	namedWindow("src image", 1);
	imshow("src image", g_gray);

	//if (argc != 2 || g_gray.empty()){
	//	cout << "Find threshold dependent contours\nUsage: " << argv[0]
	//		<< "fruits.jpg" << endl;
	//	return -1;
	//}
	namedWindow("Contours", 1);

	createTrackbar("Threshold", "Contours", &g_thresh, 255, on_trackbar);
	on_trackbar(0, 0);

	waitKey(0);

	return 0;

}