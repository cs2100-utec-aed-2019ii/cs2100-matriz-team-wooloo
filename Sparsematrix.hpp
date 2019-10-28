#ifndef SPARSE_H
#define SPARSE_H
#include "Node.hpp"

template <class T>
class SparseMatrix {
      private:
              Node<T>* x;
              Node<T>* y;
              int columns;
              int rows;
};

#endif