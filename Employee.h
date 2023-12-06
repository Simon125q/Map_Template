#pragma once

#include <iostream>

using namespace std;

class Employee
{
public:
    string name;
    string position;
    unsigned int age;
    Employee(string n, string p, unsigned int a)
        : name(n), position(p), age(a){};
};