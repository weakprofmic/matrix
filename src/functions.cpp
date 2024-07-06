#include "matrix.hpp"
#include "functions.hpp"

#include <iostream>

void print_matrix(const Matrix &matrice)
{
  auto h = matrice.rows();
  auto w = matrice.cols();
  auto data__ = matrice.data();
  std::cout << matrice.id() << "# "
            << h
            << 'x'
            << w
            << ":"
            << std::endl;
  for (auto i = 0; i < h; ++i)
  {
    for (auto j = 0; j < w; ++j)
    {
      std::cout << data__[i * w + j] << " ";
    }
    std::cout << std::endl;
  }
}