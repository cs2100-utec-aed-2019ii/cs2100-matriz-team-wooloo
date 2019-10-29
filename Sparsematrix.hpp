#ifndef SPARSE_H
#define SPARSE_H
#include "Node.hpp"
#include <iostream>
using namespace std;

template <class T>
class SparseMatrix {
      private:
              Node<T>* x;
              Node<T>* y;
              int columns;
              int rows;

      public:
      friend ostream& operator<<(ostream& os, const SparseMatrix<T>& ia);
      friend istream& operator>>(istream& is, SparseMatrix<T>& ia);
      SparseMatrix():x(nullptr),y(nullptr),columns(0),rows(0){}     
      ~SparseMatrix(){}
      int tam_column(){return columns;}
      int tam_rows(){return rows;}
      
      void insert(){

      }

      SparseMatrix& mult(){

      }

      SparseMatrix& add(){
          
      }
      SparseMatrix& transpose(){
          
      }

};
    template<class T>
    ostream& operator << (ostream &os,const SparseMatrix<T> &p)
    {
    for (int i = 0; i < p.columns; i++)
        {
        for (int j= 0; j < p.rows; j++)
            {
                os<<p.x->data;
            }
        }

    return os;
    }

    template<class T>
    istream& operator >> (istream &is, SparseMatrix<T> &p)
    {
    
    is >> p.a >> p.b;
    is.ignore();
    return is;
    }



#endif