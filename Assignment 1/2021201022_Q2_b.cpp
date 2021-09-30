#include <iostream>
#include <unordered_map>
using namespace std;

class freqNode;
/*This class will store the key,value and has 
a pointer to the frequency node which is referred here as parent*/
class setNode
{
public:
    int key, value;
    setNode *next;
    setNode *prev;
    freqNode *parent;
    setNode(int key, int value, freqNode *parent)
    {
        this->key = key;
        this->value = value;
        next = nullptr;
        prev = nullptr;
        this->parent = parent;
    }
};

/*THis class will take care of all nodes 
which comes under same frequency*/
class setList
{
public:
    setNode *head, *tail;
    setList()
    {
        head = tail = nullptr;
    }
    setNode *insert(int key, int value, freqNode *parent)
    {
        {
            setNode *node = new setNode(key, value, parent);
            /* If the list is empty create a new node,
                    insert it and update head and tail */
            if (head == nullptr && tail == nullptr)
            {
                head = tail = node;
            }
            /*If the list is not empty insert the node at 
                    the end of the tail and update the tail*/
            else
            {
                tail->next = node;
                node->prev = tail;
                tail = node;
            }
            return tail;
        }
    }
    /*This functions removes the node from the head*/
    int deleteNode()
    {
        {
            setNode *temp = head;
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
            return key;
        }
    }
    /*This function removes the node at the given pointer*/
    void deleteAt(setNode *ptr)
    {
        {
            /*If the node is head*/
            if (ptr == head)
            {
                /*If there are more than one node*/
                if (ptr->next)
                {
                    head = ptr->next;
                    head->prev = nullptr;
                    free(ptr);
                }
                /*If there is only single node*/
                else
                {
                    head = nullptr;
                    tail = nullptr;
                }
            }
            /*If the node to be deleted has both left and right nodes*/
            else if (ptr->prev != nullptr && ptr->next != nullptr)
            {
                ptr->prev->next = ptr->next;
                ptr->next->prev = ptr->prev;
                free(ptr);
            }
            /*If the node is the last node*/
            else if (ptr == tail)
            {
                /*checking if it has previous node*/
                if (ptr->prev)
                {
                    tail = tail->prev;
                    tail->next = nullptr;
                    free(ptr);
                }
                else
                {
                    tail = nullptr;
                }
            }
        }
    }
};
/*This class will store the frequency nodes and
points to its setList object*/
class freqNode
{
public:
    int data;
    freqNode *next;
    freqNode *prev;
    setList shead;
    freqNode(int data)
    {
        this->data = data;
        next = nullptr;
        prev = nullptr;
    }
};
/*THis class will store the list of frequency nodes*/
class freqList
{
public:
    freqNode *head;
    freqList()
    {
        head = nullptr;
    }
    /*This class will insert the newnode at head*/
    setNode *insert(int key, int value)
    {
        setNode *insertedNode = nullptr;
        if (head == nullptr)
        {
            freqNode *node = new freqNode(1);
            insertedNode = node->shead.insert(key, value, node);
            head = node;
        }
        else
        {
            if (head->data != 1)
            {
                freqNode *node = new freqNode(1);
                insertedNode = node->shead.insert(key, value, node);
                node->next = head;
                head->prev = node;
                head = node;
            }
            else
            {
                insertedNode = head->shead.insert(key, value, head);
            }
        }
        return insertedNode;
    }
    /*This function will be called if the capacity 
    becomes full and then first setNode will be deleted
    since it is least frequently used*/
    int deletefreqNode()
    {

        int key = head->shead.deleteNode();
        freqNode *ptr = nullptr;
        /*After deletion if the setList is empty 
        completely delete that freqNode*/
        if (head->shead.head == nullptr)
        {
            ptr = head;
            /*Checking whether it there is only one node*/
            if (ptr->next)
            {
                ptr->next->prev = nullptr;
                head = ptr->next;
                free(ptr);
            }
            else
            {
                head = nullptr;
                free(ptr);
            }
        }
        return key;
    }
    /*This function moves the recently accessed node to its 
    increased frequency node*/
    setNode *move(setNode *ptr)
    {

        int freq = ptr->parent->data;
        setNode *newAdd = nullptr;
        /*If the parent has next node*/
        if (ptr->parent->next)
        {
            /*Checking whether the next node has the required frequency*/
            if (ptr->parent->next->data == freq + 1)
            {
                newAdd = ptr->parent->next->shead.insert(ptr->key, ptr->value, ptr->parent->next);
                ptr->parent->shead.deleteAt(ptr); //deleting the node's previous position
            }
            /*If the next node did not have the required frequency*/
            else
            {
                freqNode *node = new freqNode(freq + 1);
                /*Inserting the node in between the nodes*/
                node->next = ptr->parent->next;
                node->prev = ptr->parent;
                ptr->parent->next->prev = node;
                ptr->parent->next = node;
                newAdd = ptr->parent->next->shead.insert(ptr->key, ptr->value, ptr->parent->next);
                ptr->parent->shead.deleteAt(ptr);
            }
        }
        /*If the parent has no next node*/
        else
        {
            freqNode *node = new freqNode(freq + 1);
            newAdd = node->shead.insert(ptr->key, ptr->value, node);
            ptr->parent->shead.deleteAt(ptr);
            node->prev = ptr->parent;
            ptr->parent->next = node;
        }
        /*After deletion if the freqNode has no children then delete that node*/
        if (ptr->parent->shead.head == nullptr)
        {
            /*If it is head*/
            if (ptr->parent == head)
            {
                if (head->next)
                {
                    head = head->next;
                    head->prev = nullptr;
                }
                else
                {
                    head = nullptr;
                }
            }
            /*If it contains both left and right nodes*/
            else if (ptr->parent->prev && ptr->parent->next)
            {
                ptr->parent->prev->next = ptr->parent->next;
                ptr->parent->next->prev = ptr->parent->prev;
            }
            free(ptr->parent);
        }
        return newAdd;
    }
};
class LFU
{
public:
    int capacity, size;
    unordered_map<int, setNode *> cache;
    freqList que;
    LFU(int capacity)
    {
        size = 0;
        this->capacity = capacity;
    }
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
            setNode *ptr = que.move(cache[key]);
            cache[key] = ptr;
            return cache[key]->value;
        }
    }
    void set(int key, int value)
    {
        /*Return if the cache capacity is zero*/
        if (capacity == 0)
            return;
        if (cache.find(key) == cache.end())
        {
            /*Inserting for thr first time*/
            if (size < capacity)
            {
                setNode *ptr = que.insert(key, value);
                cache[key] = ptr;
                size++;
            }
            else if (size == capacity)
            {
                int deletedKey = que.deletefreqNode();
                cache.erase(deletedKey);
                setNode *ptr = que.insert(key, value);
                cache[key] = ptr;
                cache[key]->value = value;
            }
        }
        else
        {
            setNode *ptr = cache[key];
            setNode *movedptr = que.move(ptr);
            cache[key] = movedptr;
            cache[key]->value = value;
        }
    }
    void printCache()
    {
        for (auto d : cache)
        {
            cout << "key:" << d.first << " "
                 << "value:" << d.second << endl;
        }
    }
    void printList()
    {
        freqNode *temp = que.head;
        while (temp != nullptr)
        {
            setList x = temp->shead;
            setNode *tem = x.head;
            if (tem != nullptr)
                cout << "freq: " << temp->data << " ";
            while (tem != nullptr)
            {
                cout << "(" << tem->key << " " << tem->value << ")->";
                tem = tem->next;
            }
            cout << endl;
            temp = temp->next;
        }
    }
};

int main()
{

    int capacity;
    cin >> capacity;
    LFU cache(capacity);
    int queries;
    cin >> queries;
    while (queries--)
    {
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