#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;


int main(int argc, char** argv)
{
	VideoCapture cap("E:/mycode/mycode_opencv/resource/tree.avi");

	unsigned f = (unsigned)cap.get(CAP_PROP_FOURCC);

	char fourcc[] = {
		(char)f,		//First character is lowest bits
		(char)(f >> 8),	//Next character is bits 8-15
		(char)(f >> 16),	//Next character is bits 16-23
		(char)(f >> 24),	//and don't forget to terminate
		'\0'
	};

	cout << "Fourcc for this video was: " << fourcc << endl;

	return 0;
}