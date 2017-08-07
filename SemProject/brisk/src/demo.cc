// Created by Reto

#include "brisk/libraries.h"                          						//Loads all the libraries needed to run this code
using namespace std;
using namespace cv;

// Change in function computingDescriptors.h which descriptor you want to use, e.g. brisk, surf, sift etc.

int main()
{
  int a = 2;																	//Distance from one keypoint to the other. Feel free to choose here one of your choice
  int nimages; 
  string dirname;
  dirname = "00001110";															//Choose here the directory
  int IntensityValue = 80;													    //Choose here the gray-intensity treshold
  double PercRemove = 0.3;														// Choose here the percentage of dark images you want to keep. For example, if more than 30% of the keypoints are darker than the treshold, that image will not be keeped in the folder 


  ////////////////////////*Filter here all the images that are too dark*////////////////////////////////////////////////
  ////////////////////////Comment out this part if not need/////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  mkdir("FilterImages", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
  mkdir("FilterImages/images", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
  mkdir("FilterImages/images/AMOS_day", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
  filterimages(a, nimages, dirname, IntensityValue, PercRemove);
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	
    

  //////////////////////////////////////Choose here one image int the folder for vizualizations///////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  string dirName = "FilterImages/images/AMOS_day/00001110/2014.02/20140201_121056.jpg";   //Choose here the whole path to the image, this one is used for vizualizations
  Mat image= imread(dirName);
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  int x;                                          							//Number of keypoints in x direction
  int y;                                          							//Number of keypoints in y direction
  vector <cv::Mat> descriptors(100000);                    				    //Preallocate memory
  vector <cv::KeyPoint > Keypoints;


  vector<double> d;                             							//The error ej is stored in this vector
  vector<double> data;                            							//The error ej is stores in this vector. This is used to run the code without loading all the images
  double treshold;                               							//Treshold

  insertKeypoint(image, x, y, a, Keypoints);                 				//This function creates vector <KeyPoint > Keypoints;  
  drawKeypointonImage(image, a, "notreshold", 0);               			//This function is used for plotting and saving the images 
  ReadImageAncComputeDescriptors(nimages, descriptors, Keypoints, dirname); //Have a look in ReadImage.h
  runCreatingMatrix(d, x, y, nimages, descriptors);             			//This function computes the error of each keypoint
  dump2("Vector/vector.txt", d);                        					//It saves the error in .txt file. For manipulations
  ReadInFile("Vector/vector.txt", data);                    				//It reads in the .txt file before

  vector<double> v(x*y);
  v = data;
  sort1(data, v);															//Create a copy v but sorted in ascending order
  norm(v);


  cout << "Choose the number N of points which are the most stable. Between " << 0; 
  cout << " and " << v.size() << " and press enter." << endl;
  cin >> treshold;
  cout << "You entered " << treshold << endl;


  insertKeypointTreshold(image, x, y, data, treshold, a, v);
  drawKeypointonImage(image, a, "Treshold", treshold);

 
  fastdetector(image);                            							// This function is used to detect FAST keypoints

  return 0;
}