using namespace std;
using namespace cv;




void reStructure(){
	 vector<cv::KeyPoint> keypoints;


  	stringstream ss;
  	ss << "Data1/Keypoints";


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
       	stringstream tt;
  	  	stringstream ll;
  	  	stringstream pp;
        string aux;
        aux.append(dirName);
        aux.append(imgName);

        cout << imgName << endl;

        tt << "Data1/Keypoints/" << imgName;
  	  	ll << imgName;


  	  	std::string str(ll.str());

    		str.resize(str.size()-4);

  	  	cv::FileStorage fs2(tt.str(), cv::FileStorage::READ);                     //Reading the keypoints saved in Data
  	  	cv::FileNode kptFileNode = fs2[str]; 
  	  	read(kptFileNode, keypoints);
  	  	fs2.release();

  			vector< vector<double> > data;

  			for (unsigned int i = 0; i < keypoints.size(); ++i)
  			{	
  				vector<double> d;
  				Point2f p = keypoints[i].pt;
  				d.push_back(p.x);
  				d.push_back(p.y);
  				data.push_back(d);
  			}

  			pp << "Keypoints1/" << ll.str();
  			dump(pp.str(), data);

            }
      }
      closedir (dir);
    } 
    else {
      cout<<"not present"<<endl;
     }
}
