#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

void printArray(vector<long long> v)
{
    for (int i = 0; i < v.size(); ++i)
        cout << v[i] << " ";
    cout << "\n";
}
void swap(long long **p, long long **q)
{
    long long **temp = p;
    p = q;
    q = temp;
}
void min_heapify(vector<long long> &v, long long i, long long size)
{
    long long l = 2 * i + 1;
    long long r = 2 * i + 2;
    long long smallest = i;
    if (l < size && v[l] < v[i])
        smallest = l;
    if (r < size && v[r] < v[smallest])
        smallest = r;
    if (smallest != i)
    {
        swap(v[i], v[smallest]);
        min_heapify(v, smallest, size);
    }
}
void build_heap(vector<long long> &v)
{
    long long size = v.size();
    for (long long i = size / 2 - 1; i >= 0; i--)
    {
        min_heapify(v, i, size);
    }
}
// void heapSort(vector<long long> &v)
// {
//     build_heap(v);
//     printArray(v);
//     long long size = v.size() - 1;
//     for (long long i = size; i > 0; i--)
//     {
//         swap(v[i], v[0]);
//         min_heapify(v, 0, i);
//     }
// }
void insert(vector<long long> &v, long long num)
{
    v.push_back(num);
    long long i = v.size() - 1;
    while (i >= 0 && v[i / 2] > v[i])
    {
        swap(v[i / 2], v[i]);
        i = i / 2;
    }
}
long long extract_min(vector<long long> &v)
{
    long long m = v[0];
    swap(v[0], v[v.size() - 1]);
    v.erase(v.end() - 1);
    min_heapify(v, 0, v.size());
    return m;
}
int main()
{
    // srand((unsigned)time(0));
    // ofstream outfile;
    // outfile.open("test.txt", ios::out);
    // int randomNumber;
    // for (int index = 0; index < 9; index++)
    // {
    //     randomNumber = (rand() % 100) + 1;
    //     outfile << randomNumber << ',';
    // }
    // randomNumber = (rand() % 100) + 1;
    // outfile << randomNumber;
    // outfile.close();

    vector<long long> result;
    string data;
    ifstream infile;
    infile.open("test.txt", ios::in);
    infile >> data;
    infile.close();
    stringstream linestream(data);
    string value;
    while (getline(linestream, value, ','))
    {
        stringstream con(value);
        long long x = 0;
        con >> x;
        cout << x << " ";
        result.push_back(x);
    }
    cout << endl;
    build_heap(result);
}