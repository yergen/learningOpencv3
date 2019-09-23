//Example 11-3 Log-polar transform example.

#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	//if (argc != 3){
	//	cout << "LogPolar\nUsage: " << argv[0] << "<imagename><M value>\n"
	//		<< "<M value>~30 is usually good enough\n";
	//	return -1;
	//}

	Mat src = imread("E:/mycode/mycode_opencv/resource/fruits.jpg", 1);
	if (src.empty()) { cout << "Can't load " << argv[1] << endl; return -1; }

	double M = atof("30.0");
	Mat dst(src.size(), src.type()), src2(src.size(), src.type());

	logPolar(src, dst, Point2f(src.cols*0.5f, src.rows*0.5f), M, INTER_LINEAR | WARP_FILL_OUTLIERS);
	logPolar(dst, src2, Point2f(src.cols*0.5f, src.rows*0.5f), M, INTER_LINEAR | WARP_INVERSE_MAP);

	imshow("src image", src);
	imshow("log-polar", dst);
	imshow("inverse log-polar", src2);

	waitKey();

	return 0;
}