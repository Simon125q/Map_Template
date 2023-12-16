#pragma once

#include <iostream>

using namespace std;

class BookCard
{
public:
    string name;
    string author;
    string category;
    unsigned int number_of_pages;
    bool borrowed;

    BookCard(string n, string aut, string cat, unsigned int p_num, bool borr)
        : name(n), author(aut), category(cat), number_of_pages(p_num), borrowed(borr){};

    friend ostream &operator<<(ostream &os, const BookCard &obj)
    {
        os << "Author: " << obj.author << ", Category: " << obj.category << ", Number of pages: "
           << obj.number_of_pages << ", Borrowed: " << obj.borrowed << " ";

        return os;
    }
};
