#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H
#include<vector>
#include<math.h>
#include<iomanip>
#include "./Node.hpp"
#include <iostream>
#include "CImg.h"
using namespace cimg_library;
using namespace std;

template<typename T>
class SMatrix
{
private:
  Node<T> *root;
  vector<Node<T>*> icols;
  vector<Node<T>*> irows;
public:
  unsigned int rows(){return irows.size();}
  unsigned int cols(){return icols.size();}
  SMatrix()
  {
    root = new Node<T>(5, 0, 0);
    root->next = root;
    root->down = root;
    icols.push_back(root);
    irows.push_back(root);
  }
  ~SMatrix()
  {
    for(Node<T>* &i : icols)
    {
      Node<T>* temp = i->down;
      delete i;
      while(temp != i)
      {
        Node<T>* temp2 = temp;
        temp = temp->down;
        delete temp2;
      }
      i = nullptr;
    }
  }
  T& at(int y, int x)
  {
    if(y+1 > rows()){addrows(y-rows()+1);}
    if(x+1 > cols()){addcols(x-cols()+1);}
    Node<T> *row = irows[y];
    Node<T> *col = icols[x];
    while(row->next->x <= x && row->next != irows[y])
    {
      row = row->next;
    }
    while(col->down->y <= y && col->down != icols[x])
    {
      col = col->down;
    }
    if(col == row)
    {
      return col->data;
    }
    Node<T> *temp = new Node<T>(0, y, x);
    temp->next = row->next;
    row->next = temp;
    temp->down = col->down;
    col->down = temp;
    return temp->data;
  }
  void insert(int y,int x,T value){
    add(y,x,value);
  }
  void add(int y, int x, T value)
  {
    if(y+1 > rows()){addrows(y-rows()+1);}
    if(x+1 > cols()){addcols(x-cols()+1);}
    Node<T> *row = irows[y];
    Node<T> *col = icols[x];
    while(row->next->x <= x && row->next != irows[y])
    {
      row = row->next;
    }
    while(col->down->y <= y && col->down != icols[x])
    {
      col = col->down;
    }
    if(col == row)
    {
      col->data = value;
      return;
    }
    Node<T> *temp = new Node<T>(value, y, x);
    temp->next = row->next;
    row->next = temp;
    temp->down = col->down;
    col->down = temp;
  }
  void addcols(int x)
  {
    int max = icols.size()-1;
    while(x--)
    {
      Node<T> *temp = new Node<T>(0, 0, icols.size());
      icols.push_back(temp);
      icols.at(max)->next = icols.at(max+1);
      max++;
    }
    icols.at(icols.size()-1)->next = icols.at(0);
  }
  void addrows(int y)
  {
    int max = irows.size()-1;
    while(y--)
    {
      Node<T> *temp = new Node<T>(0, irows.size(), 0);
      irows.push_back(temp);
      irows.at(max)->down = irows.at(max+1);
      max++;
    }
    irows.at(irows.size()-1)->down = irows.at(0);
  }
  Node<T>* findrow(Node<T>* value)
  {
    Node<T>* temp = irows[value->y];
    while(temp->next->x < value->x && temp->next != icols[value->y])
    {
      temp = temp->next;
    }
    return temp;
  }
  void delnode(Node<T>* col, Node<T>* row)
  {
    Node<T>* temp = col->down;
    col->down = col->down->down;
    row->next = row->next->next;
    delete temp;
  }

//propios de matriz ----------------------------
 //SIn punteros
  SMatrix<T> multv(SMatrix<T> &A){
    if(cols() == A.rows()){
      cout<<"La multiplicación vectorial:\n";
      SMatrix<T> nuevo;
    for (int k = 0; k < A.cols(); k++)
    {  
      for (int i = 0; i < rows(); i++)
      {   T suma = 0;
        for (int j = 0; j < cols(); j++)
        {
            suma = suma+ (this->at(i,j)*A.at(j,k));
        }
          nuevo.add(i,k,suma);
      }
    }
      
      nuevo.clear();
      return nuevo;
    }
    else{
      throw invalid_argument("No se puede multiplicar");
    }
  }

  SMatrix<T> add_sums(SMatrix<T> &A){
    cout<<"Suma de matrices: \n";
    if(cols() == A.cols() && rows() == A.rows()){
      SMatrix<T> nuevo ; 
      for (int i = 0; i < cols(); i++)
      {
          for (int j = 0; j < rows(); j++)
          {
              nuevo.add(j,i,this->at(j,i)+A.at(j,i));
          } 
      }  
      clear();
      nuevo.clear();
      return nuevo;
    }
    else{
     throw invalid_argument("No se puede multiplicar");
    }
  }

  SMatrix<T> transposes(){
    cout<<"Transpuesta: \n";
    SMatrix<T> nuevo; 
    for (int i = 0; i < cols(); i++)
      {
          for (int j = 0; j < rows(); j++)
          {
              nuevo->add(i,j,this->at(j,i));
          } 
      }       
    clear();
    nuevo->clear();
    return nuevo;
  }


  SMatrix<double> inverse_s(){
    if(determinante() == 0) {cout<<"La determinante es 0, no existe la inversa \n";}     
    else{
      cout<<"Inversa: \n";
      SMatrix <double> inversa;
      inversa = this->adj()->mult_escalar(pow(this->determinante(),-1) );
      inversa.clear();
      return inversa;
    }
  }

  




// con retorno de punteros -----------------
  SMatrix<T>* multvec(SMatrix<T> A){
    if(cols() == A.rows()){
      cout<<"La multiplicación vectorial:\n";
      SMatrix<T>* nuevo = new SMatrix<T> ();
    for (int k = 0; k < A.cols(); k++)
    {  
      for (int i = 0; i < rows(); i++)
      {   T suma = 0;
        for (int j = 0; j < cols(); j++)
        {
            suma = suma+ (this->at(i,j)*A.at(j,k));
        }
          nuevo->add(i,k,suma);
      }
    }
      
      nuevo->clear();
      return nuevo;
    }
    else{
      cout<<"No se puede multiplicar"<<endl;
      return nullptr;
    }
  }

  SMatrix<double>* mult_escalar(double a){
    cout<<"La multiplicación escalar por "<<a<<" :\n";
      SMatrix<double>* nuevo = new SMatrix<double>(); 
      for (int i = 0; i < cols(); i++)
      {
          for (int j = 0; j < rows(); j++)
          {
              nuevo->add(j,i,this->at(j,i)*a);
          } 
      }    
      clear();
      nuevo->clear();
      return nuevo;
  }

  SMatrix<T>* add_sum(SMatrix<T> &A){
    cout<<"Suma de matrices: \n";
    if(cols() == A.cols() && rows() == A.rows()){
      SMatrix<T>* nuevo = new SMatrix<T>(); 
      for (int i = 0; i < cols(); i++)
      {
          for (int j = 0; j < rows(); j++)
          {
              nuevo->add(j,i,this->at(j,i)+A.at(j,i));
          } 
      }  
      clear();
      nuevo->clear();
      return nuevo;
    }
    else{
      cout<<"No se pueden sumar las matrices"<<endl;
      return nullptr;
    }

  }

  SMatrix<T>* transpose(){
    cout<<"Transpuesta: \n";
    SMatrix<T>* nuevo = new SMatrix<T>(); 
    for (int i = 0; i < cols(); i++)
      {
          for (int j = 0; j < rows(); j++)
          {
              nuevo->add(i,j,this->at(j,i));
          } 
      }       
    clear();
    nuevo->clear();
    return nuevo;
  }

  T determinante(){
    return deter(this);
  }

  T deter(SMatrix<T>* aux){
    
    if(rows()==cols()){
      auto orden = rows(); 
      T deter = 0;
      if(orden ==1) return this->at(0,0);
      else if (orden == 2) return (this->at(0,0)* this->at(1,1))-(this->at(0,1)* this->at(1,0));
      else {
        T suma = 0;
        for (int i = 0; i < cols(); i++) {
          suma = suma + (this->at(0, i) * (pow(-1, i)) * redu_ord(0, i)->determinante());
        }
        return suma;
      }
    }
    else{
      cout<<"No se puede hallar la determinante \n";
      return 0;
    }
  }

  SMatrix<double>* inverse(){
    if(determinante() == 0) {cout<<"La determinante es 0, no existe la inversa \n";return nullptr;}     
    else{
      cout<<"Inversa: \n";
      SMatrix <double>* inversa = new SMatrix<double>();
      inversa = this->adj()->mult_escalar(pow(this->determinante(),-1) );
      inversa->clear();
      return inversa;
    }
  }

  void print(){
    for (int i = 0; i < rows(); i++)
      {
          for (int j = 0; j < cols(); j++)
              cout<<setw(15)<<this->at(i,j); 
          cout<<endl;
      }  
    cout<<endl;
    clear();  
  }

  SMatrix<T>* cof(){
    return cofactor(this);
  }

  SMatrix<T>* cofactor(SMatrix<T>* aux){
    auto orden = rows();
    SMatrix<T>* cof = new SMatrix<T>();
    if(orden == 2){
        cof->add(0,0,aux->at(1,1));
        cof->add(0,1,-1*aux->at(1,0));
        cof->add(1,0,-1*aux->at(0,1));
        cof->add(1,1,aux->at(0,0));
        return cof;
    }    
    else{
      for (int i = 0; i < orden; i++)
      {
        for (int j = 0; j < orden; j++)
        {
           cof->add(i,j,(pow(-1,i+j))*(redu_ord(i,j))->determinante());   
        }  
      }  
      cof->clear();
      return cof;
    }       
  }
  SMatrix<T>* redu_ord(int pos_fil,int pos_col){
    auto orden = this->cols();
    if(orden ==2){
      return this;
    }
    else
    {  SMatrix<T>* nuevo = new SMatrix<T>();     
      vector<T> aux;
      for (int i = 0; i < orden; i++)
            { if (i == pos_fil)continue;
                for (int j = 0; j < orden; j++)
                {
                    if (j==pos_col)continue;
                    aux.push_back(this->at(i,j));
                }
            }
        for(int j = 0;j<orden-1;j++){
          for(int i =0;i<(orden-1);i++)
            nuevo->add(j,i,aux[j*(orden-1)+i]);
        }

      nuevo->clear();
      return nuevo;
    } 
  }

  SMatrix<T>* adj(){
    SMatrix<T>* adj = new SMatrix<T>();
    adj = (this->cof())->transpose();
    adj->clear();
    return adj;
  }
  void clear();

  
};

template<typename T>
void SMatrix<T>::clear()
{
  for(auto it = icols.begin()+1; it != icols.end();  it++)
  {
    Node<T>* temp = *it;
    while(temp->down != *it)
    {
      if(temp->down->data == 0 && temp->down->y != 0)
      {
        delnode(temp, findrow(temp->down));
      }
      temp = temp->down;
    }
  }
}

template<typename T>
ostream& operator << (ostream &os, SMatrix<T> &p)
{
    for (int i = 0; i < p.rows(); i++)
      {
          for (int j = 0; j < p.cols(); j++)
              os<<setw(15)<<p.at(i,j); 
          os<<"\n";
      }  
    p.clear();
    
    return os;
}

template<typename T>
ostream& operator << (ostream &os, SMatrix<T>* &p)
{
    for (int i = 0; i < p->rows(); i++)
      {
          for (int j = 0; j < p->cols(); j++)
              os<<setw(15)<<p->at(i,j); 
          os<<"\n";
      }  
    p->clear();
    
    return os;
}

template<typename T>
SMatrix<T>& load_from_image(string name)
{
  SMatrix<T> val;
  CImg<unsigned char> img(name.c_str());
  for(int i = 0; i < img.width(); i++)
  {
    for(int j = 0; j < img.height(); j++)
    {
      val.at(i, j) = img(i, j);
    }
  }
  return val;
}

#endif
