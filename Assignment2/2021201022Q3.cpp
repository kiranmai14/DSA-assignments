#include <iostream>
using namespace std;
template <typename T>
class Deque
{
public:
    T *deque;
    int front, rear, size, capacity;
    Deque()
    {
        this->deque = new T[5];
        this->front = this->rear = -1;
        this->size = 0;
        this->capacity = 5;
        // for (int i = 0; i < capacity; i++)
        //     this->deque[i] = 0;
    }
    Deque(int capacity, T data)
    {
        this->deque = new T[capacity];
        for (int i = 0; i < capacity; i++)
            this->deque[i] = data;
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
        if ((this->front == -1 && this->rear == capacity - 1) || (this->front == this->rear + 1))
        {
            // cout << "Deque is full\n";
            this->resize(this->capacity * 2, 0);
        }
        else if (this->front == -1)
        {
            this->front = capacity - 1;
            deque[this->front] = val;
            this->size++;
        }
        // else if (this->front == 0)
        // {
        //     this->front = capacity - 1;
        //     deque[this->front] = val;
        //     size++;
        // }
        else
        {
            this->front--;
            deque[this->front] = val;
            this->size++;
        }
    }
    void push_back(T val)
    {
        if ((this->front == -1 && this->rear == capacity - 1) || (this->front == this->rear + 1))
        {
            // cout << "Deque is full\n";
            this->resize(this->capacity * 2, 0);
        }
        else if (this->rear == -1)
        {
            this->rear = 0;
            deque[this->rear] = val;
            this->size++;
        }
        // else if (this->rear == capacity - 1)
        // {
        //     this->rear = 0;
        //     deque[this->rear] = val;
        //     size++;
        // }
        else
        {
            this->rear++;
            deque[this->rear] = val;
            this->size++;
        }
    }
    void pop_front()
    {
        if (this->front == -1 && this->rear == -1)
        {
            cout << "Deque is empty\n";
        }
        // else if (this->front == this->rear)
        // {
        //     cout << "Dequed" << deque[this->rear] << "\n";
        //     this->front = this->rear = -1;
        //     size--;
        // }
        else if (this->front == capacity - 1)
        {
            cout << "Dequed" << deque[this->front] << "\n";
            if (this->rear == -1)
                this->front = -1;
            else
                this->front = 0;
            this->size--;
        }
        else
        {
            if (this->front == this->rear)
            {
                cout << "Dequed" << deque[this->front] << "\n";
                this->front = this->rear = -1;
                this->size--;
            }
            else
            {
                cout << "Dequed" << deque[this->front] << "\n";
                this->front++;
                this->size--;
            }
        }
    }
    void pop_back()
    {
        if (this->front == -1 && this->rear == -1)
        {
            cout << "Deque is empty\n";
        }

        else if (this->rear == 0)
        {
            cout << "Dequed" << deque[this->rear] << "\n";
            if (this->front == -1)
                this->rear = -1;
            else
                this->rear = capacity - 1;
            this->size--;
        }
        else
        {
            if (this->front == this->rear)
            {
                cout << "Dequed" << deque[this->rear] << "\n";
                this->front = this->rear = -1;
                this->size--;
            }
            else
            {
                cout << "Dequed" << deque[this->rear] << "\n";
                this->rear--;
                this->size--;
            }
        }
    }
    void fron()
    {
        if (this->front == -1 && this->rear == -1)
        {
            cout << "Deque is empty\n";
        }
        else
        {
            if (this->front == -1)
                cout << deque[0];
            cout << deque[this->front];
        }
    }
    void back()
    {
        if (this->front == -1 && this->rear == -1)
        {
            cout << "Deque is empty\n";
        }
        else
        {
            if (this->rear == -1)
                cout << deque[this->capacity - 1];
            cout << deque[this->rear];
        }
    }
    int dequeSize()
    {
        return this->size;
    }
    void clear()
    {
        this->size = 0;
        this->front = this->rear = -1;
    }
    void resize(int newsize, T val)
    {
        T *temp = new T[newsize];
        for (int i = 0; i < newsize; i++)
            temp[i] = val;
        if (newsize >= this->capacity)
        {
            for (int i = 0; i <= rear; i++)
                temp[i] = deque[i];
            int l = newsize - 1;
            if (this->front != -1)
            {
                for (int j = capacity - 1; j >= this->front && j > this->rear; j--)
                    temp[l--] = deque[j];
                this->front = l + 1;
            }
        }
        else
        {
            int l = newsize - 1;
            if (this->front != -1)
            {
                for (int i = capacity - 1; i >= this->front && l >= 0; i--)
                    temp[l--] = deque[i];
                this->front = l + 1;
                int i = 0;
                for (i = 0; i < this->front && i <= this->rear && i < newsize; i++)
                    temp[i] = deque[i];
                this->rear = i - 1;
            }
            else
            {
                int i = 0;
                for (i = 0; i <= this->rear && i < newsize; i++)
                    temp[i] = deque[i];
                this->rear = i - 1;
            }
            this->size = newsize;
        }
        this->deque = temp;
        this->capacity = newsize;
    }
    void operator[](int n)
    {
        if (!this->empty())
        {
            if (this->front != -1)
                cout<<deque[(this->front + n) % capacity];
            else
                cout<<deque[n % capacity];
        }
        else
            cout<<-1;
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
    Deque<int> d1;
    // Deque<string> d1;
    // int n, c;
    // cin >> n >> c;
    // Deque<int> d2(n, c);
    while (1)
    {
        cout << "1.push_back 2.pop_back 3.push_front 4.pop_front 5.front 6.back\n7.empty 8.size 9.resize 10.clear 11.D[n] 12.exit\n";
        int option, newsize, index;
        int val, temp;
        // string val, temp;
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
            d1.fron();
            cout << "\n";
            break;
        case 6:
            d1.back();
            cout << "\n";
            break;
        case 7:
            cout << d1.empty() << "\n";
            break;
        case 8:
            index = d1.dequeSize();
            cout << index << "\n";
            break;
        case 9:
            newsize = 0;
            cout << "Enter [newsize,default]: ";
            cin >> newsize >> temp;
            d1.resize(newsize, temp);
            d1.print();
            break;
        case 10:
            d1.clear();
            break;
        case 11:
            cout << "Enter index: ";
            cin >> index;
            d1[index] ;
            cout<< "\n";
            break;
        case 12:
            return 0;
            break;
        }
    }
}
