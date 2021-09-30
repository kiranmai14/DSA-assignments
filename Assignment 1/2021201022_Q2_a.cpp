#include <iostream>
#include <unordered_map>
using namespace std;

/*class Node will store the key,value,next pointer,prev pointer*/
class Node
{
public:
    int key, value;
    Node *next;
    Node *prev;
    Node(int key, int value)
    {
        this->key = key;
        this->value = value;
        next = nullptr;
        prev = nullptr;
    }
};
/*DoublyLinkedList will store the sequence of memory accesses*/
class DoublyLinkedList
{
public:
    Node *head, *tail;
    DoublyLinkedList()
    {
        head = tail = nullptr;
    }
    /*THis function will insert node into the DoublyLinkedList*/
    Node *insert(int key, int value)
    {
        Node *node = new Node(key, value);
        /* If the Doublylinkedlist is empty create a new node,
            insert it and update head and tail */
        if (head == nullptr && tail == nullptr)
        {
            head = tail = node;
        }
        /*If the Doublylinkedlist is not empty insert the node at 
            the end of the tail and update the tail*/
        else
        {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
        return tail;
    }
    Node *move(Node *ptr)
    {
        /*If the node is rectently accessed then it is 
        present at tail only so we will return */
        if (ptr == tail)
            return ptr;
        else
        {
            /*If the node has both prev and next node
                then make them to point each other and move 
                the ptr to the tail and update the tail*/
            if (ptr->prev != nullptr && ptr->next != nullptr)
            {
                ptr->prev->next = ptr->next;
                ptr->next->prev = ptr->prev;
                ptr->prev = tail;
                ptr->next = nullptr;
                tail->next = ptr;
                tail = ptr;
            }
            /*If the node itself is head and make the next
                node as head and move head to the tail and update tail*/
            else if (ptr == head)
            {
                ptr->prev = tail;
                tail->next = ptr;
                head = ptr->next;
                head->prev = nullptr;
                ptr->next = nullptr;
                tail = ptr;
            }
        }
        return tail;
    }
    int deleteNode()
    {
        Node *temp = head;
        int key = temp->key;
        if (head->next)
        {
            head = head->next;
            head->prev = nullptr;
            free(temp);
        }
        else
        {
            head = nullptr;
            tail = nullptr;
        }
        // head = head->next;
        // head->prev = nullptr;
        // int key = temp->key;
        // free(temp);
        return key;
    }
    void print()
    {
        Node *temp = head;
        while (temp != nullptr)
        {
            cout << temp->key << "," << temp->value << "->";
            temp = temp->next;
        }
    }
};

/*It will implement the LRU cache funtionality*/
class LRU
{
public:
    int size, capacity;
    unordered_map<int, Node *> cache;
    DoublyLinkedList que;
    /*Initializes the cache with the given capacity*/
    LRU(int capacity)
    {
        this->capacity = capacity;
        size = 0;
    }
    /*I t will return the value of the key if it is
        present in the cache*/
    int get(int key)
    {
        /*If the cache is empty it return -1*/
        if (capacity == 0)
            return -1;
        /*If the element is not in the cache return -1*/
        if (cache.find(key) == cache.end())
            return -1;
        else
        {
            /*If the element is in cache move that node to the tail
                so that it represents that it is newly accessed and
                update the pointer in the cache*/
            Node *ptr = que.move(cache[key]);
            cache[key] = ptr;
            return cache[key]->value;
        }
    }
    /*It will insert the value into the cache*/
    void set(int key, int value)
    {
        /*Return if the cache capacity is zero*/
        if (capacity == 0)
            return;
        /*checking whether the element is present in the cache*/
        if (cache.find(key) == cache.end())
        {
            Node *ptr = que.insert(key, value);
            /*If there is space in the cache insert the 
                element into the cache and increase the cache size*/
            if (size < capacity)
            {
                cache[key] = ptr;
                size++;
            }
            /*If the cache is full remove the least recently 
                used element from the cache and insert the given element*/
            else if (size == capacity)
            {
                int deletedKey = que.deleteNode();
                cache.erase(deletedKey);
                cache[key] = ptr;
                cache[key]->value = value;
            }
        }
        /*If the element is in the cache then move that 
        element to the tail of the Doublylinkedlist so that 
        it represents that it is recently accessed and 
        update its value if its value gets changed*/
        else
        {
            Node *mv = que.move(cache[key]);
            mv->value = value;
        }
    }
    void printList()
    {
        que.print();
    }
    void printCache()
    {
        for (auto d : cache)
        {
            cout << "key:" << d.first << " "
                 << "value:" << d.second << endl;
        }
    }
};


int main()
{

    int capacity;

    cin >> capacity;
    LRU cache(capacity);
    int queries;
    cin >> queries;
    while(queries--){
            int key = -1, value = -1, ch = 0, v = 0;
        cin >> ch;
        switch (ch)
        {
        case 1:
            cin >> key;
            v = cache.get(key);
            cout << v << endl;
            break;
        case 2:
            cin >> key;
            cin >> value;
            cache.set(key, value);
            break;
        }
    }

    return 0;
}