#include <iostream>
#define M 500
#define N 500
#define rows 1000
#define cols 3
using namespace std;

template <typename T>
class sparseM
{
public:
    T smat[1000][3];
    int r, c, count;
    sparseM(int r, int c)
    {
        this->r = r;
        this->c = c;
        count = 0;
    }
    void print()
    {
        cout << "row col val\n";
        for (int i = 0; i < count; i++)
        {
            cout << smat[i][0] << " " << smat[i][1] << " " << smat[i][2] << endl;
        }
    }
};

template <typename F, class T>
class arrayOperations
{
public:
    void get(T mat[M][N], int r, int c)
    {
        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < c; j++)
                cin >> mat[i][j];
        }
    }
    void toSparse(T mat[M][N], sparseM<T> &s)
    {
        int k = 0;
        for (int i = 0; i < s.r; i++)
        {
            for (int j = 0; j < s.c; j++)
            {
                if (mat[i][j] == 0)
                    continue;
                else
                {
                    s.smat[k][0] = i;
                    s.smat[k][1] = j;
                    s.smat[k][2] = mat[i][j];
                    k++;
                }
            }
        }
        s.count = k;
    }
    void addSparseMatrices(sparseM<T> s1, sparseM<T> s2, sparseM<T> &s3)
    {

        if (s1.r != s2.r || s1.c != s2.c)
            return;
        int i = 0, j = 0, k = 0;
        s3.r = s1.r;
        s3.c = s1.c;
        while (i < s1.count && j < s2.count)
        {
            if (s1.smat[i][0] == s2.smat[j][0])
            {
                s3.smat[k][0] = s1.smat[i][0];
                if (s1.smat[i][1] == s2.smat[j][1])
                {
                    T val = s1.smat[i][2] + s2.smat[j][2];
                    if (val == 0)
                        continue;
                    else
                    {
                        s3.smat[k][1] = s1.smat[i][1];
                        s3.smat[k][2] = val;
                        i++;
                        j++;
                        k++;
                    }
                }
                else
                {
                    if (s1.smat[i][1] < s2.smat[j][1])
                    {
                        s3.smat[k][1] = s1.smat[i][1];
                        s3.smat[k][2] = s1.smat[i][2];
                        i++;
                    }
                    else
                    {
                        s3.smat[k][1] = s2.smat[j][1];
                        s3.smat[k][2] = s2.smat[j][2];
                        j++;
                    }
                    k++;
                }
            }
            else
            {
                if (s1.smat[i][0] < s2.smat[j][0])
                {
                    s3.smat[k][0] = s1.smat[i][0];
                    s3.smat[k][1] = s1.smat[i][1];
                    s3.smat[k][2] = s1.smat[i][2];
                    i++;
                }
                else
                {
                    s3.smat[k][0] = s2.smat[j][0];
                    s3.smat[k][1] = s2.smat[j][1];
                    s3.smat[k][2] = s2.smat[j][2];
                    j++;
                }
                k++;
            }
        }
        while (i < s1.count)
        {
            s3.smat[k][0] = s1.smat[i][0];
            s3.smat[k][1] = s1.smat[i][1];
            s3.smat[k][2] = s1.smat[i][2];
            i++;
            k++;
        }
        while (j < s2.count)
        {
            s3.smat[k][0] = s2.smat[j][0];
            s3.smat[k][1] = s2.smat[j][1];
            s3.smat[k][2] = s2.smat[j][2];
            j++;
            k++;
        }
        s3.count = k;
    }
    void multiplySparseMatrices(sparseM<T> s1, sparseM<T> s2, sparseM<T> &res)
    {
        if (s1.c != s2.r)
            return;
        int k = 0;
        sparseM<int> s2_t(s2.r, s2.c);
        this->sparseTranspose(s2, s2_t);
        s2_t.print();
        for (int s1p = 0; s1p < s1.count;)
        {
            int r = s1.smat[s1p][0];
            for (int s2p = 0; s2p < s2_t.count;)
            {
                int c = s2_t.smat[s2p][0];
                T sum = 0;
                int t1 = s1p, t2 = s2p;
                while (t1 < s1.count && s1.smat[t1][0] == r &&
                       t2 < s2_t.count && s2_t.smat[t2][0] == c)
                {
                    if (s1.smat[t1][1] == s2_t.smat[t2][1])
                    {
                        sum += s2_t.smat[t2][2] * s1.smat[t1][2];
                        t1++;
                        t2++;
                    }
                    else if (s1.smat[t1][1] < s2_t.smat[t2][1])
                        t1++;
                    else if (s1.smat[t1][1] > s2_t.smat[t2][1])
                        t2++;
                }
                if (sum != 0)
                {
                    res.smat[k][0] = r;
                    res.smat[k][1] = c;
                    res.smat[k][2] = sum;
                    k++;
                }
                while (s2p < s2_t.count && s2_t.smat[s2p][0] == c)
                    s2p++;
            }
            while (s1p < s1.count && s1.smat[s1p][0] == r)
                s1p++;
        }
        res.count = k;
    }
    void sparseTranspose(sparseM<T> s, sparseM<T> &res)
    {
        int size = s.c;
        T total[size], index[size + 1];
        for (int i = 0; i < s.count; i++)
        {
            total[s.smat[i][1]]++;
        }
        index[0] = 1;
        for (int i = 1; i < size + 1; i++)
        {
            index[i] = index[i - 1] + total[i - 1];
        }
        for (int i = 0; i < s.count; i++)
        {
            int loc = index[s.smat[i][1]];
            res.smat[loc - 1][0] = s.smat[i][1];
            res.smat[loc - 1][1] = s.smat[i][0];
            res.smat[loc - 1][2] = s.smat[i][2];
            index[s.smat[i][1]]++;
        }
        res.r = s.c;
        res.c = s.r;
        res.count = s.count;
    }
};

int main()
{
    int r1, c1, r2, c2;
    cout << "Enter row,col 1\n";
    cin >> r1 >> c1;
    int mat1[M][N];
    int mat2[M][N];
    // double mat1[M][N];
    // double mat2[M][N];
    arrayOperations<int, int> op;
    // arrayOperations<double, double> op;

    // sparseM<double> s1(r, c);
    // sparseM<double> s2(r, c);
    // sparseM<double> res(r, c);
    cout << "Enter mat1:\n";
    op.get(mat1, r1, c1);
    sparseM<int> s1(r1, c1);
    cout << "Enter row,col 2\n";
    cin >> r2 >> c2;
    sparseM<int> s2(r2, c2);
    sparseM<int> res1(0, 0);
    sparseM<int> res2(0, 0);
    cout << "Enter mat2:\n";
    op.get(mat2, r2, c2);
    // cout << "sparsem1" << endl;
    op.toSparse(mat1, s1);
    cout << "SpareseMat1:\n";
    s1.print();
    // cout << "sparsem2" << endl;
    op.toSparse(mat2, s2);
    cout << "SpareseMat2:\n";
    s2.print();
    cout << "Adding" << endl;
    op.addSparseMatrices(s1, s2, res1);
    // op.sparseTranspose(s1, res);
    cout << "Addition result:\n";
    res1.print();
    // cout << "Transposed Matrix\n";
    cout << "Multiplying\n";
    op.multiplySparseMatrices(s1, s2, res2);
    cout<<"Multiplication result\n";
    res2.print();
    return 0;
}
