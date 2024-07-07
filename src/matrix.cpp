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

Matrix &Matrix::operator=(Matrix const &other)
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

void Matrix::swapRows(size_t row, size_t other_row)
{
  auto const r1_begin = (*this)[row];
  auto const r1_end = (*this)[row] + cols_;
  auto const r2_start = (*this)[other_row];

  std::swap_ranges(r1_begin, r1_end, r2_start);
}

/**Friends */
void swap(Matrix &lhs, Matrix &rhs)
{
  lhs.swap(rhs);
}
std::ostream &operator<<(std::ostream &os, Matrix const &matrix)
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

double const *Matrix::operator[](size_t row) const
{
  return data_ + row * cols_;
}

double const Matrix::operator()(size_t row, size_t col) const
{
  if (row > rows_ || col > cols_)
    throw OutOfBoundsException(*this, row, col);
  return data_[row * cols_ + col];
}

double *Matrix::operator[](size_t row)
{
  return data_ + row * cols_;
}

double &Matrix::operator()(size_t row, size_t col)
{
  if (row > rows_ || col > cols_)
    throw OutOfBoundsException();
  return data_[row * cols_ + col];
}

Matrix &Matrix::operator=(double x)
{
  std::fill(data_, data_ + rows_ * cols_, x);

  // for (int i = 1; i <= rows_; ++i)
  // {
  //   for (int j = 1; j <= cols_; ++j)
  //   {
  //     if (x == 1 && i != j && rows_ == cols_) // Identity matrix
  //       continue;
  //     (*this)[i][j] = x;
  //   }
  // }
  return (*this);
}

Matrix Matrix::identity(size_t size)
{
  double *data = new double[size * size]();
  for (auto i = 0; i < size * size; i += size + 1)
    data[i] = 1;
  return Matrix(size, size, data);
}

Matrix Matrix::x_matrix(size_t width, size_t height, double x)
{
  if (height == 0)
  {
    height = width;
  }
  double *data = new double[height * width]();
  std::fill(data, data + height * width, x);

  return Matrix(width, height, data);
}
Matrix Matrix::zero(size_t width, size_t height)
{
  if (height == 0)
  {
    height = width;
  }
  return Matrix::x_matrix(width, height);
}
Matrix operator+(Matrix matrice, double x)
{
  return matrice += x;
}

Matrix operator-(Matrix matrice, double x)
{
  return matrice += -x;
}
Matrix operator+(Matrix matrice, Matrix const &other)
{
  return matrice += other;
}

Matrix operator-(Matrix matrice, Matrix const &other)
{
  return
      // matrice += -other; slow because of operator- implementation
      matrice -= other;
}
Matrix operator*(Matrix matrice, double x)
{
  return matrice *= x;
}

Matrix operator/(Matrix matrice, double x)
{
  return matrice /= x;
}
Matrix operator-(Matrix matrice) // can be inefficient due to 2xcopy
{
  return matrice *= -1;
}

/* Matrix Matrix::operator^(int x) const
{
  if (rows_ != cols_)
  {
    throw WrongArgumentException();
  }

  int size = rows_;
  Matrix result(rows_, rows_);

  if (x == -1)
  {
    Matrix inverse(n, n);

    inverse = (*this).cofactor().transposed() * double(1 / ((*this).det()));
    result = inverse ^ (x * -1);
  }
  else if (x < 0)
  {
    std::cout << "Illegal operation!!!" << std::endl;
    exit(-1);
  }
  else if (x == 0)
  {
    result = (T)1;
  }
  else
  {
    result = (*this);
    for (int i = 1; i <= x - 1; ++i)
    {
      result = result * (*this);
    }
  }
  return result;
}
*/

/* void operator^=(T x)
{
  (*this) = (*this) ^ x;
} */

/* booleans
 */
bool Matrix::operator==(Matrix const &other) const
{
  // if (cols_ == other.cols_ && rows_ == other.rows_)
  // {
  //   for (int i = 1; i <= rows_; ++i)
  //   {
  //     for (int j = 1; j <= cols_; ++j)
  //     {
  //       if ((*this)[i][j] != other[i][j])
  //         return false;
  //     }
  //   }
  //   return true;
  // }
  // return false;

  return cols_ == other.cols_ && rows_ == other.rows_ && std::equal(data_, data_ + rows_ * cols_, other.data_);
}

bool Matrix::operator!=(Matrix const &other) const
{
  return !((*this) == other);
}

bool Matrix::operator<(Matrix const &other) const
{
  /* if (cols_ == other.cols_ && rows_ == other.rows_)
  {
    for (int i = 1; i <= rows_; ++i)
    {
      for (int j = 1; j <= cols_; ++j)
      {
        if ((*this)[i][j] >= other[i][j]) return false;
      }
    }
    return true;
  }
  else if (cols_ * rows_ < other.cols_ * other.rows_)
  {
    return true;
  }
  return false; */

  return (cols_ == other.cols_ && rows_ == other.rows_) && std::lexicographical_compare(data_, data_ + cols_ * rows_, other.data_, other.data_ + cols_ * rows_) ||
         (cols_ * rows_ < other.cols_ * other.rows_);
}

bool Matrix::operator<=(Matrix const &other) const
{
  return (*this) < other || (*this) == other;
}

bool Matrix::operator>(Matrix const &other) const
{
  return !((*this) <= other);
}

bool Matrix::operator>=(Matrix const &other) const
{
  return !((*this) < other);
}

/* methods
double Matrix::det() const
{
  int n = cols_;
  double d = 0;

  if (n == 1)
  {
    return (*this)[1][1];
  }
  if (n == 2)
  {
    return (((*this)[1][1] * (*this)[2][2]) - ((*this)[2][1] * (*this)[1][2]));
  }
  else
  {
    Matrix submat(n - 1, n - 1);
    for (int c = 1; c <= n; ++c)
    {
      int subi = 1;
      for (int i = 2; i <= n; ++i)
      {
        int subj = 1;
        for (int j = 1; j <= n; ++j)
        {
          if (j == c)
            continue;
          submat[subi][subj] = (*this)[i][j];
          ++subj;
        }
        ++subi;
      }
      d += (pow(-1, c - 1) * (*this)[1][c] * submat.det());
    }
  }
  return d;
}
/*
// Minor -> cofactor
double minor(int x, int y) const
{
  int n = cols_;
  Matrix<T> submat(n - 1, n - 1);

  for (int i = 1; i <= n; ++i)
  {
    for (int j = 1; j <= n; ++j)
    {
      if (i == x or j == y)
        continue;
      submat[i > x ? i - 1 : i][j > y ? j - 1 : j] = (*this)[i][j];
    }
  }
  return submat.det();
}
Matrix<T> minor() const
{
  int n = cols_;
  Matrix<T> submat(n, n);
  for (int i = 1; i <= n; ++i)
  {
    for (int j = 1; j <= n; ++j)
    {
      submat[i][j] = (*this).Minor(i, j);
    }
  }
  return submat;
}

double cofactor(int x, int y) const
{
  return pow(-1, x + y) * (cols_ == 2 && x + y == 1 ? (*this)[x][y] : (*this).Minor(x, y));
}
Matrix<T> cofactor() const
{
  int n = cols_;
  Matrix<T> submat(n, n);
  for (int i = 1; i <= n; ++i)
  {
    for (int j = 1; j <= n; ++j)
    {
      submat[i][j] = (*this).cofactor(i, j);
    }
  }
  return submat;
}

Matrix<T> transposed() const
{
  Matrix<T> trm(cols_, rows_);
  for (int i = 1; i <= cols_; ++i)
  {
    for (int j = 1; j <= rows_; ++j)
    {
      trm[j][i] = (*this)[i][j];
    }
  }
  return trm;
} */