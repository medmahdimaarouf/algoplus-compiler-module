#ifndef LIST_H
#define LIST_H
#include<iostream>
template  <class T>
class List:list
{
public:
    List();
    void append(const T &value);
};

#endif // LIST_H
