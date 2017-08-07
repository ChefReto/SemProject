void vizualization(cv::Mat image2){
  
  cv::Mat image = reSize(image2);
  vector<cv::KeyPoint> testPoints;                                          //Defining the vector keypoint for reading in the csv file with the keypoints

  stringstream tt;
  stringstream ll;
  
  tt << "Data/Keypoints/Keypoints_00006469.csv";
  ll << "Keypoints_00006469";
  

  cout << tt.str() << endl;
  cout << ll.str() << endl;
  cv::FileStorage fs2(tt.str(), cv::FileStorage::READ);                     //Reading the keypoints saved in Data
  cv::FileNode kptFileNode = fs2[ll.str()]; 
  read(kptFileNode, testPoints);
  fs2.release();

  cout << testPoints.size() << endl;
  cv::Mat img_keypoints;
  drawKeypoints(image, testPoints, img_keypoints, Scalar(0, 0, 255));
  namedWindow( "Image with Keypoints", WINDOW_AUTOSIZE );                   //Change here to WINDOW_NORMAL to manually resize the window
  imshow("Image with Keypoints", img_keypoints);
  waitKey(0);	
  stringstream pp;
  pp << "Viz/" << ll.str() << ".jpg";
  imwrite(pp.str(),img_keypoints);
}


