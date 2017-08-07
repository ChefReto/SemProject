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
             Mat image = reSize(image2);
             computingDescriptors(image, i, descriptors, Keypoints);
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
             cout << "Computing descriptors of image: " << aux << endl;
             Mat image2= imread(aux);
             Mat image = reSize(image2);
             computingDescriptors(image, i, descriptors, Keypoints);
             i ++;
             if(i == 1500){break;}
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
