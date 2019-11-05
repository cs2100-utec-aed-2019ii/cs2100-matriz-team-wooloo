#ifndef NODE_H
#define NODE_H

template <class T>
class Node {
public:
  T data;
  int posX;
  int posY;
  Node<T>* next;
  Node<T>* down;
};


#endif
