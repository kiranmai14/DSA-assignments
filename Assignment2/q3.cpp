#include <iostream>
#include <cstring>
using namespace std;
template <typename T>
class Deque
{
public:
    T *deque;
    int front, rear, size, capacity;
    Deque()
    {
        this->deque = new T[100];
        this->front = this->rear = -1;
        size = 0;
        capacity = 100;
    }
    Deque(int capacity, T data)
    {
        this->deque = new T[capacity];
        memset(this->deque, data, capacity);
        this->front = this->rear = -1;
        this->size = 0;
        this->capacity = capacity;
    }
    bool empty()
    {
        if (this->front == -1 && this->rear == -1)
        {
            cout << "Deque is empty\n";
            return true;
        }
        return false;
    }
    void push_front(T val)
    {
        if ((this->front == 0 && this->rear == capacity - 1) || (this->front == this->rear + 1))
        {
            cout << "Deque is full\n";
        }
        else if (this->front == -1 && this->rear == -1)
        {
            this->front = this->rear = 0;
            deque[this->front] = val;
            size++;
        }
        else if (this->front == 0)
        {
            this->front = capacity - 1;
            deque[this->front] = val;
            size++;
        }
        else
        {
            this->front--;
            deque[this->front] = val;
            size++;
        }
    }
    void push_back(T val)
    {
        if ((this->front == 0 && this->rear == capacity - 1) || (this->front == this->rear + 1))
        {
            cout << "Deque is full\n";
        }
        else if (this->front == -1 && this->rear == -1)
        {
            this->front = this->rear = 0;
            deque[this->rear] = val;
            size++;
        }
        else if (this->rear == capacity - 1)
        {
            this->rear = 0;
            deque[this->rear] = val;
            size++;
        }
        else
        {
            this->rear++;
            deque[this->rear] = val;
            size++;
        }
    }
    void pop_front()
    {
        if (this->front == -1 && this->rear == -1)
        {
            cout << "Deque is empty\n";
        }
        else if (this->front == this->rear)
        {
            cout << "Dequed" << deque[this->rear] << "\n";
            this->front = this->rear = -1;
            size--;
        }
        else if (this->front == capacity - 1)
        {
            cout << "Dequed" << deque[this->front] << "\n";
            this->front = 0;
            size--;
        }
        else
        {
            cout << "Dequed" << deque[this->front] << "\n";
            this->front++;
            size--;
        }
    }
    void pop_back()
    {
        if (this->front == -1 && this->rear == -1)
        {
            cout << "Deque is empty\n";
        }
        else if (this->front == this->rear)
        {
            cout << "Dequed" << deque[this->rear] << "\n";
            this->front = this->rear = -1;
            size--;
        }
        else if (this->rear == 0)
        {
            cout << "Dequed" << deque[this->rear] << "\n";
            this->rear = capacity - 1;
            size--;
        }
        else
        {
            cout << "Dequed" << deque[this->rear] << "\n";
            this->rear--;
            size--;
        }
    }
    int fron()
    {
        if (this->front == -1 && this->rear == -1)
        {
            cout << "Deque is empty\n";
            return -1;
        }
        else
        {
            return deque[this->front];
        }
    }
    int back()
    {
        if (this->front == -1 && this->rear == -1)
        {
            cout << "Deque is empty\n";
            return -1;
        }
        else
        {
            return deque[this->rear];
        }
    }
    int dequeSize()
    {
        return size;
    }
    void clear()
    {
        deque = nullptr;
        this->front = this->rear = -1;
    }
    void resize(int newsize, int val)
    {
        // int dummy[capacity];
        // for (int i = 0; i < capacity; i++)
        //     dummy[i] = deque[i];
        // deque = nullptr;
        // deque = new int[newsize];
        // memset(deque, val, newsize);
        // for (int i = 0; i < capacity; i++)
        //     deque[i] = dummy[i];
        // this->capacity = newsize;
        T *temp = new T[newsize];
        memset(temp, val, newsize);
        if(this->empty) deque = temp;
        else if (newsize >= this->capacity)
        {
            
            for (int i = 0; i <= rear; i++)
                temp[i] = deque[i];
            int l = newsize - 1;
            for (int i = capacity - 1; i >= this->front; i--)
                temp[l--] = deque[i];
        }
    }
    int operator[](int n)
    {
        return deque[(this->front + n) % capacity];
    }
    void print()
    {
        for (int i = 0; i < capacity; i++)
            cout << deque[i] << " ";
        cout << endl;
    }
};
int main()
{
    Deque<int> d1(5, 0);
    // int n, c;
    // cin >> n >> c;
    // Deque<int> d2(n, c);
    while (1)
    {
        cout << "1.push_back 2.pop_back 3.push_front 4.pop_front 5.front 6.back\n7.empty 8.size 9.resize 10.clear 11.D[n] 12.exit\n";
        int option, val, temp;
        cin >> option;
        switch (option)
        {
        case 1:
            cout << "Enter value: ";
            cin >> val;
            d1.push_back(val);
            d1.print();
            break;
        case 2:
            d1.pop_back();
            d1.print();
            break;
        case 3:
            cout << "Enter value: ";
            cin >> val;
            d1.push_front(val);
            d1.print();
            break;
        case 4:
            d1.pop_front();
            break;
        case 5:
            temp = d1.fron();
            if (temp != -1)
                cout << temp << "\n";
            break;
        case 6:
            temp = d1.back();
            if (temp != -1)
                cout << temp << "\n";
            break;
        case 7:
            cout << d1.empty() << "\n";
            break;
        case 8:
            temp = d1.dequeSize();
            cout << temp << "\n";
            break;
        case 9:
            temp = d1.dequeSize();
            cout << temp << "\n";
            break;
        case 10:
            d1.clear();
            break;
        case 11:
            cout << "Enter index: ";
            cin >> val;
            cout << d1[val] << "\n";
            break;
        case 12:
            return 0;
            break;
        }
    }
}
