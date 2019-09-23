//Example 15-5. Cleanup using cnnected components
#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;
//This cleans up the foreground segmentation mask 
//derived from calls to backgroundDiff
//
void findConnectComponents(
	Mat& mask,				//Is a grayscale(8-bit depth) "raw" mask image
							//that will be cleaned up
	vector<Rect>& bbs,		//Ref to bounding box rectangle return vector
	vector<Point>& centers,	//Ref to centers return vector
	int poly1_hull0 = 1,    //If set, approximate connected component by
							//(DEFAULT)polygon, or else convex hull(0)
	float perimScale = 4    //Len = (width+height)
	);

#define DP_EPSILON_DENOMINATOR 20.0
//How many iteration of erosion and/or dilation there should be
//
#define CVCLOSE_ITR 1

void findConnectComponents(
	Mat& mask,
	vector<Rect>& bbs,
	vector<Point>& centers,
	int poly1_hull0,
	float perimScale
	){

	//CLEAN UP RAW MASK
	//
	morphologyEx(mask, mask, MORPH_OPEN, Mat(), Point(-1, -1), CVCLOSE_ITR);
	morphologyEx(mask, mask, MORPH_CLOSE, Mat(), Point(-1, -1), CVCLOSE_ITR);

	//FIND CONTOURS AROUND ONLY BIGGER REGIONS
	//
	vector<vector<Point>> contours_all;		//all contours found
	vector<vector<Point>> contours;			//just the ones we want to keep
	findContours(mask, contours_all, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

	for (vector<vector<Point>>::iterator c = contours_all.begin(); c != contours.end(); ++c)
	{
		//length of this contour
		//
		int len = arcLength(*c, true);

		//length threshold a fraction of image perimeter
		//
		double q = (mask.rows + mask.cols) / DP_EPSILON_DENOMINATOR;
		
		if (len >= q){	//If the contour is long enough to keep...

			vector<Point> c_new;
			if (poly1_hull0){ //If the caller wants results as reduced polygons...
				approxPolyDP(*c, c_new, len / 30.0, true);
			}
			else{ //Convex Hull of the segmentation
				convexHull(*c, c_new);
			}
			contours.push_back(c_new);
		}
	}

	//Just some convenience variables
	const Scalar CVX_WHITE = CV_RGB(0xff, 0xff, 0xff);
	const Scalar CVX_BLACK = CV_RGB(0x00, 0x00, 0x00);

	//CALC CENTER OF MASS AND/OR BOUNDING RECTANGLES
	//
	int idx = 0;
	Moments moment;
	Mat scratch = mask.clone();
	for (vector<vector<Point>> ::iterator c = contours.begin(); c != contours.end; c++, idx++){

		drawContours(scratch, contours, idx, CVX_WHITE, CV_FILLED);

		//find the center of each contour
		//
		moment = moments(scratch, true);
		Point p;
		p.x = (int)(moment.m10 / moment.m00);
		p.y = (int)(moment.m01 / moment.m00);
		centers.push_back(p);

		bbs.push_back(boundingRect(*c));

		scratch.setTo(0);
	}

	//PAINT THE FOUND REGIONS BACK INTO THE IMAGE
	//
	mask.setTo(0);
	drawContours(mask, contours, -1, CVX_WHITE);

}

int main(int argc, char** argv)
{

	return 0;
}