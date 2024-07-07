#ifndef __matrix__
#define __matrix__

#include <cinttypes>
#include <exceptions.hpp>
#include <vector>
#include <algorithm>

class Matrix
{
public:
  /* Constructors and Destructor */
  explicit Matrix();
  explicit Matrix(size_t);
  explicit Matrix(size_t, size_t);
  explicit Matrix(size_t, size_t, double *const);
  explicit Matrix(size_t, size_t, std::initializer_list<double>);
  explicit Matrix(size_t, size_t, std::vector<double>);
  Matrix(Matrix const &other);
  Matrix(Matrix &&other);
  ~Matrix();

  // assignment
  Matrix &operator=(Matrix const &);
  Matrix &operator=(Matrix &&);
  Matrix &operator=(double x);

  // swap
  void swap(Matrix &) noexcept;
  void swapRows(size_t, size_t);
  friend void swap(Matrix &, Matrix &);

  /* Getters and Setters*/

  // bounds unchecked, 'array of arrays' question
  double const *operator[](size_t) const;
  double *operator[](size_t);

  // bounds checked
  double const operator()(size_t, size_t) const;
  double &operator()(size_t, size_t);

  size_t rows() const
  {
    return rows_;
  }
  size_t cols() const
  {
    return cols_;
  }

  double const *data() const
  {
    return data_;
  }

  int id() const
  {
    return id_;
  }

  void set_rows(size_t)
  {
    throw NotImplementedException(__FUNCTION__, "Stub message");
    // rows_ = height;
  }
  void set_cols(size_t)
  {
    throw NotImplementedException(__FUNCTION__, "Stub message");
    // cols_ = width;
  }

  /** IO operations */
  friend std::ostream &operator<<(std::ostream &, Matrix const &);
  friend std::istream &operator>>(std::istream &, Matrix &);

  /* Operations */
  Matrix &operator+=(double x)
  {
    std::transform((*this).data_, (*this).data_ + rows_ * cols_,
                   (*this).data_, [x](double &element)
                   { return element + x; });
    return *this;
  }
  Matrix &operator+=(Matrix const &other)
  {
    std::transform(other.data_, other.data_ + rows_ * cols_,
                   (*this).data_, (*this).data_, std::plus{});
    return *this;
  }

  Matrix &operator-=(Matrix const &other)
  {
    std::transform((*this).data_, (*this).data_ + rows_ * cols_,
                   other.data_, (*this).data_, std::minus{});
    return *this;
  }
  Matrix &operator*=(double x)
  {
    std::for_each((*this).data_, (*this).data_ + rows_ * cols_, [x](double &element)
                  { element *= x; });
    return *this;
  }

  Matrix &operator/=(double x)
  {
    *this *= (1. / x);
    return *this;
  }

  // Matrix operator+(Matrix const &)
  // {
  //   Matrix result(rows_, cols_);
  //   if (rows_ != m.rows_ || cols_ != m.cols_)
  //   {
  //     throw WrongArgumentException();
  //   }

  //   for (int i = 0; i <= rows_; ++i)
  //   {
  //     for (int j = 0; j <= cols_; ++j)
  //     {
  //       result[i][j] = (*this)[i][j] + m[i][j];
  //     }
  //   }
  //   return result;
  // }

  /** Statics */
  static Matrix identity(size_t);
  static Matrix x_matrix(size_t, size_t = 0, double = 0);
  static Matrix zero(size_t, size_t = 0);

  bool operator==(Matrix const &) const;
  bool operator!=(Matrix const &) const;
  bool operator<(Matrix const &) const;
  bool operator<=(Matrix const &) const;
  bool operator>(Matrix const &) const;
  bool operator>=(Matrix const &) const;

  // double det() const;

  // Matrix operator^(int x) const;

  // Iterator basics
  class Iterator;
  Iterator begin();
  Iterator end();

private:
  uint8_t rows_;
  uint8_t cols_;
  static int id_counter_;
  int const id_;

  double *data_;
};

#endif