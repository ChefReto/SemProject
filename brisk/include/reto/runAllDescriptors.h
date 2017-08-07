
using namespace std;


void findMostStableKeypoints(const string &dirname, cv::Mat &image);
void insertKeypoint(cv::Mat &image,int &x,int &y, int &a, vector <KeyPoint > &Keypoints);
void ReadImageAncComputeDescriptors(int &i,vector<cv::Mat>  &descriptors, vector <KeyPoint > &Keypoints, const string &dirname);
void insertKeypointTreshold(cv::Mat image, int &x,int &y, vector<double> &data, double treshold, int &a, vector<double> &v, const string &dirname);
void computingDescriptors(cv::Mat image, int i,vector<cv::Mat>  &descriptors, vector <cv::KeyPoint > &Keypoints);




void runAllDescriptors(){
	
 stringstream ss;

 ss << "FilterImages/images/AMOS_Data/FD";

 string picName = "FilterImages/images/AMOS_Data/FD/00003553/2014.02/20140201_001308.jpg";   //Choose here the whole path to the image, this one is used for vizualizations
 Mat image2= imread(picName);
 Mat image = reSize(image2);                                                                 //Resize to 256x256

 string dirName = ss.str();
 DIR *dir;
 dir = opendir(dirName.c_str());
 string imgName;
 struct dirent *ent;


 if (dir != NULL) {
 while ((ent = readdir (dir)) != NULL) {
       imgName= ent->d_name;
       //I found some . and .. files here so I reject them.
       if(imgName.compare(".")!= 0 && imgName.compare("..")!= 0)
       {
         string aux;
         aux.append(imgName);
         findMostStableKeypoints(imgName, image);
       }
  }
  closedir (dir);
} 
}


void findMostStableKeypoints(const string &dirname, cv::Mat &image){
  int a = 1;                                  //Distance from one keypoint to the other. Feel free to choose here one of your choice
  int nimages;
  vector <cv::Mat> descriptors(53824); 
  vector <cv::KeyPoint> Keypoints;
  vector <double> data;
  int x;
  int y;

  int tres = 300;                               //Best keypoints

  insertKeypoint(image, x, y, a, Keypoints);
  ReadImageAncComputeDescriptors(nimages, descriptors, Keypoints, dirname); 
  runCreatingMatrix(data, x, y, nimages, descriptors); 


  vector<double> v(x*y);
  v = data;
  sort1(data, v);                             
  norm(v);
  insertKeypointTreshold(image, x, y, data, tres, a, v, dirname);

}



/*This function inserts all keypoints in a grid fashion way*/
void insertKeypoint(cv::Mat &image,int &x,int &y, int &a, vector <KeyPoint > &Keypoints){

  int rows = image.rows;
  int cols = image.cols;

  int d = 40;                                                               //Boundaries
  int p = 0;
  int z = 0;

  for (int x = d; x < cols-d; x+=a)
  { 
    z = 0;
    for (int y = d; y < rows-d; y+=a)
    {
      Keypoints.push_back(KeyPoint(x,y,4,-1,0,0,-1));                       // Default Scales 
      z++;
          }
    p++;
  }
  SavingCSVFIle(Keypoints, "Keypoints");                                                 //Saving the Keypoints to a file
  x = p;
  y = z;
  cout << endl << p*z << " Keypoints" << endl;
  cout << p << " Points in x direction"<< endl;
  cout << z << " Points in y direction"<< endl;
}


/*This function reads all the images in the folder*/
/*It first reads an image. The computingDescriptor receivs the image, the iteration number, and the descriptor vector and computes the BRISK descriptors*/
void ReadImageAncComputeDescriptors(int &i,vector<cv::Mat>  &descriptors, vector <KeyPoint > &Keypoints, const string &dirname){
     stringstream ss;
     stringstream tt;
     ss << "FilterImages/images/AMOS_Data/FD/" << dirname << "/2014.02/";
     tt << "FilterImages/images/AMOS_Data/FD/" << dirname << "/2014.08/";

     string dirName = ss.str();
     DIR *dir;
     dir = opendir(dirName.c_str());
     string imgName;
     struct dirent *ent;

     cout << dirName << endl;
     if (dir != NULL) {
     i = 0;
     while ((ent = readdir (dir)) != NULL) {
           imgName= ent->d_name;
           //I found some . and .. files here so I reject them.
           if(imgName.compare(".")!= 0 && imgName.compare("..")!= 0)
           {
             string aux;
             aux.append(dirName);
             if(imgName == "mask.png"){
              //Do nothing
             }
             else{
             aux.append(imgName);
             cout << "Computing descriptors of image: " << aux << endl;
             Mat image2= imread(aux);
             // Mat image = reSize(image2);
             computingDescriptors(image2, i, descriptors, Keypoints);
             i ++;
             if(i == 250){break;}
             }
           }
      }
      closedir (dir);
    } 


    string dirName2 = tt.str();
    DIR *dir2;
    dir2 = opendir(dirName2.c_str());  
    string imgName2;
    struct dirent *ent2;


    if (dir2 != NULL){
      while (( ent2 = readdir (dir2)) != NULL){
        imgName2= ent2 -> d_name;
        if(imgName2.compare(".")!= 0 && imgName2.compare("..")!= 0)
           {
             string aux;
             aux.append(dirName2);
             if(imgName2 == "mask.png"){
              //Do nothing
             }
             else{
             aux.append(imgName2);
             cout << "Computing descriptors of image: " << aux << endl;
             Mat image2= imread(aux);
             // Mat image = reSize(image2);
             computingDescriptors(image2, i, descriptors, Keypoints);
             i ++;
             if(i == 500){break;}
             }
           }
      }
    closedir (dir2);
    }
    else {
      cout<<"not present"<<endl;
     }
     cout << i << " Images loaded" << endl;
}



/*This function inserts keypoints only if it satisfies a certain treshold*/
using namespace std;

void insertKeypointTreshold(cv::Mat image, int &x,int &y, vector<double> &data, double treshold, int &a, vector<double> &v, const string &dirname){
  vector <KeyPoint > Keypoints;

  int rows = image.rows;
  int cols = image.cols;
  
  int d = 40;  // Attention here, Orb defaults radius is bigger than 15 so an error will occur
  int p = 0;
  int z = 0;
  int jj = 0;
  double b = v[treshold];

  cout << treshold << endl;

  stringstream ss;

  ss << "Keypoints_" << treshold;

  stringstream pp;

  pp << "Keypoints";
  


  for (int x = d; x < cols-d; x+=a)
  { 
    z = 0;
    for (int y = d; y < rows-d; y+=a)                                    
    { 
      if ( data[jj] < b){
      Keypoints.push_back(KeyPoint(x,y,4,-1,0,0,-1));}
      z++;
      jj++;
          }
    p++;
  }
  SavingCSVFIle(Keypoints,ss.str());
  SavingCSVFIle(Keypoints,pp.str());
}


void computingDescriptors(cv::Mat image, int i,vector<cv::Mat>  &descriptors, vector <cv::KeyPoint > &Keypoints){

  cv::Mat imgGray;                                                    //Gray Image
  cv::Mat descriptors1;                                               //Descriptor
  cv::Ptr < cv::DescriptorExtractor > descriptorExtractor;
  vector<cv::KeyPoint> testPoints;                                    //Defining the vector keypoint for reading in the csv file with the keypoints




  cv::cvtColor(image, imgGray, CV_BGR2GRAY);                          //Converting the input image from RGB to Grayscale


                        /*BRISK*/
  descriptorExtractor = new brisk::BriskDescriptorExtractor(true, true, brisk::BriskDescriptorExtractor::Version::briskV2); // Calling the Constructor
  descriptorExtractor = new brisk::BriskDescriptorExtractor();        //The default brisk descriptor extractor
  descriptorExtractor->compute(imgGray, Keypoints, descriptors1);     //Computing descriptors


                        /*SURF*/
  // cv::Ptr<cv::xfeatures2d::SURF> surf = cv::xfeatures2d::SURF::create();
  // cv::Mat mask;
  // surf->detectAndCompute(image, mask, Keypoints, descriptors1, true);


                        /*SIFT*/
  // cv::Ptr<cv::xfeatures2d::SIFT> sift = cv::xfeatures2d::SIFT::create();
  // cv::Mat mask;
  // sift->detectAndCompute(image, mask, Keypoints, descriptors1, true);



                       /*ORB*/
  // Ptr<FeatureDetector> detector = ORB::create();
  // Ptr<DescriptorExtractor> extractor = ORB::create();
  // extractor->compute(imgGray, Keypoints, descriptors1);











  // If you want to read the keypoints from a csv. file
  // stringstream tt;
  // stringstream ll;
  
  // tt << "Data/Keypoints.csv";
  // ll << "Keypoints";

  // // Reading the keypoints saved in Data
  // cv::FileStorage fs2(tt.str(), cv::FileStorage::READ);
  // cv::FileNode kptFileNode = fs2[ll.str()]; 
  // read(kptFileNode, testPoints);
  // fs2.release();
  
  descriptors[i] = descriptors1;                                      //Pushing back all the descriptor to the vector descriptors
                                      
  //SavingDescriptorFIle(descriptors1, i);                            //Saving descriptors in csv file

}
