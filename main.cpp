#include "./SparseMatrix.hpp"
#define NORMAL

int main()
{
  srand(time(NULL));
  SMatrix<double> m1;
  for(int i= 0; i < 100; i++)
    m1.insert(rand()%5,rand()%5,rand()%250);    
  
  m1.print();
  m1.inverse_s().print();
  m1.add_sums(m1).print();
  m1.multv(m1).print();
  auto m2 = m1.inverse_s();
  cout<<m2;
  auto m3 = identity(5,5);
  cout<<m3;
  m1.clear();

  SMatrix<unsigned char> img = load_from_image<unsigned char>("photo.jpg");
  return 0;
}
