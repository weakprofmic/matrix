#ifndef __iterators__
#define __iterators__

#include "matrix.hpp"

namespace M_Matrix
{
  template <typename T>
  class Matrix<T>::Iterator
  {
  public:
    Iterator(T *ptr);

    Iterator &operator++();
    Iterator &operator--();

    Iterator operator++(int);
    Iterator operator--(int);
    T &operator*();
    bool operator==(const Iterator &iter);
    bool operator!=(const Iterator &iter);

  protected:
    T *pointer_;
  };

  template <typename T>
  Matrix<T>::Iterator::Iterator(T *ptr) : pointer_{ptr}
  {
  }

  template <typename T>
  typename Matrix<T>::Iterator &Matrix<T>::Iterator::operator++()
  {
    pointer_++;
    return *this;
  }
  template <typename T>
  typename Matrix<T>::Iterator &Matrix<T>::Iterator::operator--()
  {
    pointer_--;
    return *this;
  }

  template <typename T>
  typename Matrix<T>::Iterator Matrix<T>::Iterator::operator++(int)
  {
    Matrix<T>::Iterator temp = *this;
    pointer_++;
    return temp;
  }

  template <typename T>
  typename Matrix<T>::Iterator Matrix<T>::Iterator::operator--(int)
  {
    Matrix<T>::Iterator temp = *this;
    pointer_--;
    return temp;
  }

  template <typename T>
  T &Matrix<T>::Iterator::operator*()
  {
    // std::cout << " here * ";
    return *pointer_;
  }

  template <typename T>
  bool Matrix<T>::Iterator::operator==(const Iterator &iter)
  {
    return pointer_ == iter.pointer_;
  }
  template <typename T>
  bool Matrix<T>::Iterator::operator!=(const Iterator &iter)
  {
    // std::cout << pointer_ << " here != " << iter.pointer_;
    return pointer_ != iter.pointer_;
  }
  template <typename T>
  typename Matrix<T>::Iterator Matrix<T>::begin() const
  {
    return Matrix<T>::Iterator{data_};
  }
  template <typename T>
  typename Matrix<T>::Iterator Matrix<T>::end() const
  {
    return Matrix<T>::Iterator{data_ + cols_ * rows_};
  }

  template <typename Iter>
  Iter maximum(Iter first, Iter last)
  {
    Iter max = first;
    for (Iter iter = first; iter != last; iter++)
    {
      if (*max < *iter)
      {
        max = iter;
      }
    }
    return max;
  }

  template <typename T>
  class Matrix<T>::Col_Iterator : public Matrix<T>::Iterator
  {
    using Matrix<T>::Iterator::pointer_;

  public:
    Col_Iterator(T *ptr, size_t N, size_t M);
    Col_Iterator &operator++();
    Col_Iterator &operator--();

  private:
    T const *start_pointer_;
    size_t padding = 0;
    size_t step;
    size_t stop_point;
  };

  template <typename T>
  Matrix<T>::Col_Iterator::Col_Iterator(T *ptr, size_t N, size_t M) : Matrix<T>::Iterator::Iterator(ptr), start_pointer_(ptr), step(M), stop_point(N)
  {
  }

  template <typename T>
  typename Matrix<T>::Col_Iterator &Matrix<T>::Col_Iterator::operator++()
  {
    if (padding == step * stop_point - 1)
      ++padding;
    else
    {
      padding += step;

      if (padding >= step * stop_point)
      {
        padding = padding % step + 1;
      }
    }

    // std::cout << padding << ' ';
    // std::cout << pointer_ << ' ' << const_cast<double *>(start_pointer_) + step * stop_point << '\n';

    pointer_ = const_cast<double *>(start_pointer_) + padding;
    return *this;
  }
  template <typename T>
  typename Matrix<T>::Col_Iterator &Matrix<T>::Col_Iterator::operator--()
  {
    padding -= step;

    if (padding < 0)
      padding = padding - 1 + step * stop_point;

    pointer_ = const_cast<double *>(start_pointer_) + padding;
    return *this;
  }
}

#endif