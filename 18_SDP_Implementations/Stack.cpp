#include <iostream>

using namespace std;

template<typename T>
struct Node
{
    T data;
    Node<T>* next;
};

template<typename T>
class Stack
{
    public:
    Stack();
    ~Stack();
    Stack(const Stack<T>& other);
    Stack<T>& operator=(const Stack<T>& other);

    bool empty();
    void pop();
    void push(T Elem);
    T peek();

    private:
    Node<T>* start;
    void copyStack(const Stack<T>& other);
    void deleteStack();
};

template<typename T>
void Stack<T>::copyStack(const Stack<T>& other){
    if(other.start)
    {
        Node<T>* other_start = other.start;
        this->start = new Node<T>;
        start->data = other_start->data;
        start->next = nullptr;
        Node<T>* our_start = start;
        other_start = other_start->next;

        while (other_start)
        {
            Node<T>* newNode = new Node<T>;
            newNode->data = other_start->data;
            our_start->next = newNode;
            our_start = our_start->next;
            other_start = other_start->next;
        }
        start->next = nullptr;
    }
    else
    {
        start = nullptr;
    }
}

template<typename T>
void Stack<T>::deleteStack()
{
    cout << "Deconstruction: [";
    while(start)
    {
        Node<T>* tmp = start;
        start = start->next;
        cout << tmp->data << " ";
        delete tmp;
    }
    cout << "]" << endl;
}

template<typename T>
Stack<T>::Stack()
{
    start = nullptr;
}

template<typename T>
Stack<T>::~Stack()
{
    deleteStack();
}

template<typename T>
Stack<T>::Stack(const Stack<T>& other)
{
    copyStack(other);
}

template<typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other)
{
    if(this != &other){
        deleteStack();
        copyStack(other);
    }

    return *this;
}

template<typename T>
bool Stack<T>::empty(){
    return start == nullptr;
}

template<typename T>
void Stack<T>::pop(){
    if(start)
    {
        Node<T>* current = start;
        start = start->next;
        delete current;
    }
}

template<typename T>
void Stack<T>::push(T Elem)
{
    Node<T>* newNode = new Node<T>;
    newNode->data = Elem;
    newNode->next = start;
    start = newNode;
}

template<typename T>
T Stack<T>::peek(){
    return start->data;
}

int main()
{
    Stack<int> st;
    st.push(1111);
    st.push(2222);
    st.push(3);
    cout << "should be 3 -> " << st.peek() << endl;
    st.pop();
    Stack<int> st2;
    st2 = st;
    return 0;
}