#include "matrix.hpp"
#include "functions.hpp"

#include <iostream>

namespace M_Matrix
{

  template <typename T>
  void print_matrix(const Matrix<T> &matrice)
  {
    auto h = matrice.rows();
    auto w = matrice.cols();

    std::cout << matrice.id() << "# "
              << h
              << 'x'
              << w
              << ":"
              // << '\n'
              ;
    std::cout << matrice << '\n';
  }
}