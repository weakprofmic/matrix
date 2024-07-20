#include "matrix.hpp"
#include "functions.hpp"

#include <iostream>

using namespace M_Matrix;

template <typename T>
Matrix<T> operator+(Matrix<T> matrice, double x)
{
  return matrice += x;
}

template <typename T>
Matrix<T> operator-(Matrix<T> matrice, double x)
{
  return matrice += -x;
}
template <typename T>
Matrix<T> operator+(Matrix<T> matrice, Matrix<T> const &other)
{
  return matrice += other;
}

template <typename T>
Matrix<T> operator-(Matrix<T> matrice, Matrix<T> const &other)
{
  return
      // matrice += -other; slow because of operator- implementation
      matrice -= other;
}
template <typename T>
Matrix<T> operator*(Matrix<T> matrice, double x)
{
  return matrice *= x;
}

template <typename T>
Matrix<T> operator/(Matrix<T> matrice, double x)
{
  return matrice /= x;
}
template <typename T>
Matrix<T> operator-(Matrix<T> matrice) // can be inefficient due to 2xcopy
{
  return matrice *= -1;
}