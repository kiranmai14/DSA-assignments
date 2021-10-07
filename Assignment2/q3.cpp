#include <iostream>
#include <cstring>
using namespace std;
class Deque
{
public:
    int *deque, f, r, size, capacity;
    Deque()
    {
        this->deque = new int[100];
        f = r = -1;
        size = 0;
        capacity = 100;
    }
    Deque(int capacity, int data)
    {
        this->deque = new int[capacity];
        memset(this->deque, data, capacity);
        this->f = this->r = -1;
        this->size = 0;
        this->capacity = capacity;
    }
    bool empty(){
        if(f == -1 && r==-1)
        {
            cout<<"Deque is empty\n";
            return true;
        }
        return false;
    }
    void push_front(int val)
    {
        if ((f == 0 && r == capacity - 1) || (f = r + 1))
        {
            cout << "Deque is full\n";
        }
        else if (f == -1 && r == -1)
        {
            f = r = 0;
            deque[f] = val;
            size++;
        }
        else if (f == 0)
        {
            f = capacity - 1;
            deque[f] = val;
            size++;
        }
        else
        {
            f--;
            deque[f] = val;
            size++;
        }

    }
    void push_back(int val)
    {
        if ((f == 0 && r == capacity - 1) || (f = r + 1))
        {
            cout << "Deque is full\n";
        }
        else if (f == -1 && r == -1)
        {
            f = r = 0;
            deque[r] = val;
            size++;
        }
        else if (r == capacity - 1)
        {
            r = 0;
            deque[r] = val;
            size++;
        }
        else
        {
            r++;
            deque[r] = val;
            size++;
        }
    }
    void pop_front(){
        if(f == -1 && r==-1)
        {
            cout<<"Deque is empty\n";
        }
        else if(f==r){
            f=r=-1;
        }
        else if(f == capacity-1){
            cout<<"Deued"<<deque[f];
            f=0;
            size--;
        }
        else{
            cout<<"Deued"<<deque[f];
            f++;
            size--;
        }
    }
     void pop_back(){
        if(f == -1 && r==-1)
        {
            cout<<"Deque is empty\n";
        }
        else if(f==r){
            f=r=-1;
        }
        else if(r == 0){
            cout<<"Deued"<<deque[r];
            f=capacity-1;
            size--;
        }
        else{
            cout<<"Deued"<<deque[r];
            r--;
            size--;
        }
    }
    int front(){
         if(f == -1 && r==-1)
        {
            cout<<"Deque is empty\n";
            return -1;
        }
        else{
            return deque[f];
        }
    }
    int back(){
         if(f == -1 && r==-1)
        {
            cout<<"Deque is empty\n";
            return -1;
        }
        else{
            return deque[r];
        }
    }
    int size(){
        return size;
    }
    void clear(){
        deque = nullptr;
    }
    void resize(int newsize,int val){
        int dummy[capacity];
        for(int i=0;i<capacity;i++)
            dummy[i] = deque[i];
        deque = nullptr;
        deque = new int[newsize];
        memset(deque,val,newsize);
        for(int i=0;i<capacity;i++)
            deque[i] = dummy[i];
        this->capacity = newsize; 
    }
    int operator [] (int n){
        return deque[n];
    }
};
int main()
{
}
