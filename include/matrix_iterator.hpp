#ifndef __matrix_iterators__
#define __matrix_iterators__

#include "iterator.hpp"
#include "matrix.hpp"

namespace __Matrix__
{
  class Matrix::Iterator : public ::Iterator
  {
    using ::Iterator::Iterator;
  };
}

#endif