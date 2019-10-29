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
        Node():posX(0),posY(0),next(nullptr),down(nullptr){}
        ~Node(){ 
        }
};


#endif