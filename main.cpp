// Gallia

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int CamTest();
int PicTest();

int main(int argc, char **argv) {
	
	//return CamTest();
	return PicTest();

}

int CamTest()
{
	VideoCapture cap ( 0 ); // open the default camera
	if ( !cap.isOpened() )
			return -1;
	
	namedWindow ("Gallia");
	
	Mat frame;
	
	vector<KeyPoint> features;
	SusureFeatureDetector susure_detector(45, 60, 10, 8, 5);

	Scalar red(50.0, 50.0, 255.0);

	for ( ;; ) {
		cap.grab();
		bool grabbed = cap.retrieve(frame, 0); // grab a new frame
		if (!grabbed)
			continue;

		Mat img_gray;
		cvtColor(frame, img_gray, CV_RGB2GRAY);

		susure_detector.detect(img_gray, features);
		
		drawKeypoints(frame, features, frame, red, DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

		imshow("Gallia", frame);
		
		int key = cvWaitKey(2);
		if (key == -1)
			continue;
		
		if ((key&255) == 'q')
			break;
		else if ((key&255) == 27)
			break;
	}

	return 0;
}

int PicTest()
{
	Mat img_rgb  = imread("img1.ppm");
	Mat img_gray;
	cvtColor(img_rgb, img_gray, CV_RGB2GRAY);
	
	vector<KeyPoint> features;
	StarFeatureDetector star_detector(45, 75, 10, 8, 5);
	double t = (double)getTickCount();
	star_detector.detect(img_gray, features);
	t = ((double)getTickCount() - t)/getTickFrequency();
	cout<<"# star features: "<<features.size()<<" - t: "<<t<<endl;

	Mat img_out;
	Scalar red(50.0, 50.0, 255.0);
	drawKeypoints(img_gray, features, img_out, red, DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
	imwrite("image_1_star.jpg", img_out);
	
	features.clear();
	SusureFeatureDetector susure_detector(45, 78, 10, 8, 5);
	t = (double)getTickCount();
	susure_detector.detect(img_gray, features);
	t = ((double)getTickCount() - t)/getTickFrequency();
	cout<<"# susure features: "<<features.size()<<" - t: "<<t<<endl;

	drawKeypoints(img_gray, features, img_out, red, DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
	imwrite("image_1_susure.jpg", img_out);

	return 0;
}
