#ifndef __vector_iterators__
#define __vector_iterators__

#include "iterator.hpp"
#include "vector.hpp"

namespace __Matrix__
{
  class Vector::Iterator : public ::Iterator
  {
    using ::Iterator::Iterator;
  };
}

#endif