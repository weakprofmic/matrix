#include "matrix.hpp"
#include "functions.hpp"
#include "matrix_iterator.hpp"
#include "functions.cpp"
#include "matrix.cpp"
#include <iostream>
#include <iterator>
#include <vector>

using namespace M_Matrix;

int main(int argc, char *argv[])
{
  Matrix<double> one = Matrix<double>(3, 3, {10, 9, 8, 7, 6, 5, 4, 3, 2});
  Matrix<double>::Iterator it = one.iterator();
  for (; it != one.end(); ++it)
  {
    std::cout << *it << ' ';
  }

  std::cout << '\n';

  Matrix<double>::Col_Iterator c_it = one.col_iterator();

  for (; c_it != one.end(); ++c_it)
  {
    std::cout << *c_it << ' ';
    //  << c_it.pointer_ << ' ' << one.end().pointer_;
  }
  return 0;
}