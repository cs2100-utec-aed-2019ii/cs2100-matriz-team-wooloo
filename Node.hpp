#ifndef NODE_H
#define NODE_H
#include <iostream>
using namespace std;

template <class T>
struct Node {
  T data;
  int x;
  int y;
  Node<T>* next;
  Node<T>* down;
  Node(T _data, int _y, int _x): data(_data), x(_x), y(_y), next(this), down(this){}
  ~Node(){}
};

#endif
