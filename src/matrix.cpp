#include "matrix.hpp"
#include "functions.hpp"

#include <iostream>

int Matrix::id_counter_ = 0;

Matrix::Matrix() : cols_(0), rows_(0), id_(++id_counter_)
{
  data_ = nullptr;
  std::cout << "Null Matrice constructed" << std::endl;
}
Matrix::Matrix(size_t width, size_t height) : cols_(width), rows_(height), id_(++id_counter_)
{
  data_ = new double[cols_ * rows_]();
  std::cout << "Matrice constructed" << std::endl;
}
Matrix::Matrix(size_t width, size_t height, double *const data) : Matrix(width, height)
{
  std::copy(data, data + width * height, data_);
}

Matrix::Matrix(size_t width, size_t height, std::initializer_list<double> data) : Matrix(width, height)
{
  std::copy(data.begin(), data.end(), data_);
}

Matrix::Matrix(size_t width, size_t height, std::vector<double> data) : Matrix(width, height)
{
  std::copy(data.begin(), data.end(), data_);
}

Matrix::Matrix(Matrix const &other) : Matrix(other.cols_, other.rows_, other.data_)
{
  std::cout << "Matrice copy-constructed" << std::endl;
}

Matrix::Matrix(Matrix &&other) : Matrix()
{
  swap(other);
  std::cout << "Matrice moved" << std::endl;
}

Matrix::Matrix(size_t size) : Matrix(size, size)
{
  std::cout << "Square Matrice constructed" << std::endl;
}
Matrix::~Matrix()
{
  delete[] data_;
  std::cout << "Matrice destructed" << std::endl;
}

Matrix &Matrix::operator=(const Matrix &other)
{
  if (this == &other)
    return *this;

  cols_ = other.cols_;
  rows_ = other.rows_;
  data_ = new double[cols_ * rows_];

  std::copy(other.data_, other.data_ + cols_ * rows_, data_);

  std::cout << "Matrice copy assigned" << std::endl;

  return *this;
}
Matrix &Matrix::operator=(Matrix &&other)
{
  if (this == &other)
    return *this;

  ::swap(*this, other);

  print_matrix(*this);

  std::cout << "Matrice move assigned" << std::endl;

  return *this;
}

void Matrix::swap(Matrix &other) noexcept
{
  using std::swap;

  swap(rows_, other.rows_);
  swap(cols_, other.cols_);
  swap(data_, other.data_);
}

/**Friends */
void swap(Matrix &lhs, Matrix &rhs)
{
  lhs.swap(rhs);
}
std::ostream &operator<<(std::ostream &os, const Matrix &matrix)
{
  if (&matrix)
    for (int i = 0; i < matrix.rows_; ++i)
    {
      os << std::endl
         << std::endl;
      ;
      for (int j = 0; j < matrix.cols_; ++j)
      {
        os.width(6);
        os << matrix.data_[i * matrix.cols_ + j];
      }
    }
  else
    os << "Empty matrix";
  return os;
}

std::istream &operator>>(std::istream &is, Matrix &matrix)
{
  size_t rows, cols, index = 0, length;
  double *data;

  std::cout << "Input number of rows: ";
  is >> rows;
  std::cout << "Input number of cols: ";
  is >> cols;

  length = rows * cols;
  data = new double[length];

  double value = 0;
  std::cout << "Enter elements of matrice: ";
  is >> value;
  while (is.good() && index < length)
  {
    data[index++] = value;
    is >> value;
  }

  matrix = Matrix(rows, cols, data);

  is.clear();
  is.ignore(32767, '\n');
  return is;
}
