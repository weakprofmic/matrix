#include "matrix.hpp"
#include "functions.hpp"

#include <iostream>

void print_matrix(const Matrix &matrice)
{
  std::cout << matrice.get_rows()
            << 'x'
            << matrice.get_cols()
            << std::endl;
}