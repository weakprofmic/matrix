#include "matrix.hpp"
#include "functions.hpp"
// #include "matrix_iterator.hpp"
#include "functions.cpp"
#include "matrix.cpp"
#include <iostream>
#include <iterator>
#include <vector>

using namespace M_Matrix;

int main(int argc, char *argv[])
{

  double arr[15] = {};
  std::vector<double> v(arr, arr + 15);
  std::copy(v.begin(), v.end(), std::ostream_iterator<double>(std::cout, ","));
  arr[1] = 11;
  Matrix<double> m, m2, m3;
  std::cin >> m;
  Matrix m1 = m;
  m2 = m1;
  m3 = std::move(m);

  try
  {
    // Matrix m = Matrix(3, 5 , {1,2,3,4,5,6,7,8,9,10,11,12,13,45,55});
    // print_matrix(m);
    std::cout << m3 << std::endl;

    // m.set_cols(5);
  }
  catch (std::exception &e)
  {
    std::cerr << (e.what());
  }
  print_matrix(m1);
  print_matrix(m2);
  print_matrix(m3);
  print_matrix(m);
  Matrix m4 = std::move(m1);
  print_matrix(m1);
  print_matrix(m4);
  m4.swapRows(0, 1);
  print_matrix(m4);
  

  // for (auto i : m4)
  //   std::cout << i << '\n';

  // try
  // {
  //   double x = m4(0, 1);
  //   x = 5;
  //   // m4(0, 3) = 15;
  //   print_matrix(m4);
  //   std::cout << m4(0, 3);
  // }
  // catch (std::exception &e)
  // {
  //   std::cerr << (e.what());
  // }
  m4 = 1;
  // print_matrix(Matrix<double>::identity(5));
  // print_matrix(Matrix<double>::x_matrix(7, 1, 9.3));
  // print_matrix(Matrix<double>::x_matrix(3));
  // Matrix z = Matrix<double>::zero(4, 2);
  // Matrix zm = Matrix<double>::zero(4, 2) - 2;
  // Matrix xp = Matrix<double>::x_matrix(4, 2, 9) / 3;

  // std::cout << "Comparison result(0):" << (z > zm + xp) << '\n';
  // std::cout << "Comparison result(1):" << (z == zm + xp) << '\n';
  // std::cout << "Comparison result:" << (z > zm + xp) << '\n';

  return 0;
}