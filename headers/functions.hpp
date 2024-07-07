#ifndef __functions__
#define __functions__

class Matrix;
void print_matrix(const Matrix &);
void swap(Matrix &, Matrix &);
Matrix operator+(Matrix, double);
Matrix operator-(Matrix, double);
Matrix operator+(Matrix, Matrix const &);
Matrix operator-(Matrix, Matrix const &);
Matrix operator-(Matrix);
Matrix operator*(Matrix, double);
Matrix operator/(Matrix, double);

#endif