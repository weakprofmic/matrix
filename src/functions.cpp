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

  Matrix<double> operator+(Matrix<double> matrice, double x)
  {
    return matrice += x;
  }

  Matrix<double> operator-(Matrix<double> matrice, double x)
  {
    return matrice += -x;
  }
  Matrix<double> operator+(Matrix<double> matrice, Matrix<double> const &other)
  {
    return matrice += other;
  }

  Matrix<double> operator-(Matrix<double> matrice, Matrix<double> const &other)
  {
    return
        // matrice += -other; slow because of operator- implementation
        matrice -= other;
  }
  Matrix<double> operator*(Matrix<double> matrice, double x)
  {
    return matrice *= x;
  }

  Matrix<double> operator/(Matrix<double> matrice, double x)
  {
    return matrice /= x;
  }
  Matrix<double> operator-(Matrix<double> matrice) // can be inefficient due to 2xcopy
  {
    return matrice *= -1;
  }

}