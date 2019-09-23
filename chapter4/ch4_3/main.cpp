//Create a 10*10 sparse matrix with a few nonzero elements.
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	int size[] = { 10, 10 };
	SparseMat sm(2, size, CV_32F);

	for (int i = 0; i < 10; i++){ //Fill the array
		int idx[2];
		idx[0] = size[0] * rand();
		idx[1] = size[1] * rand();

		sm.ref<float>(idx) += 1.0f;
	}
	
	//print out the nonzero elements
	// 
	SparseMatConstIterator_<float> it = sm.begin<float>();
	SparseMatConstIterator_<float> it_end = sm.end<float>();

	for (; it != it_end; ++it)
	{
		const SparseMat::Node* node = it.node();
		printf(" (%3d,%3d) %f\n", node->idx[0], node->idx[1], *it);
	}

	return 0;
}