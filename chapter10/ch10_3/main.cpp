//Example 10-3. Threshold versus adaptive threshold

#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	/*if (argc != 7)
	{
		cout << "Usage: " << argv[0] << " fixed_threshold invert(0=off | 1=on) "
			"adaptive_type(0=mean | 1=gaussian) block_size offset image\n"
			"Example: " << argv[0] << "100 1 0 15 10 fruits.jpg\n";
		return -1;
	}*/
	
	//command line
	//
	/*double fixed_threshold = (double)atof(argv[1]);
	int threshold_type = atoi(argv[2]) ? THRESH_BINARY : THRESH_BINARY_INV;
	int adaptive_method = atoi(argv[3]) ? ADAPTIVE_THRESH_MEAN_C : ADAPTIVE_THRESH_GAUSSIAN_C;
	int block_size = atoi(argv[4]);
	double offset = (double)atof(argv[5]);
	Mat Igray = imread(argv[6], CV_LOAD_IMAGE_GRAYSCALE);*/

	Mat Igray = imread("E:/mycode/mycode_opencv/resource/faces.png", CV_LOAD_IMAGE_GRAYSCALE);

	//Read in gray image
	//
	//if (Igray.empty()) { cout << "Can not load " << argv[6] << endl; return -1; }


	//Declare the output iamges.
	//
	Mat It, Iat;
	threshold(Igray, It, 50, 255, THRESH_BINARY);
	adaptiveThreshold(Igray, Iat, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, (15,15), 0);

	//show the result.
	//
	imshow("Raw", Igray);
	imshow("Threshold", It);
	imshow("Adaptive Threshold", Iat);
	waitKey(0);

	return 0;
}

