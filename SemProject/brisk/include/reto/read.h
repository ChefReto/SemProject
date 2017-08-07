/*This functions reads in a two dimensional vector from txt file*/

#include <cassert>
#include <fstream>


using namespace std;

void read(const string fname, vector< vector<double> >& data){



  for (int i = 0; i < 38; ++i)
  {
    vector<double> b(51);
    for (int j = 0; j < 51; ++j)
    {
      b[j] = 0.0;
      
    }
    data.push_back(b);

  }
    
    unsigned int n = data.size();//data[0].size();
    ifstream infile(fname.c_str());
    assert(infile.good());

    
    for (unsigned int line = 0; line < n; line ++) {
        for (unsigned int i = 0; i < data[0].size(); i++) {
            infile >> data[line][i];
        }
    }
}
