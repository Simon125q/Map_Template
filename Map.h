#pragma once

#include <iostream>

using namespace std;

template <typename K_type, typename V_type>
class Map
{
    struct Node
    {
        K_type key;
        V_type value;
        Node *next;
        Node(K_type k, V_type val)
            : key(k), value(val), next(nullptr);
    };

    Node *head;

public:
    Map()
        : head(nullptr);
    Map(Map &other);
    ~Map();
    Map &operator=(Map &other);
    void add(K_type key, V_type value);
    V_type *find(K_type key);
    int size();
    void clear();

    friend ostream &operator<<(ostream &os, const Map &obj);
};
