//Summation of two arrays using the N-ary operator.
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv)
{
	const int n_mat_size = 5;
	const int n_mat_sz[] = { n_mat_size, n_mat_size, n_mat_size };
	Mat n_mat0(3, n_mat_sz, CV_32FC1);
	Mat n_mat1(3, n_mat_sz, CV_32FC1);

	RNG rng;
	rng.fill(n_mat0, RNG::UNIFORM, 0.f, 1.f);
	rng.fill(n_mat1, RNG::UNIFORM, 0.f, 1.f);

	const Mat* arrays[] = { &n_mat0, &n_mat1, 0 };
	Mat my_plane[2];
	NAryMatIterator it(arrays, my_plane);

	float s = 0.f;		//Total sum over all planes in both arrays
	int n = 0;			//Total number of planes
	for (int p = 0; p < it.nplanes; p++, ++it)
	{
		s += sum(it.planes[0])[0];
		s += sum(it.planes[1])[0];
		n++;
	}

	return 0;
}