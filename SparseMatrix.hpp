#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H
#include<vector>
#include "./Node.hpp"

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
      clear();
      nuevo->clear();
      return nuevo;
    }
    else{
      cout<<"No se puede multiplicar"<<endl;
      return nullptr;
    }
  }

  SMatrix<T>* mult_escalar(float a){
    cout<<"La multiplicación escalar por "<<a<<" :\n";
      SMatrix<T>* nuevo = new SMatrix<T>(); 
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

  SMatrix<T>* add_sum(SMatrix<T> A){
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

  float determinant(){

  }

  SMatrix<T>* inverse(){
     if(this->determinant == 0) {cout<<"La determinante es 0, no existe la inversa \n";return nullptr;}     
    else{
      SMatrix <T>* nuevo = new SMatrix<T>();
    }
  }

  void print(){
    for (int i = 0; i < cols(); i++)
      {
          for (int j = 0; j < rows(); j++)
          {
              cout<<this->at(j,i)<<"\t";
          } 
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

#endif
