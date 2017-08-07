/*This function detects the FAST keypoints*/
using namespace std;
using namespace cv;


void fastdetector(cv::Mat image){

	Mat gray;
	vector<KeyPoint> keypoints;
	cv::Mat img_keypoints;
	int threshold=50;
	cvtColor(image, gray, CV_BGR2GRAY);


	FAST(gray,keypoints,threshold,true);


	cv::KeyPointsFilter::retainBest(keypoints, 100);
	drawKeypoints(image, keypoints, img_keypoints, Scalar(0, 0, 255));
  	namedWindow( "Image with FAST Keypoints", WINDOW_NORMAL );
  	imshow("Image with FAST Keypoints", img_keypoints);
  	// waitKey(0);

	imwrite( "Viz/FastKeypoints_100.jpg", img_keypoints);

}

