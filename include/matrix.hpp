#ifndef __matrix__
#define __matrix__

#include <cinttypes>
#include <functions.hpp>
#include <exceptions.hpp>
#include <vector>
#include <algorithm>

namespace M_Matrix
{

  template <typename T>
  class Matrix;

  template <typename T>
  void swap(Matrix<T> &, Matrix<T> &);

  /** IO operations */
  template <typename T>
  std::ostream &operator<<(std::ostream &, Matrix<T> const &);

  template <typename T>
  std::istream &operator>>(std::istream &, Matrix<T> &);

  template <typename T>
  class Matrix
  {
  public:
    /* Constructors and Destructor */
    explicit Matrix();
    explicit Matrix(size_t);
    explicit Matrix(size_t, size_t);
    explicit Matrix(size_t, size_t, T *const);
    explicit Matrix(size_t, size_t, std::initializer_list<T>);
    explicit Matrix(size_t, size_t, std::vector<T>);
    Matrix(Matrix const &other);
    Matrix(Matrix &&other);

    // operator Matrix<double>();
    // template <>
    operator Matrix<double>() const
    {
      double *data = new double[rows() * cols()]();
      Iterator it = begin();
      std::for_each(data, data + rows() * cols(), [&it](double &elem)
                    { elem = static_cast<double>(*(it++)); });
      return Matrix<double>(rows(), cols(), data);
    }

    ~Matrix();

    // assignment
    Matrix &operator=(Matrix const &);
    Matrix &operator=(Matrix &&);
    Matrix &operator=(T x);

    // swap
    void swap(Matrix &) noexcept;
    void swapRows(size_t, size_t);

    /* Getters and Setters*/

    // bounds unchecked, 'array of arrays' question
    T const *operator[](size_t) const;
    T *operator[](size_t);

    // bounds checked
    T const operator()(size_t, size_t) const;
    T &operator()(size_t, size_t);

    size_t rows() const
    {
      return rows_;
    }
    size_t cols() const
    {
      return cols_;
    }

    T const *data() const
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
    friend std::ostream &operator<< <>(std::ostream &, Matrix const &);
    friend std::istream &operator>> <>(std::istream &, Matrix &);
    friend void M_Matrix::swap<>(Matrix &, Matrix &);

    /* Operations */
    Matrix &operator+=(T x)
    {
      std::transform((*this).data_, (*this).data_ + rows_ * cols_,
                     (*this).data_, [x](T &element)
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
    Matrix &operator*=(T x)
    {
      std::for_each((*this).data_, (*this).data_ + rows_ * cols_, [x](T &element)
                    { element *= x; });
      return *this;
    }

    Matrix &operator/=(T x)
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
    static Matrix x_matrix(size_t, size_t = 0, T = 0);
    static Matrix zero(size_t, size_t = 0);

    bool operator==(Matrix const &) const;
    bool operator!=(Matrix const &) const;
    bool operator<(Matrix const &) const;
    bool operator<=(Matrix const &) const;
    bool operator>(Matrix const &) const;
    bool operator>=(Matrix const &) const;

    // T det() const;

    // Matrix operator^(int x) const;

    // Iterator basics
    class Iterator;
    Iterator begin() const;
    Iterator end() const;

    class Col_Iterator;

    Iterator iterator() {
      return Iterator{data_};
    }

    Col_Iterator col_iterator() {
      return Col_Iterator{data_, rows_, cols_};
    }

    // Iterator basics
    class Linear;
    using Row = Linear;
    using Col = Linear;

    Row getRow();
    Col getCol();

  private:
    uint8_t rows_;
    uint8_t cols_;
    static int id_counter_;
    int const id_;

    T *data_;
  };

}

#include "matrix_realizations.hpp"
#endif