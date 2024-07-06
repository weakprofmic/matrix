#include "matrix.hpp"
#include "functions.hpp"
#include <iostream>
#include <iterator>
#include <vector>

int main(int argc, char *argv[])
{

  double arr[15] = {};
  std::vector<double> v(arr, arr + 15);
  std::copy(v.begin(), v.end(), std::ostream_iterator<double>(std::cout, ","));
  arr[1] = 11;
  Matrix m, m2, m3;
  std::cin >> m;
  Matrix m1 = m;
  m2 = m1;
  m3 = std::move(m);

  try
  {
    // Matrix m = Matrix(3, 5 , {1,2,3,4,5,6,7,8,9,10,11,12,13,45,55});
    print_matrix(m);
    std::cout << m << std::endl;

    // m.set_cols(5);
  }
  catch (std::exception *e)
  {
    std::cerr << (e->what());
  }
  print_matrix(m1);
  print_matrix(m2);
  print_matrix(m3);
  print_matrix(m);
  Matrix m4 = std::move(m1);
  print_matrix(m1);
  print_matrix(m4);

  return 0;
}