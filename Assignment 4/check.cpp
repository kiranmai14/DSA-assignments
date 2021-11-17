#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <sstream>
#include <math.h>
#include <algorithm>
using namespace std;

#define INP_FILE "input100000.txt"
#define OUT_FILE "outc100000.txt"

long long convertTolong(string num)
{
    stringstream con(num);
    long long x = 0;
    con >> x;
    return x;
}
int main()
{
    string data = "";
    ifstream infile;
    infile.open(INP_FILE, ios::in);
    infile >> data;
    infile.close();
    vector<long long> v;

    stringstream linestream(data);
    string value;
    while (getline(linestream, value, ','))
    {
        v.push_back(convertTolong(value));
    }

    sort(v.begin(), v.end());
    ofstream outfile;
    string name = OUT_FILE;
    outfile.open(name, ios::out);

    
    for (int i=0;i<v.size()-1;i++)
    {
        outfile << to_string(v[i]) + ",";
    }
    outfile << to_string(v[v.size()-1]);
    outfile.close();
}