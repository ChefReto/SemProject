    // This script is written for vizualizations


    using namespace std;
    using namespace cv;



    void viz(){


    string dirName = "FilterImages/images/AMOS_Data/FD/00008494/2014.08/20140801_044147.jpg";   //Choose here the whole path to the image, this one is used for vizualizations
    Mat image= imread(dirName);

    string dirname;
    dirname = "00008494";

    int a = 4;
    int x;                                          							//Number of keypoints in x direction
    int y;                                          							//Number of keypoints in y direction
    vector <cv::Mat> descriptors(100000);                    				    //Preallocate memory
    vector <cv::KeyPoint > Keypoints;
    
    
    vector<double> d;                             							//The error ej is stored in this vector
    vector<double> data;                            							//The error ej is stores in this vector. This is used to run the code without loading all the images
    double treshold;                               							//Treshold
    

    insertKeypoint(image, x, y, a, Keypoints);
    // drawKeypointonImage(image, a, "notreshold", 0);               			//This function is used for plotting and saving the images
    
    
    /////////////////////////////////////////Comment this out if you don't want to compute the descriptors again//////////////
    // //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    int nimages;
    ReadImageAncComputeDescriptors(nimages, descriptors, Keypoints, dirname); //Have a look in ReadImage.h
    cv::Size s = descriptors[1].size();
    cout << "s: " << s << endl;
    runCreatingMatrix(data, x, y, nimages, descriptors);             			//This function computes the error of each keypoint
    dump2("Vector/vector.txt", data);                        					//It saves the error in .txt file. For manipulations
    // // //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    

    ReadInFile("Vector/vector.txt", d);                    				//It reads in the .txt file before
    
    vector<double> v(x*y);
    v = d;
    sort1(d, v);															//Create a copy v but sorted in ascending order
    norm(v);
    
    
    cout << "Choose the number N of points which are the most stable. Between " << 0;
    cout << " and " << v.size() << " and press enter." << endl;
    cin >> treshold;
    cout << "You entered " << treshold << endl;
    
    
    insertKeypointTreshold(image, x, y, d, treshold, a, v, dirname);

    /////////////////////////////// Variance //////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // vector <cv::Mat> descriptorsvariance(100000);
    // vector<double> variancevector;  
    // vector <KeyPoint > KeypointsVariance;
    // insertKeypointTresholdVariance(image, x, y, d, treshold, a, v, dirname, KeypointsVariance);   
    // ReadImageAncComputeDescriptors(nimages, descriptorsvariance, KeypointsVariance, dirname);
    // cv::Size s = descriptorsvariance[1].size();
    // cout << "s: " << s << endl;
    // variance(variancevector, x, y, nimages, descriptorsvariance, treshold);
    // stringstream ss;
    // ss << "Vector/variancevector_" << treshold << "_" << dirname << "brisk_summer.csv";
    // dump2(ss.str(), variancevector);
    /////////////////////////////// Variance //////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



    drawKeypointonImage(image, a, "Treshold", treshold);
    
    
    // fastdetector(image);  

    } 

