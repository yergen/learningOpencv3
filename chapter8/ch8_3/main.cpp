//Using cv::FileStorage to read a.yml file
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;


int main(int argc, char** argv)
{
	FileStorage fs2("E:/mycode/mycode_opencv/chapter8/test.yml", FileStorage::READ);

	//first method: use (type)operator on FileNode.
	int frameCount = (int)fs2["frameCount"];

	//second method: use cv::FileNode::operator >>
	//
	string date;
	fs2["calibrationDate"] >> date;

	Mat cameraMatrix2, distCoeffs2;
	fs2["cameraMatrix"] >> cameraMatrix2;
	fs2["distCoeffs"] >> distCoeffs2;

	cout << "frameCount: " << frameCount << endl
		<< "calibration date: " << date << endl
		<< "camera matrix: " << endl << cameraMatrix2 << endl
		<< "distortion coeffs: " << endl << distCoeffs2 << endl;

	FileNode features = fs2["features"];
	FileNodeIterator it = features.begin(), it_end = features.end();
	int idx = 0;
	vector<uchar> lbpval;
	
	//iterate through a sequence using FileNodeIterator
	//
	for (; it != it_end; ++it, idx++)
	{
		cout << "fearture #" << idx << ": ";
		cout << "x=" << (int)(*it)["x"] << ", y=" << (int)(*it)["y"] << ", lbp:(";
		
		//(Note: easily read numerical arrays using FileNode >> std::vector.)
		//
		(*it)["lbp"] >> lbpval;
		for (int i = 0; i < (int)lbpval.size(); i++)
			cout << " " << (int)lbpval[i];
		cout << ")" << endl;
	}

	fs2.release();//close file

	return 0;
}
