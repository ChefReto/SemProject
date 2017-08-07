using namespace cv;

void cropimage(cv::Mat &image,const string datafile, const string dirname){


	vector<int> coord;
	vector<int> coord2;
	vector<int> coord3;
	vector<int> coord4;


	readinStringFile(datafile, dirname, coord, coord2, coord3, coord4);

	// namedWindow( "Image", WINDOW_AUTOSIZE ); 
	// imshow("Image", image);

	// waitKey(0);

	Mat cropedImage;
	Mat cropedImage2;
	Mat cropedImage3;

	cv::Size S = image.size();
	int Rows = S.height;



	if (coord.empty()){
		//Do nothing
	}
	else{

		int X = coord[0];
		int Y = coord[1];
		// int Width = coord[2];
		int Height = coord[3];


		cv::Size s = image.size();
		int rows = s.height;
		int cols = s.width;




		// Mat cropedImage = image(Rect(X,Y,Height,rows));
		if (Y == 0){
			cropedImage = image(Rect(0,0+Height,cols,rows-Height));
			// namedWindow( "CropedImage", WINDOW_AUTOSIZE ); 
			// imshow("CropedImage", cropedImage);
			// waitKey(0);
		}
		if (X == 0 && Y!= 0){

			cropedImage = image(Rect(0,0,cols,Y));
			// namedWindow( "CropedImage", WINDOW_AUTOSIZE ); 
			// imshow("CropedImage", cropedImage);
			// waitKey(0);

		}

		if (Y < (int)rows/2 && Y > 0){

			cropedImage = image(Rect(0,Y+Height,cols,rows-Height-Y));
			// namedWindow( "CropedImage", WINDOW_AUTOSIZE ); 
			// imshow("CropedImage", cropedImage);
			// waitKey(0);

		}

		if (Y > (int)rows/2 && X > 0){

			cropedImage = image(Rect(0,0,cols,Y));
			// namedWindow( "CropedImage", WINDOW_AUTOSIZE ); 
			// imshow("CropedImage", cropedImage);
			// waitKey(0);

		}

		cv::Size t = cropedImage.size();
		rows = t.height;
		cols = t.width;


		image = cropedImage;
	}



	if (coord2.empty()){
		//Do nothing
	}
	else{



		int X = coord2[0];
		int Y = coord2[1];
		// int Width = coord2[2];
		int Height = coord2[3];


		cv::Size s = cropedImage.size();
		int rows = s.height;
		int cols = s.width;



		// Mat cropedImage = image(Rect(X,Y,Height,rows));
		if (Y == 0){
			cropedImage2 = cropedImage(Rect(0,0+Height,cols,rows-Height));
			// namedWindow( "CropedImage", WINDOW_AUTOSIZE ); 
			// imshow("CropedImage", cropedImage2);
			// waitKey(0);
		}
		if (X == 0 && Y!= 0 && Y > (int)rows/2 ){

			cropedImage2 = cropedImage(Rect(0,0,cols,rows-(Rows-Y)));
			// namedWindow( "CropedImage", WINDOW_AUTOSIZE ); 
			// imshow("CropedImage", cropedImage2);
			// waitKey(0);

		}

		if (Y < (int)rows/2 && Y > 0){

			cropedImage2 = cropedImage(Rect(0,Y,cols,rows-Y));
			// namedWindow( "CropedImage", WINDOW_AUTOSIZE ); 
			// imshow("CropedImage", cropedImage2);
			// waitKey(0);

		}
		if (Y > (int)rows/2 && X > 0){

			cropedImage2 = cropedImage(Rect(0,0,cols,Y));
			// namedWindow( "CropedImage", WINDOW_AUTOSIZE ); 
			// imshow("CropedImage", cropedImage2);
			// waitKey(0);

		}

		cv::Size t = cropedImage2.size();
		rows = t.height;
		cols = t.width;

		image = cropedImage2;
	}

	if (coord3.empty()){
		//Do nothing
	}
	else{

		int X = coord3[0];
		int Y = coord3[1];
		// int Width = coord3[2];
		int Height = coord3[3];


		cv::Size s = cropedImage2.size();
		int rows = s.height;
		int cols = s.width;



		// Mat cropedImage = image(Rect(X,Y,Height,rows));
		if (Y == 0){
			cropedImage3 = cropedImage2(Rect(0,0+Height,cols,rows-Height));
			// namedWindow( "CropedImage", WINDOW_AUTOSIZE ); 
			// imshow("CropedImage", cropedImage3);
			// waitKey(0);
		}
		if (X == 0 && Y!= 0 && Y > (int)rows/2 ){

			cropedImage3 = cropedImage2(Rect(0,0,cols,rows-(Rows-Y)));
			// namedWindow( "CropedImage", WINDOW_AUTOSIZE ); 
			// imshow("CropedImage", cropedImage3);
			// waitKey(0);

		}

		if (Y < (int)rows/2 && Y > 0){

			cropedImage3 = cropedImage2(Rect(0,Y,cols,rows-Y));
			// namedWindow( "CropedImage", WINDOW_AUTOSIZE ); 
			// imshow("CropedImage", cropedImage3);
			// waitKey(0);

		}

		if (Y > (int)rows/2 && X > 0){

			cropedImage3 = cropedImage2(Rect(0,0,cols,Y));
			// namedWindow( "CropedImage", WINDOW_AUTOSIZE ); 
			// imshow("CropedImage", cropedImage3);
			// waitKey(0);

		}



		image = cropedImage3;
	}



	// namedWindow( "CropedImage", WINDOW_AUTOSIZE ); 
	// imshow("CropedImage", image);



}