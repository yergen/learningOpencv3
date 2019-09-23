//Example 13-3.Template matching

#include<opencv2/opencv.hpp>
#include<iostream>

using namespace::std;
using namespace::cv;

void help(char** argv){
	cout << "\n"
		<< "Example of using matchTemplate(). The call is:\n"
		<< "\n"
		<< argv[0] << " template image_to_be_searched\n"
		<< "\n"
		<< "  This routine will search using all methods:\n"
		<< "		TM_SQDIFF		 0\n"
		<< "		TM_SQDIFF_NORMED 1\n"
		<< "		TM_CCORR		 2\n"
		<< "		TM_CCORR_NORMED  3\n"
		<< "		TM_CCOEFF		 4\n"
		<< "		TM_CCOEFF_NORMED 5\n"
		<< "\n";
}

//Display the results of the matches
//

int main(int argc, char** argv)
{
	//if (argc != 3){
	//	//help(argv);
	//	return -1;
	//}

	Mat src, templ, ftmp[6];		//ftmp is what to display on
	
	//Read in the template to be used for matching:
	//
	if ((templ = imread("E:/mycode/mycode_opencv/resource/BlueCup.jpg", 1)).empty()){
		cout << "Error on reading template " << endl;
		//help(argv); 
		return -1;
	}

	//Read in the source image to be searched:
	//
	if ((src = imread("E:/mycode/mycode_opencv/resource/adrian.jpg", 1)).empty()){
		cout << "Error on reading template " << endl;
		//help(argv); 
		return -1;
	}

	//Do the matching of the tempalte with the image
	for (int i = 0; i < 6; ++i){
		matchTemplate(src, templ, ftmp[i], i);
		normalize(ftmp[i], ftmp[i], 1, 0, CV_MINMAX);
	}

	//Display
	//
	imshow("Template", templ);
	imshow("Image", src);
	imshow("SQDIFF", ftmp[0]);
	imshow("SQDIFF_NORMED", ftmp[1]);
	imshow("CCORR", ftmp[2]);
	imshow("CCORR_NORMED", ftmp[3]);
	imshow("CCOEE", ftmp[4]);
	imshow("CCOEE_NORMED", ftmp[5]);

	//Let user view results:
	//
	waitKey(0);

	return 0;
}