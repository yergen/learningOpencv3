//alphablend<imageA><iamgeB><x><y><width><height><alpha><beta>
//
#include<cv.h>
#include<highgui.h>
#include<opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char**argv)
{
	Mat src1 = imread("E:/mycode/mycode_opencv/resource/faces.png");
	Mat src2 = imread("E:/mycode/mycode_opencv/resource/faceTemplate.jpg"); 

	if (!src1.empty() && !src2.empty())
	{
		int x = 230, y = 155;
		int w = src2.size().width - 1, h = src2.size().height - 1;
		double alpha = 0.2, beta = 0.8;

		Mat roi1(src1, Rect(x, y, w, h));
		Mat roi2(src2, Rect(0, 0, w, h));

		addWeighted(roi1, alpha, roi2, beta, 0.0, roi1);

		namedWindow("Alpha Blend", 1);
		imshow("Alpha Blend", src1);
		waitKey(0);
	}

	return 0;
}