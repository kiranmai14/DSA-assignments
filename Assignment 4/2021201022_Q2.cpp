#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <sys/types.h>
#include <sys/stat.h>
#include <filesystem>
#include <ctime>
#include <unistd.h>

using namespace std;

#define FILE_SIZE 100000
#define K_FILES 1000

long long no_of_iterations;
long long no_of_files;
string inp_file;
string out_file;
string cwd;

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
    ifstream infile(inp_file);

    string value;
    long long count = 0;
    string fname = cwd + "/files/f";
    no_of_files = 0;
    ofstream outfile;
    bool flag = 0;
    vector<long long> v;
    while (getline(infile, value, ','))
    {
        if (count == 0)
        {
            flag = 0;
            string name = fname + to_string(no_of_files) + ".txt";
            outfile.open(name, ios::out);
            if (!outfile)
            {
                cout << no_of_files;
                cout << "unable to open file!";
                exit(-1);
            }
        }
        v.push_back(stoll(value));
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
    infile.close();
}
void k_way_merge()
{
    long long file_no = 0;
    ifstream *infile = new ifstream[K_FILES];
    vector<long long> lendigit(K_FILES);
    string fname = cwd + "/files/f";
    vector<string> filenames(K_FILES);
    while ((no_of_files - file_no) > K_FILES)
    {
        vector<struct heapele> heap;
        for (long long i = 0; i < K_FILES; i++)
        {
            string name = fname + to_string(file_no) + ".txt";
            infile[i].open(name, ios::in);
            filenames[i] = name;

            string value;
            getline(infile[i], value, ',');
            lendigit[i] = value.size() + 1;

            struct heapele ele;
            ele.index = i;
            ele.num = stoll(value);

            heap.push_back(ele);
            file_no++;
        }
        build_heap(heap);
        string name = fname + to_string(no_of_files) + ".txt";
        no_of_files++;
        ofstream outfile;
        outfile.open(name, ios::out);
        if (!outfile)
        {
            cout << "unable to open file";
            exit(-1);
        }
        while (heap.size() > 0)
        {
            struct heapele ele = extract_min(heap);
            outfile << to_string(ele.num) << ",";
            long long index = ele.index;

            string data = "";
            infile[index].seekg(lendigit[index], infile[index].beg);
            if (infile[index].peek() == EOF)
            {
                infile[index].close();
                remove(filenames[index].c_str());
                filenames[index] = "";
                continue;
            }

            string value;
            getline(infile[index], value, ',');

            lendigit[index] += value.size() + 1;
            insert(heap, stoll(value), index);
        }
        outfile.close();
    }
    long long rem = no_of_files - file_no;
    vector<struct heapele> heap;
    for (long long i = 0; i < rem; i++)
    {
        string name = fname + to_string(file_no) + ".txt";
        infile[i].open(name, ios::in);
        filenames[i] = name;
        string value;
        getline(infile[i], value, ',');
        lendigit[i] = value.size() + 1;

        struct heapele ele;
        ele.index = i;
        ele.num = stoll(value);

        heap.push_back(ele);
        file_no++;
    }
    build_heap(heap);
    no_of_files++;
    ofstream outfile;
    outfile.open(out_file, ios::out);
    if (!outfile)
    {
        cout << "unable to open file" << endl;
        exit(-1);
    }
    while (heap.size() > 0)
    {
        struct heapele ele = extract_min(heap);
        long long index = ele.index;

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
            remove(filenames[index].c_str());
            continue;
        }

        string value;
        getline(infile[index], value, ',');

        lendigit[index] += value.size() + 1;
        insert(heap, stoll(value), index);
    }
    delete[] infile;
    outfile.close();
}
int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        cout << "Insufficiet command line arguments" << endl;
        exit(-1);
    }

    inp_file = argv[1];
    out_file = argv[2];

    char tmp[256];
    getcwd(tmp, 256);
    cwd = tmp;

    clock_t start, end;
    start = clock();

    string fname = cwd + "/";
    string name = fname + out_file;

    inp_file = cwd + "/" + inp_file;
    ofstream outfile;
    outfile.open(name, ios::out);
    if (!outfile)
    {
        cout << "File not created!";
        exit(-1);
    }
    outfile.close();
    out_file = fname + out_file;

    if (mkdir("files", 0777) == -1)
    {
        cout << "Unable to create directory";
        exit(-1);
    }
    generateFiles();
    k_way_merge();
    remove("files");

    cout << "CLOCKS_PER_SEC " << CLOCKS_PER_SEC << "\n";
    cout << "CPU-TIME START " << start << "\n";
    cout << "CPU-TIME END " << end << "\n";
    cout << "CPU-TIME END - START " << end - start << "\n";
    cout << "TIME(MIN) " << static_cast<double>(end - start) / (CLOCKS_PER_SEC * 60) << "\n";

    return 0;
}
