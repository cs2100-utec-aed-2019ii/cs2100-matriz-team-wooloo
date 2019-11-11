#include "./SparseMatrix.hpp"
#define NORMAL

int main()
{
  SMatrix<int> a;
#ifdef NORMAL
  a.add(0, 0, 1);
  a.add(0, 1, 2);
  a.add(1, 0, 3);
  a.add(1, 1, 4);
#else
  a.at(0,0) = 1;
  a.at(0,1) = 2;
  a.at(1,0) = 3;
  a.at(1,1) = 4;
#endif
  cout << a.at(0,0) << "\t" << a.at(0,1) << endl;
  cout << a.at(1,0) << "\t" << a.at(1,1) << endl;
  for(int i = 0; i < 100; i++)
  {
    for(int j = 0; j < 100; j++)
    {
      a.at(i, j) = i+j;
      //a.add(i, j, i+j);
    }
  }
  a.clear();
  return 0;
}
