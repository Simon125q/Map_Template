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
    friend ostream &operator<<(ostream &os, const Employee &obj);
};

ostream &operator<<(ostream &os, const Employee &obj)
{
    os << "Employee: "
       << "name - " << obj.name << ", age - " << obj.age << ", position - " << obj.position;
    return os;
}