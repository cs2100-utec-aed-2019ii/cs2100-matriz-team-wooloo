#include <iostream>
#include "Sparsematrix.hpp"
using namespace std;

int main( int, char * []) 
{
    SparseMatrix<double> m1;
    m1 << (2,0,0) << (8,0,1) << (6,1,0) << (100,2,20);  // Insert
    cout << m1 << endl; // print in console
    m1 >> (100,2,20); // delete
    
    SparseMatrix<double> m2 = SparseMatrix<double>::identity(100,100); 
    ofstream _out("res.txt");
    _out << m2 << endl; // print in file
    _out.close();

    cout << mult(m1 * m2) << endl; //  mutiplication
    cout << add(m1 + m2) << endl; // addition
    cout << transpose(m1) << endl; // transpose

    cout << inv(m1 * m2) << endl; // Inversa - Extra!     

	  // Cargar desde imagen -  Extra (Usar CImg.h)
    SparseMatrix<double> m_image = load_from_image("myimage.jpg");
    m_image = transpose(m_image;
    ofstream _out_i("res.txt");
    _out_i << m_image;
    _out_i.close()

    return 1;
}








