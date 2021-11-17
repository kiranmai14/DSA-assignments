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

#define FILE_SIZE 65536
#define K_FILES 8192

#define INP_FILE "input1000000.txt"
#define OUT_FILE "out1000000.txt"

long long no_of_iterations;
long long no_of_files;

struct heapele
{
    long long num;
    long long index;
};
long long convertTolong(string num)
{
    stringstream con(num);
    long long x = 0;
    con >> x;
    return x;
}
void printArray(vector<struct heapele> v)
{
    for (int i = 0; i < v.size(); ++i)
        cout << v[i].num << " ";
 
    cout << "\n";
}
void swap(struct heapele **p, struct heapele **q)
{
    struct heapele **temp = p;
    p = q;
    q = temp;
}
void min_heapify(vector<struct heapele> &v, long long i, long long size)
{
    long long l = 2 * i + 1;
    long long r = 2 * i + 2;
    long long smallest = i;
    if (l < size && v[l].num < v[i].num)
        smallest = l;
    if (r < size && v[r].num < v[smallest].num)
        smallest = r;
    if (smallest != i)
    {
        swap(v[i], v[smallest]);
        min_heapify(v, smallest, size);
    }
}
void build_heap(vector<struct heapele> &v)
{
    long long size = v.size();
    for (long long i = size / 2 - 1; i >= 0; i--)
    {
        min_heapify(v, i, size);
    }
}
void insert(vector<struct heapele> &v, long long num, long long index)
{
    struct heapele ele;
    ele.index = index;
    ele.num = num;
    v.push_back(ele);
    long long i = v.size() - 1;
    long long p = (v.size() - 2) / 2;
    while (p >= 0 && v[p].num > v[i].num)
    {
        swap(v[p], v[i]);
        i = p;
        p = (p - 1) / 2;
    }
}
struct heapele extract_min(vector<struct heapele> &v)
{
    struct heapele m = v[0];
    swap(v[0], v[v.size() - 1]);
    v.erase(v.end() - 1);
    min_heapify(v, 0, v.size());
    return m;
}
void generateFiles()
{
    vector<long long> result;
    string data;
    ifstream infile;
    infile.open(INP_FILE, ios::in);
    infile >> data;
    infile.close();

    stringstream linestream(data);
    string value;
    long long count = 0;
    string fname = "/home/kiranmai/IIIT/DSA/DSA assignments/Assignment 4/files/f";
    no_of_files = 0;
    ofstream outfile;
    bool flag = 0;
    vector<long long> v;
    while (getline(linestream, value, ','))
    {
        if (count == 0)
        {
            flag = 0;
            string name = fname + to_string(no_of_files) + ".txt";
            outfile.open(name, ios::out);
        }
        v.push_back(convertTolong(value));
        count++;
        if (count == FILE_SIZE)
        {
            sort(v.begin(), v.end());
            for (auto val : v)
            {
                outfile << to_string(val) + ",";
            }
            outfile.close();
            count = 0;
            no_of_files++;
            flag = 1;
            v.clear();
        }
    }
    if (!flag)
    {
        sort(v.begin(), v.end());
        for (auto val : v)
        {
            outfile << to_string(val) + ",";
        }
        outfile.close();
        no_of_files++;
    }
}
void generateRandom()
{
    srand((unsigned)time(0));
    ofstream outfile;
    outfile.open("test.txt", ios::out);
    int randomNumber;
    for (int index = 0; index < 511; index++)
    {
        randomNumber = (rand() % 4096) + 1;
        outfile << randomNumber << ',';
    }
    randomNumber = (rand() % 100) + 1;
    outfile << randomNumber;
    outfile.close();
}
int intlog(double base, double x)
{
    return ceil(log(x) / log(base));
}

void k_way_merge()
{
    long long file_no = 0;
    ifstream infile[K_FILES];
    int lendigit[K_FILES] = {0};
    string fname = "/home/kiranmai/IIIT/DSA/DSA assignments/Assignment 4/files/f";
    // no_of_iterations = 1;
    while ((no_of_files - file_no) > K_FILES)
    {
        vector<struct heapele> heap;
        for (int i = 0; i < K_FILES; i++)
        {
            string name = fname + to_string(file_no) + ".txt";
            infile[i].open(name, ios::in);
            string data;
            infile[i] >> data;

            stringstream linestream(data);
            string value;
            getline(linestream, value, ',');
            lendigit[i] = value.size() + 1;

            struct heapele ele;
            ele.index = i;
            ele.num = convertTolong(value);

            heap.push_back(ele);
            file_no++;
        }
        build_heap(heap);
        string name = fname + to_string(no_of_files) + ".txt";
        no_of_files++;
        ofstream outfile;
        outfile.open(name, ios::out);
        while (heap.size() > 0)
        {
            struct heapele ele = extract_min(heap);
            outfile << to_string(ele.num) << ",";
            long index = ele.index;

            string data = "";
            infile[index].seekg(lendigit[index], infile[index].beg);
            if (infile[index].peek() == EOF)
            {
                infile[index].close();
                continue;
            }
            infile[index] >> data;

            string value;
            stringstream linestream(data);
            getline(linestream, value, ',');

            lendigit[index] += value.size() + 1;
            insert(heap, convertTolong(value), index);
        }
        outfile.close();
    }
    long rem = no_of_files - file_no;
    vector<struct heapele> heap;
    for (int i = 0; i < rem; i++)
    {
        string name = fname + to_string(file_no) + ".txt";
        infile[i].open(name, ios::in);
        string data;
        infile[i] >> data;

        stringstream linestream(data);
        string value;
        getline(linestream, value, ',');
        lendigit[i] = value.size() + 1;

        struct heapele ele;
        ele.index = i;
        ele.num = convertTolong(value);

        heap.push_back(ele);
        file_no++;
    }
    build_heap(heap);
    no_of_files++;
    fname = "/home/kiranmai/IIIT/DSA/DSA assignments/Assignment 4/";
    string name = fname + OUT_FILE;
    ofstream outfile;
    outfile.open(name, ios::out);
    while (heap.size() > 0)
    {
        struct heapele ele = extract_min(heap);

        long index = ele.index;

        string data = "";
        infile[index].seekg(lendigit[index], infile[index].beg);
        if (infile[index].peek() == EOF && heap.size() == 0)
        {
            outfile << to_string(ele.num);
        }
        else
        {
            outfile << to_string(ele.num) << ",";
        }
        if (infile[index].peek() == EOF)
        {
            infile[index].close();
            continue;
        }
        infile[index] >> data;

        string value;
        stringstream linestream(data);
        getline(linestream, value, ',');

        lendigit[index] += value.size() + 1;
        insert(heap, convertTolong(value), index);
    }
}
int main()
{
    generateFiles();
    k_way_merge();
}
