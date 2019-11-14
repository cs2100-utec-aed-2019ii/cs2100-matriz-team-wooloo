#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H
#include<vector>
#include<math.h>
#include<iomanip>
#include "./Node.hpp"
#include <iostream>
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

SMatrix<double> identity(int i,int j){
    if(i == j){
        SMatrix<double> nuevo;
        for (int k = 0; k < i; k++)
        {
          nuevo.add(k,k,1);
        }
        return nuevo;
    }
    else throw invalid_argument("No se puede crear");
}

  SMatrix<T> multv(SMatrix<T> &A){
    if(cols() == A.rows()){
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
    SMatrix<T> nuevo; 
    for (int i = 0; i < cols(); i++)
      {
          for (int j = 0; j < rows(); j++)
          {
              nuevo.add(i,j,this->at(j,i));
          } 
      }       
    clear();
    nuevo.clear();
    return nuevo;
  }


  SMatrix<double> inverse_s(){
    if(determinante_s() == 0) {cout<<"La determinante es 0, no existe la inversa \n";return *this;}     
    else{
      SMatrix <double> inversa = this->adj_s().mult_escalar_s(pow(this->determinante_s(),-1) );
      inversa.clear();
      return inversa;
    }
  }

  SMatrix<double> mult_escalar_s(double a){
      SMatrix<double> nuevo; 
      for (int i = 0; i < cols(); i++)
      {
          for (int j = 0; j < rows(); j++)
          {
              nuevo.add(j,i,this->at(j,i)*a);
          } 
      }    
      clear();
      nuevo.clear();
      return nuevo;
  }


  T determinante_s(){
    if(rows()==cols()){
      auto orden = rows(); 
      T deter = 0;
      if(orden ==1) return this->at(0,0);
      else if (orden == 2) return (this->at(0,0)* this->at(1,1))-(this->at(0,1)* this->at(1,0));
      else {
        T suma = 0;
        for (int i = 0; i < cols(); i++) {
          suma = suma + (this->at(0, i) * (pow(-1, i)) * redu_ord_s(0, i).determinante_s());
        }
        return suma;
      }
    }
    else{
      cout<<"No se puede hallar la determinante \n";
      return 0;
    }
  }

  SMatrix<T> cof_s(){
    return cofactor_s(this);
  }

  SMatrix<T> cofactor_s(SMatrix<T> *aux){
    auto orden = rows();
    SMatrix<T> cof;
    if(orden == 2){
        cof.add(0,0,aux->at(1,1));
        cof.add(0,1,-1*aux->at(1,0));
        cof.add(1,0,-1*aux->at(0,1));
        cof.add(1,1,aux->at(0,0));
        return cof;
    }    
    else{
      for (int i = 0; i < orden; i++)
      {
        for (int j = 0; j < orden; j++)
        {
           cof.add(i,j,(pow(-1,i+j))*(redu_ord_s(i,j)).determinante_s());   
        }  
      }  
      cof.clear();
      return cof;
    }       
  }
  SMatrix<T> redu_ord_s(int pos_fil,int pos_col){
    auto orden = this->cols();
    if(orden ==2){
      return *this;
    }
    else
    {  SMatrix<T> nuevo;     
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
            nuevo.add(j,i,aux[j*(orden-1)+i]);
        }
      nuevo.clear();
      return nuevo;
    } 
  }

  SMatrix<T> adj_s(){
    SMatrix<T> adj = (this->cof_s()).transposes();
    adj.clear();
    return adj;
  }
 
  void print(){
    for (int i = 0; i < rows(); i++)
    {
      for (int j = 0; j < cols(); j++)
      cout<<setw(rows()*3)<<at(i,j);
      cout<<endl;
    }
    cout<<endl;
    clear();
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
              os<<setw(p.rows()*3)<<p.at(i,j); 
          os<<"\n";
      }  
      os<<"\n";
    p.clear();
    
    return os;
}

//template<typename T>
//ostream& operator << (ostream &os, SMatrix<T>* &p)
//{
//    for (int i = 0; i < p->rows(); i++)
//      {
//          for (int j = 0; j < p->cols(); j++)
//              os<<setw(15)<<p->at(i,j); 
//          os<<"\n";
//      }  
//    p->clear();
//    
//    return os;
//}



  template<class T>
  SMatrix<T> mult(SMatrix<T> &A,SMatrix<T>&B){
      return A.multv(B);
  }
  template<class T>
  SMatrix<T> add(SMatrix<T> &A,SMatrix<T>&B){
      return A.add_sums(B);
  }
  template<class T>
  SMatrix<T> transpose(SMatrix<T> &A){
      return A.transposes();
  }

  template<class T>
  SMatrix<double> inv(SMatrix<T> &A){
      return A.inverse_s();
  }
  SMatrix<double> identity(int a,int b){
    if(a==b){
      SMatrix<double> nuevo;
      for (int i = 0; i < a; i++)
      {
          nuevo.add(i,i,1);
      }
      nuevo.clear();
      return nuevo;
    }
    else throw invalid_argument("No se puede porque las dimensiones no son iguales");
  }

#endif
