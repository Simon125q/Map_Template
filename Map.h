#pragma once

#include <iostream>

using namespace std;

template <typename K_type, typename V_type>
class Map
{
    struct Node;
    struct KeyAlreadyExistsException;
    struct KeyNotFoundException;
    Node *root;
    int size;

public:
    Map()
        : root(nullptr), size(0);
    Map(Map &other);
    ~Map();
    Map &operator=(Map &other);
    void add(K_type key, V_type value);
    V_type *find(K_type key);
    int size();
    void clear();

    friend ostream &operator<<(ostream &os, const Map &obj);
};

template <typename K_type, typename V_type>
void Map<K_type, V_type>::add(K_type key, V_type value)
{
    size++;
    if (root == nullptr)
    {
        root->key = key;
        root->value = value;
    }
    else
        root->insert(key, value);
}

template <typename K_type, typename V_type>
V_type *Map<K_type, V_type>::find(K_type key)
{
    if(root != nullptr)
        return root->search(key);
    else
        throw KeyNotFoundException;
}

template <typename K_type, typename V_type>
struct Map<K_type, V_type>::Node
{
    K_type key;
    V_type value;
    Node *left;
    Node *right;
    Node(K_type k, V_type val)
        : key(k), value(val), left(nullptr), right(nullptr);

    void insert(K_type key, V_type value)
    {
        if (key == this->key)
            throw KeyAlreadyExistException;
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

    V_type* search(K_type key)
    {
        if (key == this->key)
            return &(this->value);
        else if (key > this->key)
        {
            if (right != nullptr)
                return right->search(key);
            else    
                throw KeyNotFoundException;
        }
        else
        {
            if (left != nullptr)
                return left->search(key);
            else    
                throw KeyNotFoundException;
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