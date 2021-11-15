#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

int main()
{
    srand((unsigned)time(0));
    ofstream outfile;
    outfile.open("test.txt", ios::out);
    int randomNumber;
    for (int index = 0; index < 9; index++)
    {
        randomNumber = (rand() % 100) + 1;
        outfile << randomNumber << ',';
    }
    randomNumber = (rand() % 100) + 1;
    outfile << randomNumber;
    outfile.close();

    vector<string> result;
    string data;
    ifstream infile;
    infile.open("test.txt", ios::in);
    infile >> data;
    infile.close();
    while (1)
    {
        string substr;
        // getline(data, substr, ',');
        result.push_back(substr);
    }
}