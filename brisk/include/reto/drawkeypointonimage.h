void drawKeypointonImage(cv::Mat image, int &a, const string i, int treshold)
{
  // waitKey(0);
  vector<cv::KeyPoint> testPoints;                                          //Defining the vector keypoint for reading in the csv file with the keypoints
  cv::Mat img_keypoints_1;                                                  //Only used for vizualization

  stringstream tt;
  stringstream ll;
  
  tt << "Data/Keypoints.csv";
  ll << "Keypoints";

  
  cv::FileStorage fs2(tt.str(), cv::FileStorage::READ);                     //Reading the keypoints saved in Data
  cv::FileNode kptFileNode = fs2[ll.str()]; 
  read(kptFileNode, testPoints);
  fs2.release();

  cv::Mat img_keypoints;
  drawKeypoints(image, testPoints, img_keypoints, Scalar(0, 0, 255));
  namedWindow( "Image with Keypoints", WINDOW_AUTOSIZE );                   //Change here to WINDOW_NORMAL to manually resize the window
  //cv::resizeWindow("Image with Keypoints", 720, 500);                     //uncomment here if you change above to window normal
  imshow("Image with Keypoints", img_keypoints);


  ///////////////////////////IN HERE YOU CAN SAVE THE CREATED IMAGES WITH KEYPOINTS//////////////////
  ///////////////////////////////////////////////////////////////////////////////////////////////////
  if (i == "notreshold" && treshold == 0){

    stringstream ss;
    ss << "Viz/KpointsDist" << a << ".jpg";

    imwrite( ss.str(), img_keypoints );
  }
  else{
    stringstream ss;
    ss << "Viz/KpointsDist" << a << "Tres" << treshold << ".jpg";

    imwrite( ss.str(), img_keypoints );
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////////////////////////
  //waitKey(0);
}
  
