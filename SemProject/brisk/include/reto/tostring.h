/*This function outputs to the console the float vectors to a string*/
#include <string>
#include <sstream>
#include <stdint.h>
#include <limits.h>

std::string toString(const cv::Mat &a)
{
  stringstream ss;
  const unsigned char *p = a.ptr<unsigned char>();
  
  for(int i = 0; i < a.cols; ++i, ++p)
  {
    ss << (int)*p << " ";
  }
  
  return ss.str();
}
