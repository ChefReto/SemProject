//Norm


void norm(vector<double> a){
	float value = 0.0;
	for(unsigned int i = 0; i < a.size(); i++) value += a[i] * a[i];
	value = sqrt(value);
	
	for (unsigned int i = 0; i < a.size(); ++i)
	{
		a[i] = a[i]/a[a.size()-1];
			}
	dump2("Vector/normalizedvector.txt", a);

}