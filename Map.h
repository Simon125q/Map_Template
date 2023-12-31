#pragma once

#include <iostream>

#define TEST 0

using namespace std;

template <typename K_type, typename V_type>
class Map
{
    struct Node;
    Node *root;
    int size = 0;

public:
    Map()
        : root(nullptr), size(0){};
    Map(Map &other);
    ~Map();
    Map &operator=(Map &other);
    void add(K_type key, V_type value);
    V_type *find(K_type key);
    int getSize();
    void inOrderPrint(ostream &os, Node *n) const;
    Node *copy(Node *root);

    friend ostream &operator<<(ostream &os, const Map<K_type, V_type> &obj)
    {
        obj.inOrderPrint(os, obj.root);
        return os;
    };

    struct KeyAlreadyExistsException;
    struct KeyNotFoundException;
};

template <typename K_type, typename V_type>
Map<K_type, V_type>::Map(Map &other)
{
    if (TEST)
        cout << "copy constructor" << endl;
    this->root = this->copy(other.root);
    this->size = other.size;
}

template <typename K_type, typename V_type>
Map<K_type, V_type>::~Map()
{
    if (TEST)
        cout << "Map destructor" << endl;
    delete root;
}

template <typename K_type, typename V_type>
Map<K_type, V_type> &Map<K_type, V_type>::operator=(Map &other)
{
    if (TEST)
        cout << "Map assigment operator" << endl;
    delete root;
    this->size = other.size;
    this->root = this->copy(other.root);
    return *this;
}

template <typename K_type, typename V_type>
void Map<K_type, V_type>::add(K_type key, V_type value)
{
    if (TEST)
        cout << "add" << endl;
    if (root == nullptr)
    {
        root = new Node(key, value);
    }
    else
        root->insert(key, value);
    this->size++;
}

template <typename K_type, typename V_type>
V_type *Map<K_type, V_type>::find(K_type key)
{
    if (TEST)
        cout << "find" << endl;
    if (root != nullptr)
        return root->search(key);
    else
        throw KeyNotFoundException();
}

template <typename K_type, typename V_type>
int Map<K_type, V_type>::getSize()
{
    return this->size;
}

template <typename K_type, typename V_type>
void Map<K_type, V_type>::inOrderPrint(ostream &os, Map<K_type, V_type>::Node *n) const
{
    if (TEST)
        cout << "in order print" << endl;
    if (n == nullptr)
    {
        return;
    }
    this->inOrderPrint(os, n->left);
    os << n->key << "-> " << n->value << ", " << endl;
    this->inOrderPrint(os, n->right);
}

template <typename K_type, typename V_type>
typename Map<K_type, V_type>::Node *Map<K_type, V_type>::copy(typename Map<K_type, V_type>::Node *root)
{
    if (TEST)
        cout << "copy" << endl;

    if (root == nullptr)
    {
        return nullptr;
    }

    Node *root_copy = new Node(root->key, root->value);

    root_copy->left = this->copy(root->left);
    root_copy->right = this->copy(root->right);

    return root_copy;
}

// Node -----------------------------------------------

template <typename K_type, typename V_type>
struct Map<K_type, V_type>::Node
{
    K_type key;
    V_type value;
    Node *left;
    Node *right;
    Node(K_type k, V_type val)
        : key(k), value(val), left(nullptr), right(nullptr){};
    ~Node()
    {
        if (left != nullptr)
            delete left;
        if (right != nullptr)
            delete right;
    }

    void insert(K_type key, V_type value)
    {
        if (TEST)
            cout << "node insert" << endl;
        if (key == this->key)
            throw KeyAlreadyExistsException();
        if (key > this->key)
        {
            if (right != nullptr)
                right->insert(key, value);
            else
            {
                right = new Node(key, value);
            }
        }
        else
        {
            if (left != nullptr)
                left->insert(key, value);
            else
            {
                left = new Node(key, value);
            }
        }
    }

    V_type *search(K_type key)
    {
        if (TEST)
            cout << "node search" << endl;
        if (key == this->key)
            return &(this->value);
        else if (key > this->key)
        {
            if (right != nullptr)
                return right->search(key);
            else
                throw KeyNotFoundException();
        }
        else
        {
            if (left != nullptr)
                return left->search(key);
            else
                throw KeyNotFoundException();
        }
    }
};

template <typename K_type, typename V_type>
struct Map<K_type, V_type>::KeyAlreadyExistsException : public exception
{
    const char *what() const throw()
    {
        return "Element with that key already in map";
    }
};

template <typename K_type, typename V_type>
struct Map<K_type, V_type>::KeyNotFoundException : public exception
{
    const char *what() const throw()
    {
        return "Element with this key not found in map";
    }
};