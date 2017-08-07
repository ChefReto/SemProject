/*This function saves the keypoints to a csv file*/
using namespace cv;


void SavingCSVFIle(vector <KeyPoint > Keypoints, const string &name){
 
  stringstream oo;
  stringstream pp;
  oo << "Data/" <<name <<".csv";
  pp << name;
  FileStorage fs1(oo.str(), FileStorage::WRITE);
  write(fs1, pp.str(), Keypoints);
  fs1.release();
}
