#ifndef __functions__
#define __functions__

#include <iostream>
#include <cmath>
#include <iterator>

namespace __Matrix__
{
  class Vector;
  
  void print_matrix(const Matrix &);
  void swap(Matrix &, Matrix &);
  Matrix operator+(Matrix, double);
  Matrix operator-(Matrix, double);
  Matrix operator+(Matrix, Matrix const &);
  Matrix operator-(Matrix, Matrix const &);
  Matrix operator-(Matrix);
  Matrix operator*(Matrix, double);
  Matrix operator/(Matrix, double);
  Matrix operator*(Matrix const &, Matrix const &);
  void eigens_power_law(const Matrix &);
  void lu_decomposition(const Matrix &);
  void qr_decomposition(const Matrix &);


  void print_vector(const Vector &);
  void swap(Vector &, Vector &);
}

#endif