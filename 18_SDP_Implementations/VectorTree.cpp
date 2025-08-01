#include <iostream>
#include <vector> 

using namespace std;

template<typename T>
struct Node
{
    T data;
    vector<Node<T>*> successors;
};

template<typename T>
class Tree
{
    public:
    Tree();
    ~Tree();
    Tree(const Tree<T>& other);
    Tree<T>& operator=(const Tree<T>& other);

    bool empty() const;
    void print() const;
    T rootTree() const;
    Tree<T> nthTree(int n) const;

    void create();

    private:
    Node<T>* root;
    void copyHelper(Node<T>* &copyTo, Node<T>* &copyFrom);
    void copyTree(const Tree<T>& other);
    void deleteTree(Node<T>* &root);
    void pr(Node<T>* root) const;
    void createTree(Node<T>* &root);
};

template<typename T>
void Tree<T>::copyHelper(Node<T>* &copyTo, Node<T>* &copyFrom)
{
    copyTo = nullptr;
    if(copyFrom)
    {
        copyTo = new Node<T>;
        copyTo->data = copyFrom->data;
        int vectorSize = copyFrom->successors.size();
        for (int i = 0; i < vectorSize; i++)
        {
            Node<T>* newNode = new Node<T>;
            copyHelper(newNode, copyFrom->successors[i]);
            copyTo->successors.push_back(newNode);
        }
    }
}

template<typename T>
void Tree<T>::copyTree(const Tree<T>& other){
    copyHelper(root, other.root);
}

template<typename T>
void Tree<T>::deleteTree(Node<T>*&arg_root){
    if(arg_root)
    {
        int vectorSize = arg_root->successors.size();
        for (int i = 0; i < vectorSize; i++)
        {
            deleteTree(arg_root->successors[i]);
        }
        arg_root->successors.clear();
        delete arg_root;
        arg_root = nullptr;
    }
}

template<typename T>
void Tree<T>::pr(Node<T>*rt) const 
{   
    if(rt)
    {
        cout << rt->data << " ";
        vectorSize = rt->successors.size();
        for (int i = 0; i < vectorSize; i++)
        {
            pr(rt->successors[i]);   
        }
    }
}

template<typename T>
void Tree<T>::createTree(Node<T>*&rt)
{
    delete rt;
    T info;
    char c;
    cout << "Root: ";
    cin >> info;
    rt = new Node<T>;
    rt->data = info;
    do
    {  
       cout << "Do you want to add child of node: " << info << " y/n?" << endl;
       cin >> c;
       if(c == 'y')
       {
        Node<T>* newNode = new Node<T>;
        createTree(newNode);
        rt->successors.push_back(newNode);
       } 
    } while (c == 'y');
        
}

template<typename T>
Tree<T>::Tree()
{
    root = nullptr;
}

template<typename T>
Tree<T>::~Tree()
{
    deleteTree(root);
}

template<typename T>
Tree<T>::Tree(const Tree<T>& other){
    copyTree(other);
}

template<typename T>
Tree<T>& Tree<T>::operator=(const Tree<T>& other)
{
    if(this != &other)
    {
        deleteTree(root);
        copyTree(other);
    }
    return *this;
}

template<typename T>
bool Tree<T>::empty() const
{
    return root == nullptr;
}

template<typename T>
void Tree<T>::print() const {
    pr(root);
    cout << endl;
}

template<typename T>
T Tree<T>::rootTree() const {
return root->data;
}

template<typename T>
Tree<T> Tree<T>::nthTree(int index) const
{
    Tree<T> result;
    if(!root)
    {
        cout << "the tree is empty" << endl;
    }
    else if(index < 0 || index > root->)
    {
        cout << "Incorrect index" << endl;
        return result;
    }
    copyHelper(root, result->successors[index]);
    return result;
}

template<typename T>
void Tree<T>::create(){
    createTree(root);
}

int main()
{
    return 0;
}