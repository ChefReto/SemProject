#include <sys/stat.h>

int checkquality(const string dirname, const string datafile);
void filterimages(int &a, int &nimages, const string &dirname,int &IntensityValue, double &PercRemove, int &removed);
void cropimage(cv::Mat &image,const string datafile, const string dirname);
void CheckIntensity(cv::Mat image, int &a, const string &imagename, int &IntensityValue, double &PercRemove, int &removed);

using namespace cv;

void runAll(int &a, int &nimages,int &IntensityValue, double &PercRemove, int &removed, const string datafile){
	
	stringstream ss;

	ss << "images/AMOS_Data";


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
             if(checkquality(imgName, datafile) == 0){
             	cout << "Quality 0: This folder is not used" << endl;
             }
             else{
             filterimages(a, nimages, imgName,IntensityValue, PercRemove, removed);
             }
             
           }
      }
      closedir (dir);
    } 
}



/*This function reads the camreas.txt and check if the quality is 0, if quality is zero it returns a zero*/


int checkquality(const string dirname, const string datafile){
    std::string item_name;
    std::ifstream nameFileout;


    nameFileout.open(datafile);


    stringstream pp;

    pp << " " << dirname;

    while (nameFileout >> item_name)
    {   
        stringstream ss;
          std::getline(nameFileout, item_name);
          ss << item_name;
         

          if (ss.str() == pp.str()){  
            int i = 0;
            while(nameFileout >> item_name){
              stringstream tt;
              std::getline(nameFileout, item_name);
              tt << item_name;
              if (i == 0 ){
                if (item_name == " 0")
                {
                  return 0;
                }
              }
              i++;
              if(tt.str() == ""){
                break;
              }

            }
          }
    }
      
    nameFileout.close();
  return 1;

}



 

void filterimages(int &a, int &nimages, const string &dirname,int &IntensityValue, double &PercRemove, int &removed){


     int i;
     stringstream ss;
     stringstream tt;
     stringstream oo;
     stringstream ww;
     stringstream kk;

     ss << "images/AMOS_Data/" << dirname << "/2014.02/";
     tt << "images/AMOS_Data/" << dirname << "/2014.08/";

     oo <<  "FilterImages/images/AMOS_Data/" << dirname;
     const string name = oo.str();

     mkdir(name.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

     ww << oo.str() << "/2014.02/";
     kk << oo.str() << "/2014.08/";

     const string name1 = ww.str();
     mkdir(name1.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

     const string name2 = kk.str();
     mkdir(name2.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

   


     string dirName = ss.str();
     DIR *dir;
     dir = opendir(dirName.c_str());
     string imgName;
     struct dirent *ent;

     i = 0;
     if (dir != NULL) {

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
             cout << "Filtering image: " << aux << endl;
             Mat image= imread(aux);
             cropimage(image, "cameras.txt", dirname);
             stringstream ll;
             ll << ss.str() << imgName.c_str();
             CheckIntensity(image, a, ll.str(), IntensityValue, PercRemove, removed);
             i ++;
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
             cout << "Filtering image: " << aux << endl;
             Mat image= imread(aux);
             cropimage(image, "cameras.txt", dirname);
             stringstream pp;
             pp << tt.str() << imgName2.c_str();
             CheckIntensity(image, a, pp.str(),IntensityValue, PercRemove, removed);
             i ++;
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






void CheckIntensity(cv::Mat image, int &a, const string &imagename, int &IntensityValue, double &PercRemove, int &removed){
  cv::Mat imgGray;
  cv::cvtColor(image, imgGray, CV_BGR2GRAY); 




    int d = 16;               // This value is the image boudary and is also used in the other pipeline
    int rows = image.rows;
    int cols = image.cols;

    int i = 0;
    int j = 0;                                                               
 
    Scalar intensity;


  for (int x = d; x < cols-d; x+=a)
    { 
      for (int y = 10+d; y < rows-d-10; y+=a)
      {
          Scalar intensity = imgGray.at<uchar>(Point(x, y));
          i++;
          if(intensity[0] < IntensityValue){
            j++;
          }    
        }
    }

  stringstream ss;

  ss << "FilterImages/" << imagename;

  if((double)j/(double)i < PercRemove){ // "<" keep the light images // ">" keep the dark images
    imwrite(ss.str(), image);
    removed ++;
    // cout << endl <<  ss.str() << endl;
  }


}

