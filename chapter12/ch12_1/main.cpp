//Example12-1. 
//Using dft() and idft() to accelerate the computation of convolutions.

#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	/*if (argc != 3){
		cout << "Fourier Transform\nUsage: " << argv[0] << " <imagename>" << endl;
		return -1;
	}*/

	Mat A = imread("E:/mycode/mycode_opencv/resource/fruits.jpg", 0);
	
	//if (A.empty()) { cout << "Can not load " << argv[1] << endl; return -1; }

	Size patchSize(100, 100);
	Point topleft(A.cols / 2, A.rows / 2);
	Rect roi(topleft.x, topleft.y, patchSize.width, patchSize.height);
	Mat B = A(roi);
	
	int dft_M = getOptimalDFTSize(A.rows + B.rows - 1);
	int dft_N = getOptimalDFTSize(A.cols + B.cols - 1);

	Mat dft_A = Mat::zeros(dft_M, dft_N, CV_32F);
	Mat dft_B = Mat::zeros(dft_M, dft_N, CV_32F);

	Mat dft_A_part = dft_A(Rect(0, 0, A.cols, A.rows));
	Mat dft_B_part = dft_B(Rect(0, 0, B.cols, B.rows));
	//矩阵数据类型转换
	A.convertTo(dft_A_part, dft_A_part.type(), 1, -mean(A)[0]);
	B.convertTo(dft_B_part, dft_B_part.type(), 1, -mean(B)[0]);

	dft(dft_A, dft_A, 0, A.rows);
	dft(dft_B, dft_B, 0, B.rows);

	//set the last parameter to false to compute convoltion
	//instead of correlation
	//
	mulSpectrums(dft_A, dft_B, dft_A, 0, true);
	idft(dft_A, dft_A, DFT_SCALE, A.rows + B.rows - 1);

	Mat corr = dft_A(Rect(0, 0, A.cols + B.cols - 1, A.rows + B.rows - 1));
	normalize(corr, corr, 0, 1, NORM_MINMAX, corr.type());
	pow(corr, 3., corr);

	B ^= Scalar::all(255);

	imshow("dft_A", dft_A);
	imshow("Image", A);
	imshow("Correlation", corr);
	waitKey();

	return 0;
}