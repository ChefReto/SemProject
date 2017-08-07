cv::Mat reSize(cv::Mat image){
	const int kNewWidth = 256;
	const int kNewHeight = 256;
	cv::Mat new_image;
	resize(image, new_image, cvSize(kNewWidth, kNewHeight));
	return new_image;
}