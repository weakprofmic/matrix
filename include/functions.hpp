#ifndef __functions__
#define __functions__

namespace M_Matrix
{
  template <typename T>
  class Matrix;
  
  template <typename T>
  void print_matrix(const Matrix<double> &);

  Matrix<double> operator+(Matrix<double>, double);

  Matrix<double> operator-(Matrix<double>, double);

  Matrix<double> operator+(Matrix<double>, Matrix<double> const &);

  Matrix<double> operator-(Matrix<double>, Matrix<double> const &);

  Matrix<double> operator-(Matrix<double>);

  Matrix<double> operator*(Matrix<double>, double);

  Matrix<double> operator/(Matrix<double>, double);
}

#endif