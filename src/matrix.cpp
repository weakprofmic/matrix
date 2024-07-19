#include "matrix.hpp"
#include "functions.hpp"

namespace __Matrix__
{
  int Matrix::id_counter_ = 0;

  Matrix::Matrix() : cols_(0), rows_(0), id_(++id_counter_)
  {
    data_ = nullptr;
    std::cout << "Null Matrice constructed" << std::endl;
  }
  Matrix::Matrix(size_t cols_, size_t rows_) : cols_(cols_), rows_(rows_), id_(++id_counter_)
  {
    data_ = new double[cols_ * rows_]();
    std::cout << "Matrice constructed" << std::endl;
  }
  Matrix::Matrix(size_t cols_, size_t rows_, double *const data) : Matrix(cols_, rows_)
  {
    std::copy(data, data + cols_ * rows_, data_);
  }

  Matrix::Matrix(size_t cols_, size_t rows_, std::initializer_list<double> data) : Matrix(cols_, rows_)
  {
    std::copy(data.begin(), data.end(), data_);
  }

  Matrix::Matrix(size_t cols_, size_t rows_, std::vector<double> data) : Matrix(cols_, rows_)
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

    ::__Matrix__::swap(*this, other);

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
    {
      double max_length_element = *std::max_element(matrix.data_, matrix.data_ + matrix.cols_ * matrix.rows_, [](auto lhs, auto rhs)
                                                    { return std::to_string(lhs).size() < std::to_string(rhs).size(); });

      std::string max_length_str = std::to_string(max_length_element);

      max_length_str.erase(max_length_str.find_last_not_of('0') + 1, std::string::npos);
      max_length_str.erase(max_length_str.find_last_not_of('.') + 1, std::string::npos);

      int max_length = max_length_str.size();
      // std::cerr << max_length_element << ' ' << std::to_string(max_length_element) << ' ' << max_length << '\n';

      for (auto i = 0; i < matrix.rows_; ++i)
      {
        os << std::endl
           << std::endl;
        ;
        for (auto j = 0; j < matrix.cols_; ++j)
        {
          os.width(max_length + 3);
          os << std::left
              // << std::fixed
              ;
          os << matrix.data_[i * matrix.cols_ + j];
        }
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

  /** Operator overloads */
  double const *Matrix::operator[](size_t row) const
  {
    return data_ + row * cols_;
  }

  double const Matrix::operator()(size_t row, size_t col) const
  {
    if (row > rows_ || col > cols_)
      throw OutOfBoundsException(*this, row, col);
    return at(row, col);
  }

  double *Matrix::operator[](size_t row)
  {
    return data_ + row * cols_;
  }

  double &Matrix::operator()(size_t row, size_t col)
  {
    if (row > rows_ || col > cols_)
      throw OutOfBoundsException();
    return at(row, col);
  }

  double &Matrix::at(size_t row, size_t col)
  {
    return data_[row * cols_ + col];
  }

  double const &Matrix::at(size_t row, size_t col) const
  {
    return data_[row * cols_ + col];
  }

  Matrix &Matrix::operator=(double x)
  {
    std::fill(data_, data_ + rows_ * cols_, x);

    // for (auto i = 0; i <= rows_; ++i)
    // {
    //   for (auto j = 0; j <= cols_; ++j)
    //   {
    //     if (x == 1 && i != j && rows_ == cols_) // Identity matrix
    //       continue;
    //     at(i,j) = x;
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

  Matrix Matrix::x_matrix(size_t cols_, size_t rows_, double x)
  {
    if (rows_ == 0)
    {
      rows_ = cols_;
    }
    double *data = new double[rows_ * cols_]();
    std::fill(data, data + rows_ * cols_, x);

    return Matrix(cols_, rows_, data);
  }
  Matrix Matrix::zero(size_t cols_, size_t rows_)
  {
    if (rows_ == 0)
    {
      rows_ = cols_;
    }
    return Matrix::x_matrix(cols_, rows_);
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
  Matrix operator*(Matrix const &lhs, Matrix const &rhs)
  {
    if (lhs.cols() != rhs.rows())
    {
      throw "Wrong operands provided";
    }
    else
    {
      size_t n = lhs.cols();
      size_t rows = lhs.rows();
      size_t cols = rhs.cols();

      Matrix result(rows, cols);

      for (auto i = 0; i < rows; ++i)
      {
        for (auto j = 0; j < cols; ++j)
        {
          double element = 0;
          for (auto k = 0; k < n; ++k)
          {
            element += lhs[i][k] * rhs[k][j];
          }
          result[i][j] = element;
        }
      }

      return result;
    }
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
      Matrix inverse(size, size);

      inverse = cofactor().transposed(*this) * double(1 / (det()));
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
      for (auto i = 0; i <= x - 1; ++i)
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
    //   for (auto i = 0; i <= rows_; ++i)
    //   {
    //     for (auto j = 0; j <= cols_; ++j)
    //     {
    //       if (at(i,j) != other[i][j])
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
      for (auto i = 0; i <= rows_; ++i)
      {
        for (auto j = 0; j <= cols_; ++j)
        {
          if (at(i,j) >= other[i][j]) return false;
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

  /* methods */
  double Matrix::det() const
  {
    int size = cols_;
    double d = 0;

    if (size == 1)
    {
      return at(0, 0);
    }
    if (size == 2)
    {
      return ((at(0, 0) * at(1, 1)) - (at(1, 0) * at(0, 1)));
    }
    else
    {
      for (auto c = 0; c < size; ++c)
      {
        d += at(0, c) * cofactor(0, c);
      }
    }
    return d;
  }
  // Minor -> cofactor
  double Matrix::minor_det(size_t x, size_t y) const
  {
    int size = cols_;
    Matrix submat(size - 1);

    for (auto i = 0; i < size; ++i)
    {
      if (i == x)
        continue;
      for (auto j = 0; j < size; ++j)
      {
        if (j == y)
          continue;
        submat[i > x ? i - 1 : i][j > y ? j - 1 : j] = at(i, j);
      }
    }

    return submat.det();
  }
  Matrix Matrix::minor() const
  {
    int size = cols_;
    Matrix submat(size);

    for (auto i = 0; i < size; ++i)
    {
      for (auto j = 0; j < size; ++j)
      {
        submat[i][j] = minor_det(i, j);
      }
    }
    return submat;
  }

  double Matrix::cofactor(size_t x, size_t y) const
  {
    return ((x + y) % 2 ? -1 : 1) * (cols_ == 2 && x + y == 1 ? at(y, x) : minor_det(x, y));
  }

  Matrix Matrix::cofactor() const
  {
    int size = cols_;
    Matrix submat(size);

    for (auto i = 0; i < size; ++i)
    {
      for (auto j = 0; j < size; ++j)
      {
        submat[i][j] = cofactor(i, j);
      }
    }
    return submat;
  }

  Matrix Matrix::transposed(Matrix const &matrix)
  {
    size_t t_cols = matrix.rows_;
    size_t t_rows = matrix.cols_;

    Matrix trm(t_cols, t_rows);

    for (auto i = 0; i < matrix.rows_; ++i)
    {
      for (auto j = 0; j < matrix.cols_; ++j)
      {
        trm[j][i] = matrix[i][j];
      }
    }
    return trm;
  }

  void Matrix::transpose()
  {
    (*this) = Matrix::transposed((*this));
  }

  Matrix Matrix::adjoint() const
  {
    return Matrix::transposed((*this).cofactor());
  }

  Matrix Matrix::inversed(Matrix const &matrix)
  {
    return matrix.adjoint() * 1. / matrix.det();
  }

  void Matrix::inverse()
  {
    (*this) = Matrix::inversed((*this));
  }

  bool Matrix::has_pivot_one(size_t pivot_row, size_t pivot_col, size_t &alternative_pivot_row) const
  {
    for (size_t i = pivot_row + 1; i < rows_; ++i)
    {
      if (at(i, pivot_col) == 1)
      {
        alternative_pivot_row = i;
        return true;
      }
    }

    return false;
  }

  bool Matrix::has_pivot_not_zero(size_t pivot_row, size_t pivot_col, size_t &col_need_not_zero) const
  {
    for (size_t i = pivot_row + 1; i < rows_; ++i)
    {
      if (at(i, pivot_col))
      {
        col_need_not_zero = i;
        return true;
      }
    }

    return false;
  }

  bool Matrix::find_first_not_zero(size_t row, size_t &col_found_not_zero) const
  {
    for (auto i = 0; i < cols_; ++i)
    {
      if (at(row, i) != 0)
      {
        col_found_not_zero = i;
        return true;
      }
    }

    return false;
  }

  void Matrix::change_pivot_to_one(size_t row, double constant)
  {
    for (auto i = 0; i < cols_; ++i)
      if (at(row, i) != 0)
        at(row, i) = at(row, i) / constant;
  }

  void Matrix::apply_pivot_row(size_t row, size_t pivot_row, double constant)
  {
    for (auto i = 0; i < cols_; ++i)
    {
      at(row, i) -= at(pivot_row, i) * constant;
    }
  }

  Matrix Matrix::gauss_jordan_elimination(Matrix const &matrix)
  {
    Matrix tmp = matrix;

    size_t rows = tmp.rows();
    size_t cols = tmp.cols();

    size_t pivot_row = 0;
    size_t pivot_col = 0;

    /// Gauss Elimination
    while (pivot_row < rows - 1)
    {
      size_t other_row;
      if (tmp.at(pivot_row, pivot_col) != 1 && tmp.has_pivot_one(pivot_row, pivot_col, other_row) || tmp.at(pivot_row, pivot_col) == 0 && tmp.has_pivot_not_zero(pivot_row, pivot_col, other_row))
      {
        tmp.swapRows(pivot_row, other_row);
      }

      size_t col_dif_zero;
      if (tmp.find_first_not_zero(pivot_row, col_dif_zero))
      {
        if ((tmp.at(pivot_row, col_dif_zero)) != 1)
        {
          tmp.change_pivot_to_one(pivot_row, tmp.at(pivot_row, col_dif_zero));
        }

        for (size_t n = pivot_row + 1; n < rows; ++n)
        {
          tmp.apply_pivot_row(n, pivot_row, tmp.at(n, col_dif_zero));
        }
      }

      ++pivot_row;
      ++pivot_col;
    }

    // Jordan Elimination
    while (pivot_row > 0)
    {
      size_t col_dif_zero;

      if (tmp.find_first_not_zero(pivot_row, col_dif_zero))
      {
        if ((tmp.at(pivot_row, col_dif_zero)) != 1)
        {
          tmp.change_pivot_to_one(pivot_row, tmp.at(pivot_row, col_dif_zero));
          print_matrix(tmp);
        }
      }

      for (int n = pivot_row - 1; n >= 0; --n)
      {
        tmp.apply_pivot_row(n, pivot_row, tmp.at(n, col_dif_zero));
      }
      --pivot_row;
    }

    return tmp;
  }

  Matrix Matrix::operator^(int x) const
  {
    if (x == 1)
    {
      return Matrix(*this);
    }

    if (rows_ == cols_)
    {
      if (x == -1)
      {
        return inversed((*this));
      }
      else if (x < 0)
      {
        throw "Illegal operand.\n";
      }
      else if (x == 0)
      {
        return Matrix(1, 1, {1});
      }
      else
      {
        Matrix result = (*this);
        result = (*this);

        for (int i = 1; i < x / 2; ++i)
        {
          result = result * (*this); // better solution is to diagonalize matrix
        }
        result = result * result;
        return x % 2 == 0 ? result : result * (*this);
      }
    }
    else
    {
      throw "A matrix can raised to a certain power only if it has the same rows_ and cols_.\n";
    }
  }

  Matrix::operator double() const
  {
    // if(is_constant)?
    if (cols_ == 1 && cols_ == rows_)
      return at(0, 0);
    else
    {
      throw "Unsupported operation for this arguments\n";
    }
  }

  bool Matrix::is_identity() const
  {
    if (!is_square())
      return false;

    return *this == identity(cols_);
  }

  bool Matrix::is_symmetric() const
  {
    return *this == transposed((*this));
  }

  bool Matrix::is_skewSymmetric() const
  {
    if (!is_square())
    {
      return false;
    }

    for (size_t i = 0; i < rows_; ++i)
    {
      for (size_t j = i + 1; j < cols_; ++j)
      {
        if (at(i, j) != -at(j, i))
        {
          return false;
        }
      }
    }

    return true;
  }

  bool Matrix::is_diagonal() const
  {
    if (!is_square())
      return false;

    for (size_t i = 0; i < rows_; ++i)
      for (size_t j = 0; j < cols_; ++j)
        if (i != j && at(i, j) != 0)
          return false;

    return true;
  }

  bool Matrix::is_zero() const
  {
    return std::all_of(data_, data_ + rows_ * cols_,
                       [](auto const &x)
                       { return x == 0; });
  }

  bool Matrix::is_constant() const
  {
    return std::adjacent_find(data_, data_ + rows_ * cols_, std::not_equal_to{}) == data_ + rows_ * cols_;
  }

  bool Matrix::is_orthogonal() const
  {
    if (!is_square())
      return false;

    return (*this * transposed(*this) == identity(cols_));
  }

  bool Matrix::is_invertible() const
  {
    return det() != 0;
  }

  bool Matrix::is_lowerTriangular() const
  {
    if (!is_square())
      return false;

    for (size_t i = 0; i < rows_; ++i)
      for (size_t j = i + 1; j < cols_; ++j)
        if (at(i, j))
          return false;

    return true;
  }

  bool Matrix::is_upperTriangular() const
  {
    if (!is_square())
      return false;

    for (size_t i = 0; i < rows_; ++i)
      for (size_t j = 0; j < i; ++j)
        if (at(i, j))
          return false;

    return true;
  }
}

#include "matrix_iterator.hpp"

Matrix::Iterator Matrix::begin()
{
  return Matrix::Iterator{data_};
}

Matrix::Iterator Matrix::end()
{
  return Matrix::Iterator{data_ + cols_ * rows_};
}