//Example 15-5. Cleanup using cnnected components
#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;
//This cleans up the foreground segmentation mask 
//derived from calls to backgroundDiff
//
void findConnectedComponents(
	Mat& mask,		//Is a grayscale(8-bit depth) "raw" mask image
	//that will be cleaned up
	int poly1_hull0 = 1, //If set, approximate connected component by
	//(DEFAULT)polygon, or else convex hull(0)
	float perimScale = 4, //Len = (width+height)
	){

}

int main(int argc, char** argv)
{

	return 0;
}