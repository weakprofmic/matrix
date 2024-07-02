#include "matrix.hpp"

#include <iostream>

Matrix::Matrix()
{
  std::cout << "Matrice constructed" << std::endl;
}
Matrix::Matrix(size_t width, size_t height) : cols(width), rows(height)
{
  std::cout << "Matrice constructed" << std::endl;
}
Matrix::Matrix(size_t size) : cols(size), rows(size)
{
  std::cout << "Matrice constructed" << std::endl;
}
Matrix::~Matrix()
{
  std::cout << "Matrice destructed" << std::endl;
}
