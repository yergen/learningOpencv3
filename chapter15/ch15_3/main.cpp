//Example15-3.Computing the off-diagonal elements of a covariance model.

#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

vector<Mat> planes(3);
vector<Mat> sums(3);
vector<Mat> xysums(6);
Mat sum1;	//不能跟系统函数名一样
int image_count = 0;

//A function to accumulate
//the information we need for our variance computation.
//
void accumulateCovariance(Mat& I)
{

	Mat sum;
	int i, j, n;

	if (sum1.empty()){
		for (int i = 0; i < 3; i++)	//the r, g, and b sums
		{
			sums[i] = Mat::zeros(I.size(), CV_32FC1);
		}
		for (int n = 0; n < 6; n++)
		{
			xysums[n] = Mat::zeros(I.size(), CV_32FC1);
		}
	}

	split(I, planes);
	for (int i = 0; i < 3; i++){
		accumulate(planes[i], sums[i]);
	}
	int n = 0;
	for (int i = 0; i < 3;i++)		//"row" of Sigma
	for (int j = i; j < 3; j++)		//"column" of Sigma
	{
		n++;
		accumulateProduct(planes[i], planes[j], xysums[n]);
	}

	image_count++;

}

//note that 'variance' is sigma^2
//
void computeCovariance(
	Mat& covariance		//a six-channel array, channels are the
	){					//rr,rg,rb,gg,gb,and bb elements of Sigma_xy

	double one_by_N = 1.0 / image_count;

	//reuse the xysum arrays as storage for individual entries
	//
	int n = 0;
	for (int i = 0; i < 3;i++)		//"row" of Sigma
	for (int j = i; j < 3; j++)		//"column" of Sigma
	{
		n++;
		xysums[n] = one_by_N *xysums[n] - (one_by_N*one_by_N)*sums[i].mul(sums[j]);
	}

	//reassemble the six individual elements into a six-channel array
	//
	merge(xysums, covariance);

}

int main(int argc, char** argv)
{


	return 0;

}