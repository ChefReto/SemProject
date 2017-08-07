/*Returns the mean from a bunch of descriptors*/

void meanValue(const std::vector<cv::Mat> &descriptors, cv::Mat &mean)
{

    if(descriptors.empty()) return;

    if(descriptors.size() == 1)
    {
        mean = descriptors[0].clone();
        return;
    }
    //binary descriptor
    if (descriptors[0].type()==CV_8U ){
        //determine number of bytes of the binary descriptor
        int L= 48;// change to 32 if orb
        vector<int> sum( L * 8, 0);
   
        for(size_t i = 0; i < descriptors.size(); ++i)
        {
            const cv::Mat &d = descriptors[i];
            const unsigned char *p = d.ptr<unsigned char>();

            for(int j = 0; j < d.cols; ++j, ++p)
            {
                if(*p & (1 << 7)) ++sum[ j*8     ];
                if(*p & (1 << 6)) ++sum[ j*8 + 1 ];
                if(*p & (1 << 5)) ++sum[ j*8 + 2 ];
                if(*p & (1 << 4)) ++sum[ j*8 + 3 ];
                if(*p & (1 << 3)) ++sum[ j*8 + 4 ];
                if(*p & (1 << 2)) ++sum[ j*8 + 5 ];
                if(*p & (1 << 1)) ++sum[ j*8 + 6 ];
                if(*p & (1))      ++sum[ j*8 + 7 ];
            }
        }

        mean = cv::Mat::zeros(1, L, CV_8U);
        unsigned char *p = mean.ptr<unsigned char>();

        const int N2 = (int)descriptors.size() / 2 + descriptors.size() % 2;
        for(size_t i = 0; i < sum.size(); ++i)
        {
            if(sum[i] >= N2)
            {
                // set bit
                *p |= 1 << (7 - (i % 8));
            }

            if(i % 8 == 7) ++p;
        }
    }
    //non binary descriptor
    else{
        assert(descriptors[0].type()==CV_32F );//ensure it is float

        mean.create(1, descriptors[0].cols,descriptors[0].type());
        mean.setTo(cv::Scalar::all(0));
        float inv_s =1./double( descriptors.size());
        for(size_t i=0;i<descriptors.size();i++)
            mean +=  descriptors[i] * inv_s;
    }
}
