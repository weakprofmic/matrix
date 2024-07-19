#ifndef __my_iterators__
#define __my_iterators__

class Iterator
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

#endif