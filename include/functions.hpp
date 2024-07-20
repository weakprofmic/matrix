#ifndef __functions__
#define __functions__

namespace M_Matrix
{
  template <typename T>
  class Matrix;
  
  template <typename T>
  void print_matrix(const Matrix<T> &);

  template <typename T>
  Matrix<T> operator+(Matrix<T>, double);

  template <typename T>
  Matrix<T> operator-(Matrix<T>, double);

  template <typename T>
  Matrix<T> operator+(Matrix<T>, Matrix<T> const &);

  template <typename T>
  Matrix<T> operator-(Matrix<T>, Matrix<T> const &);

  template <typename T>
  Matrix<T> operator-(Matrix<T>);

  template <typename T>
  Matrix<T> operator*(Matrix<T>, double);

  template <typename T>
  Matrix<T> operator/(Matrix<T>, double);
}

#endif