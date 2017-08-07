/*This function writes a vector< vector<double>  to txt file*/
#include <cassert>
#include <fstream>


using namespace std;


void dump(const string fname, vector< vector<double> >& data){
    
    unsigned int n = data[0].size();
    ofstream fout(fname.c_str());
    assert(fout.good());
    for (unsigned int i = 0; i < data.size(); i ++) {
        for (unsigned int line = 0; line < n; line++) {
        	if(line == 0){
            fout << data[i][line] << ",";}
            else{
            fout << data[i][line];
            }
        }
        fout << endl;
    }
}
