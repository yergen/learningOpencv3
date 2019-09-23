//Example 15-1.Reading out the RGB value of all pixels 
//in one row of a video and accumulating those values 
//into three separate files

#include<opencv2/opencv.hpp>
#include<iostream>
#include<fstream>

using namespace std;
using namespace cv;

void help(char** argv)
{

	cout << "\n"
		<< "Read out RGB pixel values and store them to disk\nCall:\n"
		<< argv[0] << "avi_file\n"
		<< "\n This will store to files blines.csv, glines.csv andrlines.csv\n\n"
		<< endl;

}

int main(int argc, char** argv)
{

	//if (argc != 2) { help(argv); return -1; }
	namedWindow("E:/mycode/mycode_opencv/resource/tree.avi", WINDOW_AUTOSIZE);

	VideoCapture cap;
	if (!cap.open("E:/mycode/mycode_opencv/resource/tree.avi"))
	{
		cerr << "Couldn't open video file" << endl;
		//help(argv);
		cap.open(0);
		return -1;
	}

	Point pt1(10, 10), pt2(30, 30);
	int max_buffer;
	Mat rawImage;
	ofstream b, g, r;
	b.open("blines.csv");
	g.open("glines.csv");
	r.open("rlines.csv");

	//MAIN PROCESSING LOOP
	//
	for (;;){
		cap >> rawImage;
		if (!rawImage.data) break;

		LineIterator it(rawImage, pt1, pt2, 8);
		for (int j = 0; j < it.count; ++j, ++it){
			b << (int)(*it)[0] << ",";
			g << (int)(*it)[1] << ",";
			r << (int)(*it)[2] << ",";
			(*it)[2] = 255;	//Mark this sample in red
		}
		imshow("E:/mycode/mycode_opencv/resource/tree.avi", rawImage);
		waitKey(10);
		b << "\n"; g << "\n"; r << "\n";
	}

	//CLEAN UP
	//
	b << endl; g << endl; r << endl;
	b.close(); g.close(); r.close();
	cout << "\n"
		<< "Data stored to files: blines.csv,glines.csv and rlines.csv\n\n"
		<< endl;

	return 0;

}