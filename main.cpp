#include "matrix.hpp"
#include "functions.hpp"
#include "matrix_iterator.hpp"
#include "vector_iterator.hpp"
#include "random_wrapper.hpp"
#include "vector.hpp"
#include <iostream>
#include <iterator>
#include <vector>
#include <numeric>

using Matrix = __Matrix__::Matrix;
using Vector = __Matrix__::Vector;

int main(int argc, char *argv[])
{
  int inds[16];
  double arr[16] = {};
  std::vector<double> v(arr, arr + 16);
  std::copy(v.begin(), v.end(), std::ostream_iterator<double>(std::cout, ","));
  arr[1] = 11;

  Random random;

  std::iota(inds, inds + 16, 0);
  for (auto i : inds)
  {
    arr[i] = random.random_integer(0, 10);
  }
  std::copy(arr, arr + 16, std::ostream_iterator<double>(std::cout, ","));

  Matrix m(4, 4, arr);
  Vector mv (16, arr);

  print_vector(mv);
  
  std::cout << *mv.begin();
  

  // print_matrix(m);
  // m.transpmose();
  // print_matrix(m);
  // print_matrix(m ^ 0);
  // std::cout << double(m ^ 0) + 5;
  // std::cout << Matrix::inversed(m);
  // std::cout << m;
  // std::cout << m * Matrix::transposed(m);
  // Matrix m1(1, 1, {888});

  // eigens_power_law(m);

  // lu_decomposition(m);
  qr_decomposition(m);

  // print_matrix(Matrix::transposed(m).cofactor());
  // print_matrix(m.adjoint());
  // print_matrix(m.cofactor());
  // print_matrix(m);
  // m.inverse();
  // print_matrix(m);
  // std::cout << m.det();

  // std::cout << m;

  return 0;
}