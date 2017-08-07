/*This function stores a vector<double> in a txt file*/
#include <cassert>
#include <fstream>

using namespace std;

void dump2(const string fname, vector<double> & data){
    
    unsigned int n = data.size();
    ofstream fout(fname.c_str());
    assert(fout.good());
    for (unsigned int line = 0; line < n; line ++) {
            fout << data[line] << " ";
        fout << endl;
    }
}
