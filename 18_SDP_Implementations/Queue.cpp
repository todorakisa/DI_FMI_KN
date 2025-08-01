#include <iostream>

using namespace std; 

template<typename T>
struct Node
{
    T data;
    Node<T>* next;
};

template<typename T>
class Queue
{
    private:
    void copyQueue(const Queue<T>& other);
    void deleteQueue();
    Node<T>* front;
    Node<T>* back;

    public:
    Queue();
    ~Queue();
    Queue(const Queue<T>& other);
    Queue<T>& operator=(const Queue<T>& other);

    void enqueue(T Elem);
    void dequeue();
    bool empty();
    T Head();
};

template<typename T>
void Queue<T>::copyQueue(const Queue<T>& other)
{
    if(other.front)
    {
        Node<T>* other_head = other.front;
        front = new Node<T>;
        front->data = other_head->data;
        front->next = nullptr;
        back = front;
        other_head = other_head->next;

        while (other_head)
        {
            Node<T>* newNode = new Node<T>;
            newNode->data = other_head->data;
            back->next = newNode;
            back = back->next;
            other_head = other_head->next;
        }  
        back->next = nullptr;
    }
    else
    {
        back = nullptr;
        front = nullptr;
    }
}

template<typename T>
void Queue<T>::deleteQueue()
{
    cout << "Destructor Queue: [";
    while (front)
    {
        Node<T>* tmp = front;
        front = front->next;
        cout << tmp->data <<" ";
        delete tmp;
    }
    back = nullptr;
    front = nullptr;
    cout << "]" << endl;
}

template<typename T>
Queue<T>::Queue()
{
    front = nullptr;
    back = nullptr;
}

template<typename T>
Queue<T>::~Queue()
{
    deleteQueue();
}

template<typename T>
Queue<T>::Queue(const Queue<T>& other){
    copyQueue(other);
}

template<typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& other)
{
    if(this != &other)
    {
        deleteQueue();
        copyQueue(other);
    }
    return *this;
}

template<typename T>
void Queue<T>::enqueue(T Elem)
{
    Node<T>* newNode = new Node<T>;
    newNode->data = Elem;
    newNode->next = nullptr;
    if(empty())
    {
        back = newNode;
        front = newNode;
    }
    else
    {
        back->next = newNode;
        back = back->next;
    }
}

template<typename T>
void Queue<T>::dequeue()
{
    Node<T>* tmp = front;
    front = front->next;
    delete tmp;
}

template<typename T>
bool Queue<T>::empty()
{
    return front == nullptr;
}

template<typename T>
T Queue<T>::Head()
{
    return front->data;
}

int main()
{
    Queue<int> my_q;
    my_q.enqueue(1);
    my_q.enqueue(2);
    my_q.enqueue(3);
    my_q.enqueue(4);
    my_q.enqueue(5);
    cout << "Test head: "<< my_q.Head() <<endl;
    my_q.dequeue();

    Queue<int> CopyQ (my_q);
    
    while (!CopyQ.empty())
    {
        cout << CopyQ.Head() << " ";
        CopyQ.dequeue();
    }
    cout << endl;

    CopyQ.enqueue(333);
    CopyQ.enqueue(333);
    CopyQ.enqueue(333);
    CopyQ.enqueue(333);

    return 0;
}