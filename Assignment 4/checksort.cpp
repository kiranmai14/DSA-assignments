#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <unistd.h>
#include <climits>

using namespace std;

int main(int argc, char **argv)
{
	string infile = string(argv[1]);
	ifstream myFile(infile);
	string temp;
	long prev = INT_MIN;
	bool result = false;
	int count = 0;
	long curr;
	while (getline(myFile, temp, ','))
	{
		count++;
		curr = stol(temp);
		if(prev>curr){result=true;break;}
		prev = curr;
	}

	if (!result){
		cout << "Sorted" << endl;
		cout << "Number of numbers: " << count << endl;
		}
	else{
		cout << "Not sorted" << endl;
		cout<< "At: "<< prev<< ","<<curr;
	}	
	return 0;
}
