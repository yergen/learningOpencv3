#include<opencv2/opencv.hpp>
#include<iostream>
#include<fstream>

using namespace std;
using namespace cv;

//Global storage
//
//Float, 3-channel images
//
Mat IavgF, IdiffF, IprevF, IhiF, IlowF;
Mat tmp, tmp2;

//Float, 1-channel image
//
vector<Mat> Igray(3);
vector<Mat> Ilow(3);
vector<Mat> Ihi(3);

//Byte, 1-channel images
//
Mat Imaskt;

//Thresholds
//
float high_thresh = 30.0;
float low_thresh = 38.0;

//Counts number of images learned for averaging later
//
double Icount;

//I is just a sample image for allocation purposes
//(passed in for sizing)
//
void AllocateImages(const Mat& I){
	
	Size sz = I.size();

	IavgF	= Mat::zeros(sz, CV_32FC3);
	IdiffF	= Mat::zeros(sz, CV_32FC3);
	IprevF  = Mat::zeros(sz, CV_32FC3);
	IhiF	= Mat::zeros(sz, CV_32FC3);
	IlowF	= Mat::zeros(sz, CV_32FC3);
	Icount	= 0.00001;		//Protect against divide by zero

	tmp		= Mat::zeros(sz, CV_32FC3);
	tmp2	= Mat::zeros(sz, CV_32FC3);
	Imaskt	= Mat(sz, CV_32FC1);

}

//learn the background statistics for one more frame
//I is a color sample of the background,3-channel,8u
//
void accumulateBackground(Mat& I){

	static int first = 1;		//nb. Not thread safe
	I.convertTo(tmp, CV_32F);	//convert to float
	if (!first){
		IavgF += tmp;
		absdiff(tmp, IprevF, tmp2);
		IdiffF += tmp2;
		Icount += 1.0;
	}
	first = 0;
	IprevF = tmp;

}

void setHighThreshold(float scale){

	IhiF = IavgF + (IdiffF*scale);
	split(IhiF, Ihi);

}

void setLowThreshold(float scale){

	IlowF = IavgF - (IdiffF*scale);
	split(IlowF, Ilow);

}

void createModelsfromStats(){

	IavgF *= (1.0 / Icount);
	IdiffF *= (1.0 / Icount);

	//Make sure diff is always something
	//
	IdiffF += Scalar(1.0, 1.0, 1.0);		
	setHighThreshold(high_thresh);
	setLowThreshold(low_thresh);

}

//Create a binary: 0,255 mask where 255 means foreground pixel
//I			Input image,3-channel,8u
//Imask		Mask image to be created,1-channel 8u
//
void backgroundDiff(Mat& I, Mat&Imask){

	I.convertTo(tmp, CV_32F);	//To float
	split(tmp, Igray);

	//Channel 1
	//
	inRange(Igray[0], Ilow[0], Ihi[0], Imask);

	//Channel 2
	//
	inRange(Igray[1], Ilow[1], Ihi[1], Imaskt);
	Imask = min(Imask, Imaskt);

	//Channel 3
	//
	inRange(Igray[2], Ilow[2], Ihi[2], Imaskt);
	Imask = min(Imask, Imaskt);

	//Finally, invert the results
	//
	Imask = 255 - Imask;

}

void help(char** argv){
	cout << "\n"
		<< "Train a background model on incoming video,then run the model\n"
		<< argv[0] << " avi_file\n"
		<< endl;
}

int main(int argc, char** argv)
{

	Mat image;
	const int number_to_train_on = 50;
	//if (argc != 2) { help(argv); return -1; }
	namedWindow("E:/mycode/mycode_opencv/resource/tree.avi", WINDOW_AUTOSIZE);

	VideoCapture cap;
	if (!cap.open("E:/mycode/mycode_opencv/resource/tree.avi")){
		cerr << "Couldn't open video file" << endl;
		//help(argv);
		cap.open(0);
		return -1;
	}

	//FIRST PROCESSING LOOP (TRAINING)
	//
	int frame_count = 0;

	while (1){
		cap >> image;
		if (!image.data) {exit(0); }
		if (frame_count == 0) { AllocateImages(image);}

		accumulateBackground(image);
		frame_count++;
		imshow("E:/mycode/mycode_opencv/resource/tree.avi", image);
		if (waitKey(100) == 0x20 || frame_count >= number_to_train_on) break;
	}
	printf("%d", frame_count);
	//We have all of our data, so create the models
	//
	createModelsfromStats();

	//SECOND PROCESSING LOOP(TESTING)
	//
	Mat mask;
	while (1){
		cap >> image;
		if (!image.data) exit(0);

		backgroundDiff(image, mask);

		//A simple visualization is to write to the red channel
		//
		split(image, Igray);
		Igray[2] = max(mask, Igray[2]);
		merge(Igray, image);

		imshow("E:/mycode/mycode_opencv/resource/tree.avi", image);
		if (waitKey(100) == 0x20)	break;
	}

	return 0;

}