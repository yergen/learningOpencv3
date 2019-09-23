//Example2-8.Combining the pyramid down operator(twice) and 
//the Canny subroutine in a simple pipeline.
#include<opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv)
{
	Mat img_rgb, img_gry, img_pyr, img_pyr2, img_cny;

	namedWindow("Example Gray", WINDOW_AUTOSIZE);
	namedWindow("Example Canny", WINDOW_AUTOSIZE);

	img_rgb = imread("girl.jpg");

	cvtColor(img_rgb, img_gry, COLOR_BGR2GRAY);
	imshow("Example Gray", img_gry);
	pyrDown(img_gry, img_pyr);
	//imshow("Example gry", img_gry);
	pyrDown(img_pyr, img_pyr2);
	//imshow("Example gry2", img_pyr2);
	Canny(img_pyr2, img_cny, 10, 100, 3, true);
	imshow("Example Canny", img_cny);

	waitKey(0);

	return 0;
}