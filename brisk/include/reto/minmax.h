/*This function returns the min or max element of a vector*/
/*Pass the vector and the string "min" or "max"*/

using namespace std;


double MinMax(vector<double> &data, const string i){
	double minmax;

	if(i == "min"){
		auto smallest = std::min_element(std::begin(data), std::end(data));
		minmax = (double)*smallest;
	}
	else{
		auto biggest = std::max_element(std::begin(data), std::end(data));
		minmax = (double)*biggest;
	}
	return minmax;
}
