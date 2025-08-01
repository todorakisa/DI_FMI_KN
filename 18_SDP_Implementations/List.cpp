#include <stdio.h>
#include <iostream>

using namespace std;

template<typename T>
struct Node
{
    T data;
    Node<T>* next;
};

template<typename T>
class List 
{
    public:
    List();
    List(const List<T>& other);
    ~List();
    List<T>& operator=(const List<T>& other);
    void removeFirst();
    void removeAt(int index);
    void insertBegining(T Elem);
    void insertAt(T Elem, int index);
    bool isEmpty();
    void print() const;

    private:
    Node<T>* head;
    void copyList(const List<T> &other); 
    void deleteList(); 
};

template<typename T>
void List<T>::copyList(const List<T> &other)
{
    if(other.head)
    {
        Node<T> *tmp_other_head = other.head;
        this->head = new Node<T>;
        this->head->data = other.head->data;
        Node<T> *tmp_my_head = this->head;
        tmp_other_head = tmp_other_head->next;

        while (tmp_other_head)
        {
            Node<T> *newNode = new Node<T>;
            newNode->data = tmp_other_head->data;
            tmp_my_head->next = newNode;
            tmp_my_head = tmp_my_head->next;
            tmp_other_head = tmp_other_head->next;
        } 
        tmp_my_head->next = nullptr;
    }
    else
    {
        head = nullptr;
    }
}

template<typename T>
void List<T>::removeFirst()
{
    if(head)
    {
        Node<T>* tmp = head;
        head = head->next;
        delete tmp;
    }
}

template<typename T>
void List<T>::print() const
{
    cout << "List: ";
    Node<T>* tmp = this->head;
    while (tmp)
    {
        cout << "[" << tmp->data << "] ";
        tmp = tmp->next;
    }
    cout << endl;
}

template<typename T>
void List<T>::deleteList()
{
    cout << "Destructor: [ ";
    while (head)
    {
        Node<T>* tmp = head;
        head = head->next;
        cout << tmp->data << " ";
        delete tmp;
    }
    cout << "]" << endl;
}

template<typename T>
void List<T>::insertBegining(T Elem)
{
    Node<T>* newElem = new Node<T>;
    newElem->data = Elem;
    newElem->next = this->head;
    this->head = newElem;
}

template<typename T>
List<T>::List()
{
    head = nullptr;
}

template<typename T>
List<T>::~List(){
    deleteList();
}

template<typename T>
bool List<T>::isEmpty(){
    if(head == nullptr)
    {
        return true;
    }
    else
    {
        return false;
    }
}


template<typename T>
List<T>& List<T>::operator=(const List<T>& other)
{
    if(this != &other)
    {
        deleteList();
        copyList(other);
    }

    return *this;
}

template<typename T> 
List<T>::List(const List<T>& other)
{
    copyList(other);
}

template<typename T>
void List<T>::insertAt(T Elem, int index)
{
    if(index < 0)
    {
        cout << "Error: negative index" << endl;
        return;
    }
    else if(index == 0)
    {
        insertBegining(Elem);
    }
    else
    {
        Node<T>* current = this->head;
        while (index > 0)
        {
            current = current->next;
            if(!current)
            {
                cout << "Error: too big index" << endl;
                return;
            }
            index--;
        }

        Node<T>* newNode = new Node<T>;
        newNode->data = Elem;
        if(current->next)
        {
            newNode->next = current->next->next;
        }
        else
        {
            newNode->next = nullptr;
        }
        current->next = newNode;
    }
}

template<typename T>
void List<T>::removeAt(int index)
{
    if(index < 0)
    {
        cout << "Error: negative index" << endl;
        return;
    }
    else if(index == 0)
    {
        removeFirst();
    }
    else
    {
        Node<T>* current = this->head;
        while (index > 1)
        {
            current = current->next;
            if(!current || !current->next)
            {
                cout << "Error: too big index" << endl;
                return;
            }
            index--;
        }

        if(current->next->next)
        {
            Node<T>* continueNode = current->next->next;
            delete current->next;
            current-> next = continueNode;
        }
        else
        {
            delete current->next;
            current->next = nullptr;
        }
    }
}

int main ()
{
    List<int> myIntList;
    myIntList.insertBegining(5);
    List<int> myIntList2 = myIntList;
    myIntList.insertBegining(4);
    myIntList.insertBegining(3);
    myIntList.insertBegining(2);
    myIntList.insertBegining(1);
    myIntList.print();
    myIntList.removeFirst();
    myIntList2.insertBegining(5);
    myIntList2.insertBegining(5);
    myIntList2.print();
    List<int> copconst(myIntList2);
    copconst.insertAt(111, 2);
    copconst.print();
    copconst.removeAt(2);
    copconst.print();
    myIntList2 = myIntList;
    List<int> patka;
    myIntList2 = patka;
    cout << "Is List empty: " << myIntList.isEmpty() << endl;
    return 0;
}