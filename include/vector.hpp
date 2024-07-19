#ifndef __my_vector__
#define __my_vector__

#include "exceptions.hpp"

#include <cinttypes>
#include <vector>
#include <algorithm>
#include <iostream>
#include <limits>

namespace __Matrix__
{
  class Vector
  {
  public:
    /* Constructors and Destructor */
    explicit Vector();
    explicit Vector(size_t);
    explicit Vector(size_t, double);
    explicit Vector(size_t, double *const);
    explicit Vector(size_t, std::initializer_list<double>);
    Vector(std::initializer_list<double>);
    explicit Vector(size_t, std::vector<double>);
    Vector(std::vector<double>);
    Vector(Vector const &other);
    Vector(Vector &&other);
    ~Vector();

    // assignment
    Vector &operator=(Vector const &);
    Vector &operator=(Vector &&);
    Vector &operator=(double);

    // checks

    // bool is_zero() const;
    // bool is_constant() const;
    // bool is_orthogonal() const;

    // swap
    void swap(Vector &) noexcept;
    friend void swap(Vector &, Vector &);

    /* Getters and Setters*/

    // bounds unchecked, 'array of arrays' question
    double const &operator[](size_t) const;
    double &operator[](size_t);

    // bounds checked
    double const operator()(size_t) const;
    double &operator()(size_t);

    size_t size() const
    {
      return size_;
    }

    double const *data() const
    {
      return data_;
    }

    int id() const
    {
      return id_;
    }

    void set_size(size_t)
    {
      throw NotImplementedException(__FUNCTION__, "Stub message");
      // rows_ = height;
    }
   
    /** IO operations */
    friend std::ostream &operator<<(std::ostream &, Vector const &);
    friend std::istream &operator>>(std::istream &, Vector &);

    /* Operations */
    Vector &operator+=(double x)
    {
      std::transform((*this).data_, (*this).data_ + size_,
                     (*this).data_, [x](double &element)
                     { return element + x; });
      return *this;
    }
    Vector &operator+=(Vector const &other)
    {
      std::transform(other.data_, other.data_ + size_,
                     (*this).data_, (*this).data_, std::plus{});
      return *this;
    }

    Vector &operator-=(Vector const &other)
    {
      std::transform((*this).data_, (*this).data_ + size_,
                     other.data_, (*this).data_, std::minus{});
      return *this;
    }
    Vector &operator*=(double x)
    {
      std::for_each((*this).data_, (*this).data_ + size_, [x](double &element)
                    { element *= x; });
      return *this;
    }

    Vector &operator/=(double x)
    {
      *this *= (1. / x);
      return *this;
    }

    /** Statics */
    // static Vector identity(size_t);
    // static Vector x_vector(size_t, double = 0);
    // static Vector zero(size_t);
    // static Vector transposed(Vector const &);
    // static Vector inversed(Vector const &);

    // Vector operator^(int) const;

    // operator double() const;

    bool operator==(Vector const &) const;
    bool operator!=(Vector const &) const;
    bool operator<(Vector const &) const;
    bool operator<=(Vector const &) const;
    bool operator>(Vector const &) const;
    bool operator>=(Vector const &) const;

    // void transpose();
    // void inverse();

    // Vector operator^(int x) const;

    // Iterator basics
    class Iterator;
    Iterator begin();
    Iterator end();

  private:
    uint8_t size_;
    static int id_counter_;
    int const id_;
    double *data_;

    double &at(size_t);
    double const &at(size_t) const;
  };
}

#endif