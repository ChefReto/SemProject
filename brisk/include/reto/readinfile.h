/*This function reads in from txt file a single column with arbitrary many rows*/
#include <cassert>
#include <fstream>


using namespace std;


void ReadInFile(const string fname, vector<double> &d){
	
    ifstream infile(fname);
    double di;
    while(infile >> di) {
        d.push_back(di);
    }
}
