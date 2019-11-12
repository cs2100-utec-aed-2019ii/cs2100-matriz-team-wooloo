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
        Node(int p_x,int p_y,T dato):posX(p_x),posY(p_y),next(nullptr),down(nullptr),data(dato){}
        ~Node(){ 
        }
};


#endif