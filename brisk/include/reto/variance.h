double variance1(int &j, int &nimages, vector<cv::Mat> &descriptors,  double &treshold);
void insertKeypointTresholdVariance(cv::Mat image, int &x,int &y, vector<double> &data, double treshold, int &a, 
	vector<double> &v, const string &dirname,vector <KeyPoint > &Keypoints);


void variance(vector< double> &d, int &x, int &y, int nimages, vector<cv::Mat> &descriptors,  double &treshold){
	
	
  cout << "Please wait, this process takes a while" << endl;




  for (int i = 0; i < treshold; ++i)
  {	
    d.push_back(variance1(i, nimages, descriptors, treshold));
  }
}


double variance1(int &j, int &nimages, vector<cv::Mat> &desc,  double &treshold){ 
  std::vector<cv::Mat> descriptors(nimages);
  cv::Mat mean;


  // cv::Size s = desc[2].size();
  // double rows = s.height;
 
    for (int i = 0; i < nimages; ++i) 
    {	
    	// cout << "iii: " << i << endl;
        descriptors[i] = desc[i].row(j); //Push back all the descriptors of all images for that particular keypoint Size of descripto 48x624
    	// cout << "i: " << i << endl;
    }

  // cout << "Hello World 1" << endl;

  meanValue(descriptors, mean); 
  vector<double> d(nimages);

  vector<double> var(nimages);
  cv::Mat tempMat;

  for (int i = 0; i < nimages; ++i)
        { subtract(descriptors[i], mean, tempMat);
          double b = tempMat.dot(tempMat);
          var[i] = b;
  }
  double sum_of_elems;
  sum_of_elems = 0;
  std::for_each(var.begin(), var.end(), [&] (double n) {
  sum_of_elems += n;}
  );

  return sum_of_elems/nimages;
}


















void insertKeypointTresholdVariance(cv::Mat image, int &x,int &y, vector<double> &data, double treshold, int &a, 
	vector<double> &v, const string &dirname,vector <KeyPoint > &Keypoints){

  int rows = image.rows;
  int cols = image.cols;
  
  int d = 45; //15
  int p = 0;
  int z = 0;
  int jj = 0;
  double b = v[treshold];

  stringstream ss;

  ss << "Keypoints_" << treshold;

  stringstream pp;

  pp << "Keypoints";
  


  for (int x = d; x < cols-d; x+=a)
  { 
    z = 0;
    for (int y = d; y < rows-d; y+=a)                                    //10 is here the upper and lower boundary
    { 
      if ( data[jj] < b){
      Keypoints.push_back(KeyPoint(x,y,4,-1,0,0,-1));}
      z++;
      jj++;
          }
    p++;
  }

}
