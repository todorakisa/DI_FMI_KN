#include <iostream>

using namespace std;

template<typename T>
struct Node{
    T data;
    Node<T>* next;
    Node<T>* prev;
};

template<typename T>
class DLL
{
    public:
    DLL();
    ~DLL();
    DLL(const DLL<T>& other);
    DLL<T>& operator=(const DLL<T>& other);

    void insertFirst(T Elem);
    void insertAt(T Elem, int index);
    void insertAtEnd(T Elem);
    void removeFirst();
    void removeAt(int index);
    bool empty();
    void print() const;

    private:
    Node<T> *head;
    void copyList(const DLL<T>& other);
    void deleteList();
};

template<typename T>
void DLL<T>::copyList(const DLL<T>& other)
{
    if(other.head)
    {
        Node<T>* other_head = other.head;
        head = new Node<T>;
        head->data = other_head->data;
        head->next = nullptr;
        head->prev = nullptr;
        Node<T>* our_head = head;
        other_head = other_head->next;

        while (other_head)
        {
            Node<T>* newNode = new Node<T>;
            newNode->data = other_head->data;
            newNode->prev = our_head;
            our_head->next = newNode;
            our_head = our_head->next;
            other_head = other_head->next;
        }
        our_head->next = nullptr;
    }
}

template<typename T>
void DLL<T>::deleteList(){
    if(head)
    {
        cout << "Destructor of: " << head->data << endl;
        while (head)
        {
            Node<T>* tmp = head;
            head = head->next;
            delete tmp;        
        }
    }
}

template<typename T>
DLL<T>::DLL()
{
    head = nullptr;
}

template<typename T>
DLL<T>::~DLL()
{
    deleteList();
}

template<typename T>
DLL<T>::DLL(const DLL<T>& other)
{
    copyList(other);
}

template<typename T>
DLL<T>& DLL<T>::operator=(const DLL<T>& other)
{
    if(this != &other)
    {
        deleteList();
        copyList(other);
    }
    return *this;
}

template<typename T>
bool DLL<T>::empty(){
    return head == nullptr;
}

template<typename T>
void DLL<T>::insertFirst(T Elem){
    if(!head)
    {
        head = new Node<T>;
        head->data = Elem;
        head->next = nullptr;
        head->prev = nullptr;
    }else{
        Node<T>* newHead = new Node<T>;
        newHead->data = Elem;
        newHead->prev = nullptr;
        newHead->next = head;
        head = newHead;
    }
}

template<typename T>
void DLL<T>::insertAtEnd(T Elem){
    if(!head){
        insertFirst(Elem);
    }else{
        Node<T>* current = head;
        while (current->next)
        {
            current = current->next;
        }
        Node<T>* newNode = new Node<T>;
        newNode->data = Elem;
        newNode->next = nullptr;
        newNode->prev = current;
        current->next = newNode;
    }
}

template<typename T>
void DLL<T>::insertAt(T Elem, int index)
{
    if(index == 0)
    {
        insertFirst(Elem);
    }
    else if(index < 0)
    {
        cout << "Error: Invalid index" << endl;
        return;
    }
    else
    {
        Node<T>* current = head;
        while (index > 0)
        {
            if(!current)
            {
                cout << "Error: too big index" << endl;
            }
            current = current->next;
            index--;
        }
        Node<T>* newNode = new Node<T>;
        newNode->data = Elem;
        if(current->next){
            newNode->next = current->next;
            current->next->prev = newNode;
        }else{
            newNode->next = nullptr;
        }
        newNode->prev = current;
        current->next = newNode;
    }
}

template<typename T>
void DLL<T>::removeFirst()
{
    if(head)
    {
        Node<T>* tmp = head;
        head = head->next;
        if(head) head->prev = nullptr;
        delete tmp;
    }
}

template<typename T>
void DLL<T>::removeAt(int index)
{
    if(index < 0)
    {
        cout << "Error: Negative Index not possible" << endl;
    }
    else if(index == 0)
    {
        removeFirst();
    }
    else
    {
        index--;
        Node<T>* current = head;
        while (index > 0)
        {
            current = current->next;
            if(!current){
                cout << "Error: out of range" << endl;
            }
            index--;
        }
        Node<T>* nodeToDelete = current->next;
        current->next = current->next->next;
        current->next->prev = current;
        delete nodeToDelete;
    }
}

template<typename T>
void DLL<T>::print() const
{
    if(head)
    {
        cout << "[";
        Node<T>* current = head;
        while (current)
        {
            cout << current->data << " ";
            current = current->next;
        }
        cout << "]" << endl;
    }
}

int main()
{
    DLL<int> l;
    cout << l.empty() << endl;
    l.insertFirst(5);
    cout << l.empty() << endl;
    l.print();
    l.removeFirst();
    l.print();
    l.removeFirst();
    l.print();
    l.insertAt(6,0);
    l.insertAt(7,0);
    l.print();
    l.insertAtEnd(9);
    l.insertFirst(10);
    l.print();
    l.removeAt(1);
    l.print();
    DLL<int> l2 = l;
    l2.print();
    return 0;
}