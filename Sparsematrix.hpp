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
      
      void insert(int columna,int fila, T dato){
          Node<T>* aux_x = x;Node<T>* aux_y = y;
          while (aux_x)
          {
            
            aux_x->next;
          }
          
      }

      SparseMatrix& mult(){
          
      }

      SparseMatrix& add(){
          
      }
      
      void erase(int _x,int _y){
        
      }

      SparseMatrix& transpose(SparseMatrix<T>m1){
          for (int i = 0; i < m1.tam_column; i++)
          {
              for (int j = 0; j < count; j++)
              {
                  /* code */
              }
          } // opcion
          
          //cambio de coordenadas
      }

      void swap(T &a,T &b){
          auto temp = a;
          a = b;
          b = temp;
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
    ostream& operator<<(ostream &out, SparseMatrix<T> m){
    out << m(0,0);
    return out;
    }

    template<class T>
    istream& operator >> (istream &is, SparseMatrix<T> &p)
    {
    
    is >> p.a >> p.b;
    is.ignore();
    return is;
    }



#endif