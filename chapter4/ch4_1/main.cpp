//Example 4-1.Summation of a multidimensional array,
//done plane by plane.
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	const int n_mat_size = 5;
	const int n_mat_sz[] = { n_mat_size, n_mat_size, n_mat_size };
	Mat n_mat(3, n_mat_sz, CV_32FC1);
	
	RNG rng;
	rng.fill(n_mat, RNG::UNIFORM, 0.f, 1.f);//随机产生0-1范围的浮点数

	const Mat* arrays[] = { &n_mat, 0 };
	Mat my_planes[1];
	NAryMatIterator it(arrays, my_planes);

	//On each iteration,it.planes[i] will be the current plane of the
	//i-th array from 'arrays'.
	//
	float s = 0.f; //Total sum over all planes
	int n = 0;	   //Total number of planes
	for (int p = 0; p < it.nplanes; p++, ++it){
		s += sum(it.planes[0])[0];
		n++;
	}

	cout << s << endl;
	cout << n << endl;

	return 0;
}