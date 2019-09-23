//A better way to print a matrix.
#include<opencv2/opencv.hpp>

using namespace cv;

const int ndim = 3;
const int size[] = { 5, 5, 5 };

template <class T> void print_matrix(const SparseMat_<T>* sm)
{
	SparseMatConstIterator_<T> it = sm->begin();
	SparseMatConstIterator_<T> it_end = sm->end();

	for (; it != it_end; ++it)
	{
		const typename SparseMat_ < T::Node* node = it.node();
		cout << "(" << node->idx[0] << ", " << node->idx[1]
			<< " )= " << *it << endl;
	}
}

void calling_function1(void)
{
	//...
	SparseMat_<float> sm(ndim, size);
	//...
	print_matrix<float>(&sm);
}

void calling_function2(void)
{
	//...
	SparseMat sm(ndim, size, CV_32F);
	//...
	print_matrix<float>((SparseMat_<float>*) sm);
}

int main(int argc, char** argv)
{

	return 0;
}