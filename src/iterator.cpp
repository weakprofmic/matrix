#include "iterator.hpp"

Iterator::Iterator(double *ptr) : pointer_{ptr}
{
}

Iterator &Iterator::operator++()
{
  pointer_++;
  return *this;
}

Iterator &Iterator::operator--()
{
  pointer_--;
  return *this;
}

Iterator Iterator::operator++(int)
{
  Iterator temp = *this;
  pointer_++;
  return temp;
}

Iterator Iterator::operator--(int)
{
  Iterator temp = *this;
  pointer_--;
  return temp;
}

double &Iterator::operator*()
{
  return *pointer_;
}

bool Iterator::operator==(const Iterator &iter)
{
  return pointer_ == iter.pointer_;
}

bool Iterator::operator!=(const Iterator &iter)
{
  return pointer_ != iter.pointer_;
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