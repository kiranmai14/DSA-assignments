#include <iostream>
#define M 500
#define N 500
#define rows 1000
#define cols 3
using namespace std;

template <typename T>
class Node
{
public:
    int row, col;
    T value;
    Node *next;
    Node *prev;
    Node(int row, int col, T value)
    {
        this->row = row;
        this->col = col;
        this->value = value;
        next = nullptr;
        prev = nullptr;
    }
};

template <typename T>
Node<T> *merge(Node<T> *left, Node<T> *right);
template <typename T>
void divide(Node<T> *head, Node<T> **left, Node<T> **right);
template <typename T>
void mergeSort(Node<T> **headptr);

template <class T>
class sparseMatLL
{
public:
    Node<T> *head, *tail;
    sparseMatLL(int r, int c)
    {
        head = tail = new Node<T>(r, c, 0);
    }
    void insert(int row, int col, T value)
    {
        Node<T> *node = new Node<T>(row, col, value);
        if(head == nullptr && tail == nullptr)
            head = tail = node;
        tail->next = node;
        node->prev = tail;
        tail = node;
    }
    void deleteFront()
    {
        if (head == nullptr || head->next == nullptr)
            return;
        else
        {
            Node<T> *temp = head;
            head = head->next;
            free(temp);
        }
    }
    void insertFront(int row, int col, int value)
    {
        if (head == nullptr)
            return;
        else
        {
            Node<T> *temp = new Node<T>(row, col, value);
            head->prev = temp;
            temp->next = head;
            head = temp;
        }
    }
    void print()
    {
        Node<T> *temp = head->next;
        cout << "row col val\n";
        while (temp != nullptr)
        {
            cout << (temp->row) << " " << (temp->col) << " " << temp->value << endl;
            temp = temp->next;
        }
    }
};

template <class T>
class LLoperations
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
    void toSparse(T mat[M][N], sparseMatLL<T> &s)
    {
        int k = 0;
        for (int i = 0; i < s.head->row; i++)
        {
            for (int j = 0; j < s.head->col; j++)
            {
                if (mat[i][j] == 0)
                    continue;
                else
                {
                    s.insert(i, j, mat[i][j]);
                    k++;
                }
            }
        }
        s.head->value = k;
    }
    void addSparseMatrices(sparseMatLL<T> s1, sparseMatLL<T> s2, sparseMatLL<T> &s3)
    {
        int k = 0;
        if (s1.head->row != s2.head->row || s1.head->col != s2.head->col)
            return;
        Node<T> *t1 = s1.head->next, *t2 = s2.head->next;
        while (t1 != nullptr && t2 != nullptr)
        {
            if (t1->row == t2->row)
            {
                if (t1->col == t2->col)
                {
                    T val = t1->value + t2->value;
                    if (val != 0)
                        s3.insert(t1->row, t1->col, val);
                    t1 = t1->next;
                    t2 = t2->next;
                }
                else if (t1->col < t2->col)
                {
                    s3.insert(t1->row, t1->col, t1->value);
                    t1 = t1->next;
                }
                else if (t1->col > t2->col)
                {
                    s3.insert(t2->row, t2->col, t2->value);
                    t2 = t2->next;
                }
                k++;
            }
            else
            {
                if (t1->row < t2->row)
                {
                    s3.insert(t1->row, t1->col, t1->value);
                    t1 = t1->next;
                }
                else if (t1->row > t2->row)
                {
                    s3.insert(t2->row, t2->col, t2->value);
                    t2 = t2->next;
                }
                k++;
            }
        }
        while (t1 != nullptr)
        {
            s3.insert(t1->row, t1->col, t1->value);
            t1 = t1->next;
            k++;
        }
        while (t2 != nullptr)
        {
            s3.insert(t2->row, t2->col, t2->value);
            t2 = t2->next;
            k++;
        }
        s3.head->value = k;
    }
    void sparseTranspose(sparseMatLL<T> s, sparseMatLL<T> &res)
    {
        res = s;
        Node<T> *temp = res.head;
        while (temp != nullptr)
        {
            T var = temp->col;
            temp->col = temp->row;
            temp->row = var;
            temp = temp->next;
        }
        int r = res.head->row;
        int c = res.head->col;
        int val = res.head->value;
        res.deleteFront();
        mergeSort(&(res.head));
        // res.print();
        res.insertFront(r, c, val);
    }
    void multiplyMatrices(sparseMatLL<T> s1, sparseMatLL<T> s2, sparseMatLL<T> &s3)
    {
        if (s1.head->col != s2.head->row)
            return;
        int k = 0;
        sparseMatLL<T> s2_t(s2.head->row, s2.head->col);
        this->sparseTranspose(s2, s2_t);
        Node<T> *temp1 = s1.head->next;
        Node<T> *temp2 = s2_t.head->next;
        // s3.insertFront(s1.head->row, s2.head->col, 0);
        Node<T> *res = s3.head;
        while (temp1 != nullptr)
        {
            int r = temp1->row;
            temp2 = s2_t.head->next;
            while (temp2 != nullptr)
            {
                int c = temp2->row;
                T sum = 0;
                Node<T> *x1 = temp1;
                Node<T> *x2 = temp2;
                while (x1 && x1->row == r && x2 && x2->row == c)
                {
                    if (x1->col == x2->col)
                    {
                        sum += x1->value * x2->value;
                        x1 = x1->next;
                        x2 = x2->next;
                    }
                    else if (x1->col < x2->col)
                    {
                        x1 = x1->next;
                    }
                    else if (x1->col > x2->col)
                    {
                        x2 = x2->next;
                    }
                }
                if (sum != 0)
                {
                    s3.insert(r, c, sum);
                    k++;
                }
                while (temp2 != nullptr && temp2->row == c)
                {
                    temp2 = temp2->next;
                }
            }
            while (temp1 != nullptr && temp1->row == r)
            {
                temp1 = temp1->next;
            }
        }
        res->value = k;
    }
};
template <typename T>
Node<T> *merge(Node<T> *left, Node<T> *right)
{
    Node<T> *ans = nullptr;
    if (left == nullptr)
        return right;
    if (right == nullptr)
        return left;
    if (left->row < right->row)
    {
        ans = left;
        ans->next = merge(left->next, right);
    }
    else if (left->row == right->row)
    {
        if (left->col <= right->col)
        {
            ans = left;
            ans->next = merge(left->next, right);
        }
        else
        {
            ans = right;
            ans->next = merge(left, right->next);
        }
    }
    else if (left->row > right->row)
    {
        ans = right;
        ans->next = merge(left, right->next);
    }
    return ans;
}
template <typename T>
void divide(Node<T> *head, Node<T> **left, Node<T> **right)
{
    Node<T> *f, *s;
    s = head;
    f = head->next;
    while (f != nullptr)
    {
        f = f->next;
        if (f != nullptr)
        {
            s = s->next;
            f = f->next;
        }
    }
    *left = head;
    *right = s->next;
    s->next = nullptr;
}
template <typename T>
void mergeSort(Node<T> **headptr)
{
    Node<T> *head = *headptr;
    if (head == nullptr || head->next == nullptr)
        return;
    Node<T> *a, *b;
    divide(head, &a, &b);
    mergeSort(&a);
    mergeSort(&b);
    *headptr = merge(a, b);
}
int main()
{
    int r1, c1, r2, c2;
    // int mat1[M][N];
    // int mat2[M][N];
    // LLoperations<int> op;
    // cout << "Enter row,col 1\n";
    // cin >> r1 >> c1;
    // sparseMatLL<int> s1(r1, c1);
    // cout << "Enter mat1\n";
    // op.get(mat1, r1, c1);
    // op.toSparse(mat1, s1);
    // cout << "Enter row,col 1\n";
    // cin >> r2 >> c2;
    // sparseMatLL<int> s2(r2, c2);
    // cout << "Enter mat2\n";
    // op.get(mat2, r2, c2);
    // op.toSparse(mat2, s2);
    // cout << "SpareseMat1:\n";
    // s1.print();
    // cout << "SpareseMat2:\n";
    // s2.print();
    // sparseMatLL<int> s3(r1, c1);
    // // op.sparseTranspose(s1, s3);
    // cout << "Transpose..\n";
    // // cout << "Adding...\n";
    // // op.addSparseMatrices(s1, s2, s3);
    // cout << "Multiplying...\n";
    // op.multiplyMatrices(s1, s2, s3);
    // s3.print();
    double mat1[M][N];
    double mat2[M][N];
     LLoperations<double> op;
    cout << "Enter row,col 1\n";
    cin >> r1 >> c1;
    sparseMatLL<double> s1(r1, c1);
    cout << "Enter mat1\n";
    op.get(mat1, r1, c1);
    op.toSparse(mat1, s1);
    // cout << "Enter row,col 1\n";
    // cin >> r2 >> c2;
    // sparseMatLL<double> s2(r2, c2);
    // cout << "Enter mat2\n";
    // op.get(mat2, r2, c2);
    // op.toSparse(mat2, s2);
    cout << "SpareseMat1:\n";
    s1.print();
    // cout << "SpareseMat2:\n";
    // s2.print();
    sparseMatLL<double> st(r1, c1);
    sparseMatLL<double> sa(r1, c1);
    sparseMatLL<double> sm(r1, c1);
    // op.addSparseMatrices(s1,s2,sa);
    // op.multiplyMatrices(s1,s2,sm);
    // op.sparseTranspose(s1,st);
    // cout<<"Addition:\n";
    // sa.print();
    // cout<<"Multiplication:\n";
    // sm.print();
     cout<<"Transpose:\n";
    s1.print();

    return 0;
}