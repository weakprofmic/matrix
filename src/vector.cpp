#include "vector.hpp"
#include "functions.hpp"

namespace __Matrix__
{
  int Vector::id_counter_ = 0;

  Vector::Vector() : size_(0), id_(++id_counter_)
  {
    data_ = nullptr;
    std::cout << "Null Vector constructed" << std::endl;
  }
  Vector::Vector(size_t size) : size_(size), id_(++id_counter_)
  {
    data_ = new double[size]();
    std::cout << "Vector constructed" << std::endl;
  }
  Vector::Vector(size_t size, double x) : Vector(size)
  {
    std::fill(data_, data_ + size, x);
  }
  Vector::Vector(size_t size, double *const data) : Vector(size)
  {
    std::copy(data, data + size, data_);
  }

  Vector::Vector(size_t size, std::initializer_list<double> data) : Vector(size)
  {
    std::copy_n(data.begin(), size, data_);
  }
  Vector::Vector(std::initializer_list<double> data) : Vector(data.size())
  {
    std::copy(data.begin(), data.end(), data_);
  }

  Vector::Vector(size_t size, std::vector<double> data) : Vector(size)
  {
    std::copy_n(data.begin(), size, data_);
  }
  Vector::Vector(std::vector<double> data) : Vector(data.size())
  {
    std::copy(data.begin(), data.end(), data_);
  }

  Vector::Vector(Vector const &other) : Vector(other.size_, other.data_)
  {
    std::cout << "Vector copy-constructed" << std::endl;
  }

  Vector::Vector(Vector &&other) : Vector()
  {
    swap(other);
    std::cout << "Vector moved" << std::endl;
  }

  Vector::~Vector()
  {
    delete[] data_;
    std::cout << "Vector destructed" << std::endl;
  }

  Vector &Vector::operator=(Vector const &other)
  {
    if (this == &other)
      return *this;

    size_ = other.size_;
    data_ = new double[size_];

    std::copy(other.data_, other.data_ + size_, data_);

    std::cout << "Vector copy assigned" << std::endl;

    return *this;
  }
  Vector &Vector::operator=(Vector &&other)
  {
    if (this == &other)
      return *this;

    ::__Matrix__::swap(*this, other);

    print_vector(*this);

    std::cout << "Vector move assigned" << std::endl;

    return *this;
  }

  void Vector::swap(Vector &other) noexcept
  {
    using std::swap;

    swap(size_, other.size_);
    swap(data_, other.data_);
  }

  /**Friends */
  void swap(Vector &lhs, Vector &rhs)
  {
    lhs.swap(rhs);
  }
  std::ostream &operator<<(std::ostream &os, Vector const &vector)
  {
    if (&vector)
    {
      double max_length_element = *std::max_element(vector.data_, vector.data_ + vector.size_, [](auto lhs, auto rhs)
                                                    { return std::to_string(lhs).size() < std::to_string(rhs).size(); });

      std::string max_length_str = std::to_string(max_length_element);

      max_length_str.erase(max_length_str.find_last_not_of('0') + 1, std::string::npos);
      max_length_str.erase(max_length_str.find_last_not_of('.') + 1, std::string::npos);

      int max_length = max_length_str.size();
      // std::cerr << max_length_element << ' ' << std::to_string(max_length_element) << ' ' << max_length << '\n';

      for (auto j = 0; j < vector.size_; ++j)
      {
        os.width(max_length + 3);
        os << std::left
            // << std::fixed
            ;
        os << vector.data_[j];
      }
    }
    else
      os << "Empty vector";
    return os;
  }

  std::istream &operator>>(std::istream &is, Vector &vector)
  {
    size_t size, index = 0;
    double *data;

    std::cout << "Input number of elements: ";
    is >> size;

    data = new double[size];

    double value = 0;
    std::cout << "Enter elements of vector: ";
    is >> value;
    while (is.good() && index < size)
    {
      data[index++] = value;
      is >> value;
    }

    vector = Vector(size, data);

    is.clear();
    is.ignore(32767, '\n');
    return is;
  }

  /** Operator overloads */
  double const &Vector::operator[](size_t padding) const
  {
    return data_[padding];
  }

  double const Vector::operator()(size_t padding) const
  {
    if (padding > size_)
      throw "OutOfBoundsException";
    return at(padding);
  }

  double &Vector::operator[](size_t padding)
  {
    return data_[padding];
  }

  double &Vector::operator()(size_t padding)
  {
    if (padding > size_)
      throw "OutOfBoundsException";
    return at(padding);
  }

  double &Vector::at(size_t padding)
  {
    return data_[padding];
  }

  double const &Vector::at(size_t padding) const
  {
    return data_[padding];
  }

  Vector &Vector::operator=(double x)
  {
    std::fill(data_, data_ + size_, x);

    // for (auto i = 0; i <= rows_; ++i)
    // {
    //   for (auto j = 0; j <= cols_; ++j)
    //   {
    //     if (x == 1 && i != j && rows_ == cols_) // Identity vector
    //       continue;
    //     at(i,j) = x;
    //   }
    // }
    return (*this);
  }

  Vector operator+(Vector vector, double x)
  {
    return vector += x;
  }

  Vector operator-(Vector vector, double x)
  {
    return vector += -x;
  }
  Vector operator+(Vector vector, Vector const &other)
  {
    return vector += other;
  }

  Vector operator-(Vector vector, Vector const &other)
  {
    return
        // vector += -other; slow because of operator- implementation
        vector -= other;
  }
  Vector operator*(Vector vector, double x)
  {
    return vector *= x;
  }

  Vector operator/(Vector vector, double x)
  {
    return vector /= x;
  }
  double operator*(Vector const &lhs, Vector const &rhs)
  {
    if (lhs.size() != rhs.size())
    {
      throw "Wrong operands provided";
    }
    else
    {

      double result;

      for (auto i = 0; i < lhs.size(); ++i)
      {
        result += lhs[i] * rhs[i];
      }
      return result;
    }
  }

  Vector operator-(Vector vector) // can be inefficient due to 2xcopy
  {
    return vector *= -1;
  }

  /* Vector Vector::operator^(int x) const
  {
    if (rows_ != cols_)
    {
      throw WrongArgumentException();
    }

    int size = rows_;
    Vector result(rows_, rows_);

    if (x == -1)
    {
      Vector inverse(size, size);

      inverse = cofactor().transposed(*this) * double(1 / (det()));
      result = inverse ^ (x * -1);
    }
    else if (x < 0)
    {
      std::cout << "Illegal operation!!!" << std::endl;
      exit(-1);
    }
    else if (x == 0)
    {
      result = (T)1;
    }
    else
    {
      result = (*this);
      for (auto i = 0; i <= x - 1; ++i)
      {
        result = result * (*this);
      }
    }
    return result;
  }
  */

  /* void operator^=(T x)
  {
    (*this) = (*this) ^ x;
  } */

  /* booleans
   */
  bool Vector::operator==(Vector const &other) const
  {
    // if (cols_ == other.cols_ && rows_ == other.rows_)
    // {
    //   for (auto i = 0; i <= rows_; ++i)
    //   {
    //     for (auto j = 0; j <= cols_; ++j)
    //     {
    //       if (at(i,j) != other[i][j])
    //         return false;
    //     }
    //   }
    //   return true;
    // }
    // return false;

    return size_ == other.size_ && std::equal(data_, data_ + size_, other.data_);
  }

  bool Vector::operator!=(Vector const &other) const
  {
    return !((*this) == other);
  }

  bool Vector::operator<(Vector const &other) const
  {
    /* if (cols_ == other.cols_ && rows_ == other.rows_)
    {
      for (auto i = 0; i <= rows_; ++i)
      {
        for (auto j = 0; j <= cols_; ++j)
        {
          if (at(i,j) >= other[i][j]) return false;
        }
      }
      return true;
    }
    else if (cols_ * rows_ < other.cols_ * other.rows_)
    {
      return true;
    }
    return false; */

    return (size_ == other.size_) && std::lexicographical_compare(data_, data_ + size_, other.data_, other.data_ + size_) ||
           (size_ < other.size_);
  }

  bool Vector::operator<=(Vector const &other) const
  {
    return (*this) < other || (*this) == other;
  }

  bool Vector::operator>(Vector const &other) const
  {
    return !((*this) <= other);
  }

  bool Vector::operator>=(Vector const &other) const
  {
    return !((*this) < other);
  }
}

#include "vector_iterator.hpp"

__Matrix__::Vector::Iterator __Matrix__::Vector::begin()
{
  return Vector::Iterator{data_};
}

__Matrix__::Vector::Iterator __Matrix__::Vector::end()
{
  return Vector::Iterator{data_ + size_};
}
