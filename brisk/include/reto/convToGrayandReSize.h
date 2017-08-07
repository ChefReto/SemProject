// This function reads in all folder from "FilterImages/images/AMOS_Data/FD/" and further all images form those folders.
// Once read in it converts all images to gray and resizes to 256x256

void convToGrayandReSize(cv::Mat image, const string dirname, const string imgname, const string dirName);
void readConvertResize(const string &dirname);




void readallDirs(){
     stringstream ss;
     ss << "FilterImages/images/AMOS_Data/FD/";

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
             aux.append(dirName);
             cout << "Writing images of dir: " << imgName << endl;
             readConvertResize(imgName);
           }
      }
      closedir (dir);
    } 

}



void readConvertResize(const string &dirname){
     stringstream ss;
     stringstream tt;
     ss << "FilterImages/images/AMOS_Data/FD/" << dirname << "/2014.02/";
     tt << "FilterImages/images/AMOS_Data/FD/" << dirname << "/2014.08/";

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
             aux.append(dirName);
             aux.append(imgName);
             Mat image= imread(aux);
             convToGrayandReSize(image, dirName, imgName, dirname);
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
             aux.append(imgName2);
             Mat image= imread(aux);
             convToGrayandReSize(image, dirName2, imgName2, dirname);
           }
      }
    closedir (dir2);
    }
    else {
      cout<<"not present"<<endl;
     }
}



void convToGrayandReSize(cv::Mat image, const string dirname, const string imgname, const string dirName){
	stringstream oo;
	oo <<  "Grayimages/" << dirName;
	const string name = oo.str();
	mkdir(name.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

	const int kNewWidth = 256;
	const int kNewHeight = 256;
	cv::Mat new_image;
	cv::Mat imgGray;

	stringstream pp;
	pp << "Grayimages/" << dirName << "/"<< imgname;

	resize(image, new_image, cvSize(kNewWidth, kNewHeight));
	cv::cvtColor(new_image, imgGray, CV_BGR2GRAY); 
	imwrite(pp.str(), imgGray);
}