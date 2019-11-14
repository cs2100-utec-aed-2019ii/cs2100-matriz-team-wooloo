/*#include <iostream>
#include "Sparsematrix.hpp"
#include <time.h>
using namespace std;


int main( int, char * [])

{
   srand(time(NULL));
   SparseMatrix<double> m1;
   for(int i= 0; i < 100; i++)
     m1.insert(rand()%100,rand()%100,rand()%250);//(f,c,val)    cout << m1 << endl; // print in console
   m1.erase(100,2); // delete(f,c)    SparseMatrix<double> m2 = SparseMatrix<double>::identity(m1.f,m1.f); //f,c
   ofstream _out("res.txt");
   _out << m2 << endl; // print in file
   _out.close();    cout << mult(m1,m2) << endl; //  mutiplication
   cout << add(m1,m2) << endl; // addition
   cout << transpose(m1) << endl; // transpose    cout << inv(m1) << endl; // Inversa - Extra!      // Cargar desde imagen -  Extra (Usar CImg.h)
   SparseMatrix<double> m_image = load_from_image("lenna.jpg");//512x512
   ofstream _out_i("res.txt");
   _out_i << m_image;
   _out_i.close()    return 1; */

#include "./SparseMatrix.hpp"
#define NORMAL
  

int main()
{
  SMatrix<double> a;
  SMatrix<double> b;
#ifdef NORMAL
  a.add(0, 0, 1);
  a.add(0, 1, 2);
  a.add(1, 0, 3);
  a.add(1, 1, 4);

  b.add(0, 0, 3);
  b.add(0, 1, 1);
  b.add(0, 2, 4);
  b.add(1, 0, -1);
  b.add(1, 1, 2);
  b.add(1, 2, 1);
  b.add(2, 0, 3);
  b.add(2, 1, 2);
  b.add(2, 2, 1);
#else
  a.at(0,0) = 1;
  a.at(0,1) = 2;
  a.at(1,0) = 3;
  a.at(1,1) = 4;
#endif
  srand(time(NULL));
   SMatrix<double> m1;
   for(int i= 0; i < 100; i++)
     m1.insert(rand()%4,rand()%4,rand()%250);    
  
  
  m1.print();
  m1.inverse_s().print();
  m1.add_sums(m1).print();
  m1.multv(m1).print();
  m1.clear();

 

  
  
  //cout<<a.multvec(a)->determinant()<<endl;
 /* for(int i = 0; i < 100; i++)
  {
    for(int j = 0; j < 100; j++)
    {
      a.at(i, j) = i+j;
      //a.add(i, j, i+j);
    }
// }*/

  //d->clear();
  a.clear();
  b.clear();
  return 0;
}
