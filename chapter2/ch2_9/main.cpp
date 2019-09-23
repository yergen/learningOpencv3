//Example2-9.We show a simple way to read and 
//write pixel values from example 2-8.
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;
int main(int argc, char** argv)
{
	Mat img_rgb, img_gry, img_pyr, img_pyr2, img_cny;
	int x = 16, y = 32;

	namedWindow("Example Gray", WINDOW_AUTOSIZE);
	namedWindow("Example Canny", WINDOW_AUTOSIZE);
	
	img_rgb = imread("girl.jpg");

	cvtColor(img_rgb, img_gry, COLOR_BGR2GRAY);
	imshow("Example Gray", img_gry);
	pyrDown(img_gry, img_pyr);
	pyrDown(img_pyr, img_pyr2);
	Canny(img_pyr2, img_cny, 10, 100, 3, true);
	imshow("Example Canny", img_cny);

	Vec3b intensity = img_rgb.at<Vec3b>(y, x);
	//(Note:We could write img_rgb.at<Vec3b>(x,y)[0])
	//
	uchar blue = intensity[0];
	uchar green = intensity[1];
	uchar red = intensity[2];
	
	cout << "At(x,y) = (" << x << ", " << y <<
		"):(blue,green,red)=(" << (unsigned int)blue <<
		", "<< (unsigned int)green << ", " << 
		(unsigned int)red <<")" << endl;

	cout << "Gray pixel there is: " <<
		(unsigned int)img_gry.at<uchar>(y, x) << endl;
	
	x /= 4; y /= 4;

	cout << "Pyramid2 pixel there is: " <<
		(unsigned int)img_pyr2.at<uchar>(y, x) << endl;

	waitKey(0);

	return 0;
}