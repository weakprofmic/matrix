#ifndef __matrix__
#define __matrix__

#include "exceptions.hpp"

#include <cinttypes>
#include <vector>
#include <algorithm>
#include <iostream>
#include <limits>

namespace __Matrix__
{
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
    Matrix &operator=(double);

    // checks
    bool is_square() const
    {
      return rows_ == cols_;
    }

    bool is_identity() const;
    bool is_symmetric() const;
    bool is_skewSymmetric() const;
    bool is_diagonal() const;
    bool is_zero() const;
    bool is_constant() const;
    bool is_orthogonal() const;
    bool is_invertible() const;
    bool is_upperTriangular() const;
    bool is_lowerTriangular() const;

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

    /** Statics */
    static Matrix identity(size_t);
    static Matrix x_matrix(size_t, size_t = 0, double = 0);
    static Matrix zero(size_t, size_t = 0);
    static Matrix transposed(Matrix const &);
    static Matrix gauss_jordan_elimination(Matrix const &);
    static Matrix inversed(Matrix const &);

    Matrix operator^(int) const;

    operator double() const;

    bool operator==(Matrix const &) const;
    bool operator!=(Matrix const &) const;
    bool operator<(Matrix const &) const;
    bool operator<=(Matrix const &) const;
    bool operator>(Matrix const &) const;
    bool operator>=(Matrix const &) const;

    void transpose();
    void inverse();

    Matrix cofactor() const;
    Matrix adjoint() const;
    Matrix minor() const;

    double det() const;

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

    double minor_det(size_t, size_t) const;
    double cofactor(size_t, size_t) const;

    double &at(size_t row, size_t col);
    double const &at(size_t row, size_t col) const;

    bool has_pivot_one(size_t pivot_row, size_t pivot_col, size_t &alternative_pivot_row) const;
    bool has_pivot_not_zero(size_t pivot_row, size_t pivot_col, size_t &col_dif_zero) const;
    bool find_first_not_zero(size_t row_num, size_t &num_coluna_num_dif_zero) const;
    void change_pivot_to_one(size_t row_num, double constant);
    void apply_pivot_row(size_t row_num, size_t num_pivot_row, double constant);
  };
}

#endif