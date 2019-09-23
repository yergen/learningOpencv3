//Example 14-3.Drawing labeled connected components.

#include<opencv2/opencv.hpp>
#include<algorithm>
#include<iostream>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{

	Mat img, img_edge, labels, centroids, img_color, stats;  
	
	//load image or show help if no image was provided
	//
	img = imread("E:/mycode/mycode_opencv/resource/HandIndoorColor.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	//if (argc != 2 || img.empty()){
	//	cout << "\nExample 8_3 Drawing Connected componnents\n"
	//		<< "Call is:\n" << argv[0] << " image\n\n";
	//	return -1;
	//}

	threshold(img, img_edge, 128, 255, THRESH_BINARY);
	imshow("Image after threshold", img_edge);

	int i, nccomps = connectedComponentsWithStats(img_edge, labels, stats, centroids);
	cout << "Total Connected Components Detected: " << nccomps << endl;

	vector<Vec3b> colors(nccomps + 1);
	colors[0] = Vec3b(0, 0, 0);	//background pixels remain black.
	for (int i = 1; i <= nccomps; i++){
		colors[i] = Vec3b(rand() % 256, rand() % 256, rand() % 256);
		if (stats.at<int>(i - 1, CC_STAT_AREA) < 100)
			colors[i] = Vec3b(0, 0, 0);	//small regions are painted with black too.
	}
	img_color = Mat::zeros(img.size(), CV_8UC3);
	for (int y = 0; y < img_color.rows;y++)
	for (int x = 0; x < img_color.cols; x++)
	{
		int label = labels.at<int>(y, x);
		CV_Assert(0 <= label && label <= nccomps);
		img_color.at<Vec3b>(y, x) = colors[label];
	}
	imshow("Labeled map", img_color);
	waitKey();

	return 0;

}