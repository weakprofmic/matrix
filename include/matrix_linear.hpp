#ifndef __linears__
#define __linears__

#include "matrix.hpp"

namespace M_Matrix
{
  template <typename T>
  class Matrix<T>::Linear
  {
  public:
    class Iterator;

    Matrix<T>::Linear::Iterator Matrix<T>::Linear::begin();
    Matrix<T>::Linear::Iterator Matrix<T>::Linear::end();

    T operator[](size_t index) {
      return data_[index];
    }

  private:
    T *data_;
    Iterator *iterator;
  };

  template <typename T>
  class Matrix<T>::Linear::Iterator
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

  private:
    T *pointer_;
  };

  template <typename T, size_t N>
  class Col_Iterator : public Matrix<T>::Linear::Iterator
  {
  public:
    using Matrix<T>::Linear::Iterator::Iterator;
    Matrix<T>::Linear::Iterator &operator++() override
    {
      pointer_ += N;
      return *this;
    }

  private:
    T *pointer_;
  };

  template <typename T>
  Matrix<T>::Linear::Iterator::Iterator(T *ptr) : pointer_{ptr}
  {
  }

  template <typename T>
  Matrix<T>::Linear::Iterator &Matrix<T>::Linear::Iterator::operator++()
  {
    pointer_++;
    return *this;
  }
  template <typename T>
  Matrix<T>::Linear::Iterator &Matrix<T>::Linear::Iterator::operator--()
  {
    pointer_--;
    return *this;
  }

  template <typename T>
  Matrix<T>::Linear::Iterator Matrix<T>::Linear::Iterator::operator++(int)
  {
    Matrix<T>::Linear::Iterator temp = *this;
    pointer_++;
    return temp;
  }

  template <typename T>
  Matrix<T>::Linear::Iterator Matrix<T>::Linear::Iterator::operator--(int)
  {
    Matrix<T>::Linear::Iterator temp = *this;
    pointer_--;
    return temp;
  }

  template <typename T>
  T &Matrix<T>::Linear::Iterator::operator*()
  {
    return *pointer_;
  }

  template <typename T>
  bool Matrix<T>::Linear::Iterator::operator==(const Iterator &iter)
  {
    return pointer_ == iter.pointer_;
  }
  template <typename T>
  bool Matrix<T>::Linear::Iterator::operator!=(const Iterator &iter)
  {
    return pointer_ != iter.pointer_;
  }
  template <typename T>
  Matrix<T>::Linear::Iterator Matrix<T>::Linear::begin()
  {
    return Matrix<T>::Linear::Iterator{data_};
  }
  template <typename T>
  Matrix<T>::Linear::Iterator Matrix<T>::Linear::end()
  {
    return Matrix<T>::Linear::Iterator{data_ + cols_ * rows_};
  }

}
#endif