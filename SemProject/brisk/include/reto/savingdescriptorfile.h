/*This function saves the keypoints to a csv file*/
#include <list>
#include <dirent.h>
#include <string.h>
#include <sstream>
#include <stdint.h>
#include <limits.h>


using namespace std;
using namespace cv;


void SavingDescriptorFIle(cv::Mat descriptors, int i){
 
  stringstream oo;
  stringstream pp;
  oo << "Data/descriptors" << i << ".csv";
  pp << "descriptors"  << i;


  cv::FileStorage fs1(oo.str(), FileStorage::WRITE);
  write(fs1, pp.str(), descriptors);

  fs1.release();
}
