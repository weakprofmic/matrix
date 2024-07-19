#include "exceptions.hpp"
#include "matrix.hpp"

using Matrix = __Matrix__::Matrix;

OutOfBoundsException::OutOfBoundsException(const Matrix &thrower, size_t row, size_t col)
{
  std::ostringstream oss;
  oss << "Index was out of matrice bounds" << " : " << "matrice dimensions - "
      << thrower.rows() << "x" << thrower.cols() << std::endl
      << "provided position - ("
      << row + 1 << "," << col + 1 << ')' << std::endl;
  error_message = oss.str();

  /* error_message = std::string(message);
  error_message += " : ";
  error_message += function; */
}