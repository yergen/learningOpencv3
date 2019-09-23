//Creating signatures from histograms for EMD;
//note that this code is the source of the data in table 13-1,
//in which the hand histogram is compared in different lighting conditions.
//

#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

void help(char** argv)
{
	cout << "\nCall is:\n"
		<< argv[0] << " modeImage0 testImage1 testImage2 badImage3\n\n"
		<< "for example: "
		<< " ./ch7_ex7_3_expanded HandIndoorColor.jpg HandOutdoorColor.jpg "
		<< "HandOutdoorSunColor.jpg fruits.jpg\n"
		<< "\n";
}

int main(int argc, char** argv)
{
	//if (argc != 5) { help(argv); return -1; }

	vector<Mat> src(5);
	Mat tmp;
	int i;

	tmp = imread("E:/mycode/mycode_opencv/resource/HandIndoorColor.jpg", 1);
	if (tmp.empty()) {
		cerr << "Error on reading imae " << endl;
		return -1;
	}

	//parse the first image into two image halves divided halfway on y
	//
	Size size = tmp.size();
	int width = size.width;
	int height = size.height;
	int halfHeight = height >> 1;

	cout << "Getting size [[" << tmp.cols << "] [" << tmp.rows << "]]\n" << endl;
	cout << "Got size(w,h): (" << size.width << "," << size.height << ")" << endl;

	src[0] = Mat(Size(width, halfHeight), CV_8UC3);
	src[1] = Mat(Size(width, halfHeight), CV_8UC3);

	//Divide the first image into top and bottom halves into src[0] and src[1]
	//
	Mat_<Vec3b>::iterator tmpit = tmp.begin<Vec3b>();

	//top half
	//
	Mat_<Vec3b>::iterator s0it = src[0].begin<Vec3b>();
	for (int i = 0; i < width*halfHeight; ++i, ++tmpit, ++s0it) *s0it = *tmpit;

	//Bottom half
	//
	Mat_<Vec3b>::iterator s1it = src[1].begin<Vec3b>();
	for (int i = 0; i < width*halfHeight; ++i, ++tmpit, ++s1it) *s1it = *tmpit;

	vector<string> img = { "E:/mycode/mycode_opencv/resource/HandOutdoorColor.jpg",
		"E:/mycode/mycode_opencv/resource/HandOutdoorSunColor.jpg",
		"E:/mycode/mycode_opencv/resource/fruits.jpg" };

	//Load the other three images
	//
	for (i = 2; i < 5; ++i){
		src[i] = imread(img[i - 2], 1);
		if (src[i].empty()){
			cerr << "Error on reading image" << endl;
			return -1;
		}
	}

	//Compute the HSV image, and decompose it into separate planes.
	//
	vector<Mat> hsv(5), hist(5), hist_img(5);
	int			 h_bins		 = 8;
	int			 s_bins		 = 8;
	int			 hist_size[] = { h_bins, s_bins }, ch[] = { 0, 1 };
	float		 h_ranges[]  = { 0, 180 }; //hue range is [0,180]
	float		 s_ranges[]  = { 0, 255 };
	const float* ranges[]    = { h_ranges, s_ranges };
	int			 scale		 = 10;
	
	for (int i = 0; i < 5; ++i){
		cvtColor(src[i], hsv[i], COLOR_BGR2HSV);
		calcHist(&hsv[i], 1, ch, noArray(), hist[i], 2, hist_size, ranges, true);
		normalize(hist[i], hist[i], 0, 255, NORM_MINMAX);
		hist_img[i] = Mat::zeros(hist_size[0] * scale, hist_size[1] * scale, CV_8UC3);

		//Draw our histogram For the 5 images
		//
		for (int h = 0; h < hist_size[0];h++)
		for (int s = 0; s < hist_size[1]; s++){
			float hval = hist[i].at<float>(h, s);
			rectangle(
				hist_img[i],
				Rect(h*scale, s*scale, scale, scale),
				Scalar::all(hval),
				-1);
		}
	}

	//Display
	//
	namedWindow("Source0", 1); imshow("Source0", src[0]);
	namedWindow("HS Histogram0", 1); imshow("HS Histogram0", hist_img[0]);

	namedWindow("Source1", 1); imshow("Source1", src[1]);
	namedWindow("HS Histogram1", 1); imshow("HS Histogram1", hist_img[1]);

	namedWindow("Source2", 1); imshow("Source2", src[2]);
	namedWindow("HS Histogram2", 1); imshow("HS Histogram2", hist_img[2]);

	namedWindow("Source3", 1); imshow("Source3", src[3]);
	namedWindow("HS Histogram3", 1); imshow("HS Histogram3", hist_img[3]);

	namedWindow("Source4", 1); imshow("Source4", src[4]);
	namedWindow("HS Histogram4", 1); imshow("HS Histogram4", hist_img[4]);

	
	//Compare the histogram src0 vs 1,vs 2,vs 3,vs 4
	cout << "Comparison:\n"
		<< "Corr            Chi             Intersece           Bhat\n"
		<< endl;

	for (int i = 1; i < 5; ++i){//For each histogram
		cout << "Hist[0] vs Hist[" << i << "]: " << endl;
		for (int j = 0; j < 4; ++j){//For each comparison type
			cout << "method[" << j << "]: " << compareHist(hist[0], hist[i], j) << " ";
		}
		cout << endl;
	}

	//Do EMD and report
	//
	vector<Mat> sig(5);
	cout << "\nEMD: " << endl;

	//oi vey, parse histograms to earth movers signatures
	//
	for (int i = 0; i < 5; ++i){

		vector<Vec3f> sigv;

		//(re)normalize histogram to make the bin weights sum to 1.
		//
		normalize(hist[i], hist[i], 1, 0, NORM_L1);
		for (int h = 0; h < h_bins; h++)
		for (int s = 0; s < s_bins; s++){
			float bin_val = hist[i].at<float>(h, s);
			if (bin_val != 0)
				sigv.push_back(Vec3f(bin_val, (float)h, (float)s));
		}

		//make Nx3 32fC1 matrix, where N is the number of nonzero histogram bins
		//
		sig[i] = Mat(sigv).clone().reshape(1);
		if (i > 0)
			cout << "Hist[0] vs Hist[" << i << "]: "
			<< EMD(sig[0], sig[i], DIST_L2) << endl;
	}

	waitKey(0);

	return 0;
}