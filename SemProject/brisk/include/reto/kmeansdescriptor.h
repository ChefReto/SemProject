
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
using namespace cv;
using namespace std;
// static void help()
// {
//     cout << "\nThis program demonstrates kmeans clustering.\n"
//             "It generates an image with random points, then assigns a random number of cluster\n"
//             "centers and uses kmeans to move those cluster centers to their representitive location\n"
//             "Call\n"
//             "./kmeans\n" << endl;
// }
int KmeansDescriptor(vector <KeyPoint > Keypoints, vector<cv::Mat>  &descriptors)
{


//     Mat points();

//     for (unsigned int i = 0; i < Keypoints.size(); ++i)
//     {
//       points[i] = Keypoints[i].pt;
//     }


//     Mat centers;


     
// // kmeans(points, clusterCount, labels,TermCriteria( TermCriteria::EPS+TermCriteria::COUNT, 10, 1.0), 3, KMEANS_PP_CENTERS, centers);

// // imshow("clusters", img);



// Create the BOW object with K classes

int K = 10;
BOWKMeansTrainer bow(K);

for(unsigned int k = 0; descriptors.size(); k++ )
{
    // Convert characteristics vector to float
    // This is require by BOWTrainer class
    Mat descr;
    descriptors[k].convertTo(descr, CV_32F);
    // Add it to the BOW object
    bow.add(descr);
}
// Perform the clustering of stored vectors
Mat voc = bow.cluster();

  return 0;
}

