/* It first goes to runCreatingMatrix. That function loops over all possible keypoints*/
/*In MeanDistance it loops over all possible images*/


double MeanDistance(int &j, int &nimages, vector<cv::Mat> &descriptors);


void runCreatingMatrix(vector< double> &d, int &x, int &y, int nimages, vector<cv::Mat> &descriptors){
  cout << "Please wait, this process takes a while" << endl;

  int numberOfKeypoints = x*y;


  cout << numberOfKeypoints << endl;
  for (int i = 0; i < numberOfKeypoints; ++i)
  {
    d.push_back(MeanDistance(i, nimages, descriptors));

  }
}


double MeanDistance(int &j, int &nimages, vector<cv::Mat> &desc){ 
  std::vector<cv::Mat> descriptors(nimages);
  cv::Mat mean;


    for (int i = 0; i < nimages; ++i) 
    {
        descriptors[i] = desc[i].row(j); //Push back all the descriptors of all images for that particular keypoint Size of descripto 48x624
    }

  meanValue(descriptors, mean); 


  vector<double> d(nimages);

        for (int i = 0; i < nimages; ++i)
        {
          d[i] = distance(descriptors[i], mean);
        }
  
  double sum_of_elems;
  sum_of_elems = 0;
  std::for_each(d.begin(), d.end(), [&] (double n) {
  sum_of_elems += n;}
  );
  // cout << "j: " << j << endl;
  return sum_of_elems/nimages;
}


