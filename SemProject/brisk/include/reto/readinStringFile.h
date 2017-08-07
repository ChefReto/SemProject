
void readinStringFile(const string datafile, const string dirname, vector<int> &Tokens1, vector<int> &Tokens2,vector<int> &Tokens3,vector<int> &Tokens4){

		std::string item_name;
		std::ifstream nameFileout;

		std::vector<char> v;

		nameFileout.open(datafile);

		int Temp;
		int Temp2;
		int Temp3;
		int Temp4;
		

		stringstream pp;

		pp << " " << dirname;

		while (nameFileout >> item_name)
		{		
				stringstream ss;
			    std::getline(nameFileout, item_name);
			    ss << item_name;

			   
			    if (ss.str() == pp.str()){	
			    	int i = 0;
			    	while(nameFileout >> item_name){
			    		stringstream tt;
			    		std::getline(nameFileout, item_name);
			    		tt << item_name;


			    		if (i == 3 ){
			    			while(tt >> Temp)
						        Tokens1.push_back(Temp);
			    		}
			    		if (i == 4 ){
			    			while(tt >> Temp2)
						        Tokens2.push_back(Temp2);
			    		}
			    		if (i == 5 ){
			    			while(tt >> Temp3)
						        Tokens3.push_back(Temp3);
			    		}
			    		if (i == 6 ){
			    			while(tt >> Temp4)
						        Tokens4.push_back(Temp4);
			    		}
			    		i++;
			    		if(tt.str() == ""){
						  	break;
			    		}

			    	}
			    }
		}
			
		nameFileout.close();

}
