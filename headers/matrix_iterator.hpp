#ifndef __iterators__
#define __iterators__

#include "matrix.hpp"

class Matrix::Iterator
{
public:
  Iterator(double *ptr);

  Iterator &operator++();
  Iterator &operator--();

  Iterator operator++(int);
  Iterator operator--(int);
  double &operator*();
  bool operator==(const Iterator &iter);
  bool operator!=(const Iterator &iter);

private:
  double *pointer_;
};

Matrix::Iterator::Iterator(double *ptr) : pointer_{ptr}
{
}

Matrix::Iterator &Matrix::Iterator::operator++()
{
  pointer_++;
  return *this;
}

Matrix::Iterator &Matrix::Iterator::operator--()
{
  pointer_--;
  return *this;
}


Matrix::Iterator Matrix::Iterator::operator++(int)
{
  Matrix::Iterator temp = *this;
  pointer_++;
  return temp;
}

Matrix::Iterator Matrix::Iterator::operator--(int)
{
  Matrix::Iterator temp = *this;
  pointer_--;
  return temp;
}

double &Matrix::Iterator::operator*()
{
  return *pointer_;
}

bool Matrix::Iterator::operator==(const Iterator &iter)
{
  return pointer_ == iter.pointer_;
}

bool Matrix::Iterator::operator!=(const Iterator &iter)
{
  return pointer_ != iter.pointer_;
}

Matrix::Iterator Matrix::begin()
{
  return Matrix::Iterator{data_};
}

Matrix::Iterator Matrix::end()
{
  return Matrix::Iterator{data_ + cols_ * rows_};
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

#endif