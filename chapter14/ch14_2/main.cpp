//Example 14-2.Finding and drawing contours on an input image.

#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

struct AreaCmp{
	AreaCmp(const vector<float> & _areas) : areas(&_areas){}
	bool operator()(int a, int b) const{ return (*areas)[a] > (*areas)[b]; }
	const vector<float>* areas;
};


int main(int argc, char** argv)
{

	Mat img, img_edge, img_color;

	//load image or show help if no image was provided
	//
	img = imread("E:/mycode/mycode_opencv/resource/box.png", CV_LOAD_IMAGE_GRAYSCALE);

	//if (argc != 2 || img.empty()){
	//	cout << "\nExample 8_2 Drawing Contours\nCall is:\n./ch8_ex8_2 image\n\n";
	//	return -1;
	//}

	threshold(img, img_edge, 128, 255, THRESH_BINARY);
	imshow("Image after threshold", img_edge);
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	findContours(img_edge, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE);
	cout << "\n\nHit any key to draw the next contour,ESC to quit\n\n";
	cout << "Total Contours Detected: " << contours.size() << endl;

	vector<int> sortIdx(contours.size());
	vector<float> areas(contours.size());
	
	for (int n = 0; n < (int)contours.size(); n++){
		sortIdx[n] = n;
		areas[n] = contourArea(contours[n], false);
	}

	//sort contours so that the largest contours go first.
	//
	sort(sortIdx.begin(), sortIdx.end(), AreaCmp(areas));

	cout << "contours.size: " << contours.size() << endl;
	for (int n = 0; n < (int)sortIdx.size(); n++){
		int idx = sortIdx[n];
		cvtColor(img, img_color, COLOR_GRAY2BGR);
		drawContours(
			img_color, contours, idx,
			Scalar(0, 0, 255), 2, 8, hierarchy,
			0		//Try different values of max_level,and see what happens
			);
		cout << "n: " << n << endl;
		cout << "Contour #" << idx << ": area=" << areas[idx] <<
			",nvertices=" << contours[idx].size() << endl;
		imshow("E:/mycode/mycode_opencv/resource/box.png", img_color);
		int k;
		if ((k = waitKey() & 255) == 27)	//等待Esc按键按下退出
			break;
	}
	cout << "Finished all contours\n";

	return 0;

}