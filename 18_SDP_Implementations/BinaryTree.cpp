#include <iostream>

using namespace std;

template<typename T>
struct Node
{
    T data;
    Node<T>* left;
    Node<T>* right;
};

template<typename T>
class BinaryTree
{       
    public:
    BinaryTree();
    ~BinaryTree();
    BinaryTree(const BinaryTree<T>& other);
    BinaryTree<T>& operator=(const BinaryTree<T>& other);

    bool empty();
    void print() const;
    T rootTree() const;
    BinaryTree<T> leftTree() const;
    BinaryTree<T> rightTree() const;

    void addNode(const T& elem);
    void create();
    void create3(const T &elem, BinaryTree<T> &left, BinaryTree<T> &right);

    private:
    Node<T>* root;
    void copyHelper(Node<T>* &copyTo, const Node<T> * const &copyFrom) const;
    void copyTree(const BinaryTree<T>& other);
    void createTree(Node<T>*& root);
    void deleteTree(Node<T>*& root);
    void addHelper(Node<T>*& root, const T& elem);
    void pr(Node<T>* root) const;
};

template<typename T>
void BinaryTree<T>::copyHelper(Node<T>* &copyTo, Node<T> const * const &copyFrom) const
{
    copyTo = nullptr;
    if(copyFrom)
    {
        copyTo = new Node<T>;
        copyTo->data = copyFrom->data;
        copyHelper(copyTo->left, copyFrom->left);
        copyHelper(copyTo->right, copyFrom->right);
    }
}

template<typename T>
void BinaryTree<T>::copyTree(const BinaryTree<T>& other){
    copyHelper(root, other.root);
}

template<typename T>
void BinaryTree<T>::deleteTree(Node<T>*& root)
{
    if(root)
    {
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
        root = nullptr;
    }
}

template<typename T>
void BinaryTree<T>::createTree(Node<T>* &root){
    T info;
    char c;
    cout << "Root: ";
    cin >> info;
    root = new Node<T>;
    root->data = info; 
    root->left = nullptr;
    root->right = nullptr;
    cout << "Is there left tree from " << info <<" y/n?: " << endl;
    cin >> c;
    if(c == 'y') createTree(root->left);    
    cout << "Is there right tree from " << info <<" y/n?: " << endl;
    cin >> c;
    if(c == 'y') createTree(root->right);    
}

template<typename T>
BinaryTree<T>::BinaryTree()
{
    root = nullptr;
}

template<typename T>
BinaryTree<T>::~BinaryTree()
{
    deleteTree(root);
}

template<typename T>
BinaryTree<T>::BinaryTree(const BinaryTree<T>& other)
{
    copyTree(other);
}

template<typename T>
BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree<T>& other){
    if(this != &other)
    {
        deleteTree(root);
        copyTree(other);
    }
    return *this;
}

template<typename T>
void BinaryTree<T>::pr(Node<T>*root) const {
    if(root)
    {
        pr(root->left);
        cout << root->data << " ";
        pr(root->right);
    }
}

template<typename T>
bool BinaryTree<T>::empty(){
    return root == nullptr;
}

template<typename T>
void BinaryTree<T>::print() const
{
    pr(root);
    cout << endl;
}

template<typename T>
T BinaryTree<T>::rootTree() const{
    return root->data;
}

template<typename T>
BinaryTree<T> BinaryTree<T>::leftTree() const
{
    BinaryTree<T> result;
    if(root)
    {
        copyHelper(result.root, root->left);
    }
    return result;
}

template<typename T>
BinaryTree<T> BinaryTree<T>::rightTree() const
{
    BinaryTree<T> result;
    if(root)
    {
        copyHelper(result.root, root->right);
    }
    return result;
}

template<typename T>
void BinaryTree<T>::addHelper(Node<T>*&root, const T& elem){
    if(!root)
    {
        root = new Node<T>;
        root->data = elem;
        root->left = nullptr;
        root->right = nullptr;
    }
    else if(elem < root->data)
    {
        addHelper(root->left,elem);
    }
    else
    {
        addHelper(root->right,elem);
    }
}

template<typename T>
void BinaryTree<T>::addNode(const T& elem)
{
    addHelper(root, elem);
}

template<typename T>
void BinaryTree<T>::create() 
{
    root = nullptr;
    T info;
    char c;
    do
    {
        cout << "Add element:";
        cin >> info;
        addNode(info);
        cout << endl;
        cout << "Continue adding? y/n:";
        cin >> c;
    } while (c == 'y');
}

template<typename T>
void BinaryTree<T>::create3(const T& elem, BinaryTree<T>& leftTree, BinaryTree<T>& rightTree)
{
    if(root)
    {
        deleteTree(root);
    }
    root = new Node<T>;
    root->data = elem;
    copyHelper(root->left, leftTree.root);
    copyHelper(root->right, rightTree.root);
}

int main()
{
    BinaryTree<int> t1;
    t1.create();
    BinaryTree<int> t_error;
    t_error.leftTree();
    BinaryTree<int> t2 = t1;
    t1.print();
    t2.print();
    BinaryTree<int> t3 = t1.leftTree();
    t3.print();
    return 0;
}