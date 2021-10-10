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
        this->deque = new T[100];
        this->front = this->rear = -1;
        this->size = 0;
        capacity = 100;
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
            cout << "Deque is full\n";
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
            cout << "Deque is full\n";
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
    int operator[](int n)
    {
        if (!this->empty())
        {
            if (this->front != -1)
                return deque[(this->front + n) % capacity];
            else
                return deque[n % capacity];
        }

        else
            return -1;
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
        int option, val, temp, newsize;
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
            newsize = temp = 0;
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
            cin >> val;
            cout << d1[val] << "\n";
            break;
        case 12:
            return 0;
            break;
        }
    }
}
