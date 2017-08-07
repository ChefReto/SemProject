void findMostStableKeypoints(const string &dirname){
	int a = 1;																	//Distance from one keypoint to the other. Feel free to choose here one of your choice
  	int nimages;
	vector <cv::Mat> descriptors(50000); 
	vector <cv::KeyPoint > Keypoints;
	vector <std::double> data;
	int x;
	int y;

	int tres = 500;																//Best keypoints

	insertKeypoint(image, x, y, a, Keypoints);
	ReadImageAncComputeDescriptors(nimages, descriptors, Keypoints, dirname);
	runCreatingMatrix(data, x, y, nimages, descriptors); 

	vector<double> v(x*y);
  	v = data;
  	sort1(data, v);															
  	norm(v);
	insertKeypointTreshold(image, x, y, data, tres, a, v, dirname);

}