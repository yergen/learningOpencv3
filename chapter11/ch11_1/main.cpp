//Example11-1. An affine transformation

#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	//if (argc != 2)
	//{
	//	cout << "Wrap affine\nUsage: " << argv[0] << " <imagename>\n" << endl;
	//	return -1;
	//}

	Mat src = imread("E:/mycode/mycode_opencv/resource/fruits.jpg", 1);
	if (src.empty()) { cout << "Can not load " << argv[1] << endl; return -1; }

	Point2f srcTri[] =
	{
		Point2f(0, 0),				//src Top left
		Point2f(src.cols - 1, 0),	//src Top right
		Point2f(0.0, src.rows - 1)	//src Bottom left
	};

	Point2f dstTri[] =
	{
		Point2f(src.cols*0.f, src.rows*0.33f),		//dst Top left
		Point2f(src.cols*0.85f, src.rows*0.25f),	//dst Top right
		Point2f(src.cols*0.15f, src.rows*0.7f)		//dst Bottom left
	};

	//COMPUTE AFFINE MATRIX
	//
	Mat warp_mat = getAffineTransform(srcTri, dstTri);
	Mat dst, dst2;
	warpAffine(src, dst, warp_mat, src.size(), INTER_LINEAR, BORDER_CONSTANT, Scalar());
	for (int i = 0; i < 2; ++i)
	{
		circle(dst, dstTri[i], 5, Scalar(255, 0, 255), -1, LINE_AA);
	}

	imshow("Affine Transform Test", dst);
	waitKey();

	for (int frame = 0;; ++frame)
	{
		//COMPUTE ROTATION MATRIX
		Point2f center(src.cols*0.5f, src.rows*0.5f);
		double angle = frame * 3 % 360, scale = (cos((angle - 60)*CV_PI / 180) + 1.05)*0.8;
		
		Mat rot_mat = getRotationMatrix2D(center, angle, scale);

		warpAffine(src, dst, rot_mat, src.size(), INTER_LINEAR, BORDER_CONSTANT, Scalar());

		imshow("Rotated Image", dst);
		if (waitKey(30) >= 0)
			break;
	}

	return 0;
}
